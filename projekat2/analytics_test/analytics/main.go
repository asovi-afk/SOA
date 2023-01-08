package main

import (
	"context"
	"encoding/json"
	"fmt"
	"flag"
	"log"
	"os"
	"os/signal"
	"sync"
	"syscall"
	"time"
	
	"github.com/eclipse/paho.mqtt.golang"
	"github.com/influxdata/influxdb-client-go/v2"

	"google.golang.org/grpc"
	"google.golang.org/grpc/credentials/insecure"

	pb "analytics/notify"
)

type Request struct {
	Title string `json:"title"`
}

type Result struct {
	Register []string `json:"register"`
}

var (
	Topics map[string]string = map[string]string {
		"signal": "analytics/requests/signal",	// gateway -> analytics
		"result": "analytics/results/filter", 	// ekuiper -> analytics
		"request": "analytics/requests/filter",	// analytics -> ekuiper
	}
	addr = flag.String("addr", "localhost:50051", "the address to connect to")
)

func Orchestration(f func()) context.Context {
	ctx, cancel := context.WithCancel(context.Background())

	go func() {
		c := make(chan os.Signal)
		signal.Notify(c, syscall.SIGINT, syscall.SIGTERM, syscall.SIGKILL)
		defer signal.Stop(c)
		
		select {
		case <-c: 
			f()
			cancel()
		}
	}()

	return ctx
}

func ProcessRequest(msg []byte, cMQTT mqtt.Client, cDB influxdb2.Client) {
	fmt.Printf("Process Request: %s\n", msg)
	fmt.Println("After Process Request!")
	// mosquitto
	token := cMQTT.Publish(Topics["request"], 0x02, false, msg)
	token.Wait()
	// unmarshal
	var rq Request
	json.Unmarshal(msg, &rq)
	fmt.Println(rq.Title)

	// influxdb
	writeAPI  := cDB.WriteAPI("soa", "analytics")
	p := influxdb2.NewPointWithMeasurement("stat").
		AddTag("unit", "string").
		AddField("title", rq.Title).
		SetTime(time.Now())
	writeAPI.WritePoint(p)
	writeAPI.Flush()
}

func ProcessResult(msg []byte, f func(rs Result) ) {
	fmt.Printf("Process Result: %s\n", msg)
	// unmarshal
	var rs Result
	if err := json.Unmarshal(msg, &rs); err != nil {
		fmt.Println("could not unmarshal result: ", err)
	} else if len(rs.Register) > 0{
		// qRPC
		fmt.Println("Trying gRPC")
		f(rs)
	}
	fmt.Printf("Unmarshaled: %v\n", rs)
	fmt.Printf("rs.Register: %v\n", rs.Register)
	fmt.Printf("rs.Register.Len: %v\n", len(rs.Register))
}

func main() {
	
	flag.Parse()
	ad := *addr
	fmt.Printf("%s\n", ad)
	for i:=0; i < 2; i++ {
		fmt.Println("You are here!")
	}

	time.Sleep(20 * time.Second)
	wg := &sync.WaitGroup{}
	stopped := make(chan struct{})

	ctx := Orchestration(func() {
		close(stopped)
		wg.Wait()
	})

	gRPCConn, err := grpc.Dial(*addr, grpc.WithTransportCredentials(insecure.NewCredentials()))
	if err != nil {
		fmt.Printf("did not connect: %v\n", err)
	}
	clientRPC := pb.NewNotifierClient(gRPCConn)

	clientDB := influxdb2.NewClient("http://analytics_influxdb:8086", "UDVHkVrADVF1TpkdCVjaycO9vKJfhjRZeDrcd2nWZN1fzaoGrQiZyxL6ehTjRyj8OGZry8Hsp_fa_4VGLYd-_g==")

	// mqtt.DEBUG = log.New(os.Stdout, "", 0)
	mqtt.ERROR = log.New(os.Stdout, "", 0)
	opts := mqtt.NewClientOptions().AddBroker("tcp://mosquitto:1883").SetClientID("analyticsTestClient")
	
	opts.SetKeepAlive(60 * time.Second)
	// Set the message callback handler
	opts.SetDefaultPublishHandler(func(cMQTT mqtt.Client, msg mqtt.Message){
		go func() {
			select {
			case <-stopped:
				return
			default:
				wg.Add(1)
				if msg.Topic() == Topics["signal"] {
					ProcessRequest(msg.Payload(), cMQTT, clientDB)
				} else {
					ProcessResult(msg.Payload(), func(rs Result) {
						fmt.Println("Starting F()")
						stream, err := clientRPC.Notify(context.Background())
						if err != nil {
							fmt.Printf("%v.Notify(_) = _, %v\n", clientRPC, err)
						}
						for _, title := range rs.Register {
							if err := stream.Send(&pb.NotificationRequest{Title: title}); err != nil {
								fmt.Printf("%v.Send(%v) = %v\n", stream, title, err)
							} else {
								m := make(map[string]string)
								m["Title"]=title
								fmt.Printf("gRPC poslat: %v\n", m)
							}
						}
						reply, err := stream.CloseAndRecv()
						if err != nil {
							fmt.Printf("%v.CloseAndRecv() = %v\n", stream, err)
						}
						fmt.Printf("gRPC Server returned: %v", reply)
					})
				}
				wg.Done()
			}
		}()
	})
	opts.SetPingTimeout(1 * time.Second)
	opts.SetOrderMatters(false)

	clientMQTT := mqtt.NewClient(opts)
	if token := clientMQTT.Connect(); token.Wait() && token.Error() != nil {
		panic(token.Error())
	}

	// Subscribe to a topic
	topics := map[string]byte {Topics["signal"]: 0x02, Topics["result"]: 0x02}
	if token := clientMQTT.SubscribeMultiple(topics, nil); token.Wait() && token.Error() != nil {
		fmt.Println(token.Error())
		os.Exit(1)
	}

	select {
	case <-ctx.Done():

		// gRPC
		gRPCConn.Close()

		// influxdb
		clientDB.Close()

		// Unscribe from mosquitto
		if token := clientMQTT.Unsubscribe("testtopic/#"); token.Wait() && token.Error() != nil {
			fmt.Println(token.Error())
			os.Exit(1)
		}
		// Disconnect from mosquitto
		clientMQTT.Disconnect(250)

		 time.Sleep(2 * time.Second)
		 fmt.Println("Analytics service ends.")
	}
}
