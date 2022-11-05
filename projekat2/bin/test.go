package main

import (
	"context"
	"fmt"
	"time"

	"encoding/json"
	"os"
	"os/signal"
	"syscall"

	mqtt "github.com/eclipse/paho.mqtt.golang"

	"github.com/influxdata/influxdb-client-go/v2"
)

const (
	TOPIC = "topic1"
	QOS = 1
	SERVERADDRESS = "tcp://172.17.0.2:1883"
	CLIENTID = "mqtt_subscriber"

	WRITETOLOG  = true  // If true then received messages will be written to the console
	WRITETODISK = false // If true then received messages will be written to the file below

	OUTPUTFILE = "/binds/receivedMessages.txt"
)


// GLOBAL
var ch chan string

// handler is a simple struct that provides a function to be called when a message is received. The message is parsed
// and the count followed by the raw message is written to the file (this makes it easier to sort the file)
type handler struct {
	f *os.File
}

func NewHandler() *handler {
	var f *os.File
	if WRITETODISK {
		var err error
		f, err = os.Create(OUTPUTFILE)
		if err != nil {
			panic(err)
		}
	}
	return &handler {f: f}
}

// Close closes the file
func (o *handler) Close() {
	if o.f != nil {
		if err := o.f.Close(); err != nil {
			fmt.Printf("ERROR closing file: %s", err)
		}
		o.f = nil
	}
}

// Message 
type Message struct {
	Count uint64
}

// handle is called when a message is received
func (o *handler) handle(_ mqtt.Client, msg mqtt.Message) {
	// We extract the count and write that out first to simplify checking for missing values
	var m Message 



	if err := json.Unmarshal(msg.Payload(), &m); err != nil {
		fmt.Printf("Message could not be parsed (%s): %s", msg.Payload(), err)
	}
	if o.f != nil {
		// Write out the number (make it long enough that sorting works) and the payload
		if _, err := o.f.WriteString(fmt.Sprintf("%09d %s\n", m.Count, msg.Payload())); err != nil {
			fmt.Printf("ERROR writing to file: %s", err)
		}
	}

	if WRITETOLOG {
		fmt.Printf("received message: %s\n", msg.Payload())
	}
}


func writeToInfluxDB() {

	fmt.Println("write to influx db func START")
	client := influxdb2.NewClient("http://172.17.0.3:8086", "wtGv8HeY0n1twnoCi6NDpF8qbg2aU0u5hYlJ5poXWBzK4Mru1BcZCmSrQPFj1RvHgUN4Q9OLe62TYYrhrw_3jA==")
	writeAPI := client.WriteAPIBlocking("soa", "test")

	wg := sync.WaitGroup{}

	for v := range ch {
		wg.Add(1)
		go func() {
			fmt.Println("Updateing influx with: %s", v)
			p := influxdb2.NewPointWithMeasurement("mqtt").
				AddTag("unit", "message").
				AddField("payload", v).
				AddField("length", len(v)).
				SetTime(time.Now())
			// write point asynchronously
			writeAPI.WritePoint(p)
			// Flush writes
			writeAPI.Flush()
		}
	}

	wg.Wait()
	client.Close()
	fmt.Println("write to influx db func END")
}



func main() {
	fmt.Println("Hello There!")

	ch = make(chan string)
	go writeToInfluxDB(ch)


	// MQTT PART
	// Enable logging by uncommenting the below
	// mqtt.ERROR = log.New(os.Stdout, "[ERROR] ", 0)
	// mqtt.CRITICAL = log.New(os.Stdout, "[CRITICAL] ", 0)
	// mqtt.WARN = log.New(os.Stdout, "[WARN]  ", 0)
	// mqtt.DEBUG = log.New(os.Stdout, "[DEBUG] ", 0)

	// Create a handler that will deal with incoming messages
	h := NewHandler()
	defer h.Close()

	// Now we establish the connection to the mqtt broker
	opts := mqtt.NewClientOptions()
	opts.AddBroker(SERVERADDRESS)
	opts.SetClientID(CLIENTID)

	opts.SetOrderMatters(false)       // Allow out of order messages (use this option unless in order delivery is essential)
	opts.ConnectTimeout = time.Second // Minimal delays on connect
	opts.WriteTimeout = time.Second   // Minimal delays on writes
	opts.KeepAlive = 10               // Keepalive every 10 seconds so we quickly detect network outages
	opts.PingTimeout = time.Second    // local broker so response should be quick


	// Automate connection management (will keep trying to connect and will reconnect if network drops)
	opts.ConnectRetry = true
	opts.AutoReconnect = true

	// If using QOS2 and CleanSession = FALSE then it is possible that we will receive messages on topics that we
	// have not subscribed to here (if they were previously subscribed to they are part of the session and survive
	// disconnect/reconnect). Adding a DefaultPublishHandler lets us detect this.
	opts.DefaultPublishHandler = func(_ mqtt.Client, msg mqtt.Message) {
		fmt.Printf("UNEXPECTED MESSAGE: %s\n", msg)
	}

	// Log events
	opts.OnConnectionLost = func(cl mqtt.Client, err error) {
		fmt.Println("connection lost")
	}

	opts.OnConnect = func(c mqtt.Client) {
		fmt.Println("connection established")

		// Establish the subscription - doing this here means that it will happen every time a connection is established
		// (useful if opts.CleanSession is TRUE or the broker does not reliably store session data)
		t := c.Subscribe(TOPIC, QOS, h.handle)

		// the connection handler is called in a goroutine so blocking here would hot cause an issue. However as blocking
		// in other handlers does cause problems its best to just assume we should not block
		go func() {
			_ = t.Wait() // Can also use '<-t.Done()' in releases > 1.2.0
			if t.Error() != nil {
				fmt.Printf("ERROR SUBSCRIBING: %s\n", t.Error())
			} else {
				fmt.Println("subscribed to: ", TOPIC)
			}
		}()
	}

	opts.OnReconnecting = func(mqtt.Client, *mqtt.ClientOptions) {
		fmt.Println("attempting to reconnect")
	}

	//
	// Connect to the broker
	//
	client := mqtt.NewClient(opts)

	// If using QOS2 and CleanSession = FALSE then messages may be transmitted to us before the subscribe completes.
	// Adding routes prior to connecting is a way of ensuring that these messages are processed
	client.AddRoute(TOPIC, h.handle)

	if token := client.Connect(); token.Wait() && token.Error() != nil {
		panic(token.Error())
	}
	fmt.Println("Connection is up")

	// Messages will be delivered asynchronously so we just need to wait for a signal to shutdown
	sig := make(chan os.Signal, 1)
	signal.Notify(sig, os.Interrupt)
	signal.Notify(sig, syscall.SIGTERM)

	<-sig
	fmt.Println("signal caught - exiting")
	close(ch)
	client.Disconnect(1000)
	fmt.Println("shutdown complete")

}