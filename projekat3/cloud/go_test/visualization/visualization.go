package main

import (
	"context"
	"encoding/json"
	"fmt"
	"flag"
	"os"
	"os/signal"
	"sync"
	"syscall"
	"strconv"
	"time"

	"github.com/eclipse/paho.mqtt.golang"
	"github.com/influxdata/influxdb-client-go/v2"
)

var (
	hostMQTT = flag.String("mqtt-host", "mqtt_brocker:1883", "mqtt brocker address and port to connect to")
	topic = flag.String("t", "p3/edgex/edgex-export-2", "topic to subscribe to") // edgex -> visualization
	hostIDB = flag.String("influxdb-host", "v-influxdb:8086", "influxdb address and port to connect to")
)

type Reading struct {
	ID         		string  `json:"id"`
	Origin     		uint64  `json:"origin"`
	DeviceName 		string  `json:"deviceName"`
	ResourceName 	string 	`json:"resourceName"`
	ProfileName 	string  `json:"profileName"`
	ValueType  		string  `json:"valueType"`
	Value      		string 	`json:"value"` // treba da bude Float64
}

type JsonStruct struct {
	APIVersion 	string  `json:"apiVersion"`
	ID         	string  `json:"id"`
	DeviceName 	string  `json:"deviceName"`
	ProfileName string 	`json:"profileName"`
	SourceName 	string  `json:"sourceName"`
	Origin     	uint64  `json:"origin"`
	Readings   []Reading `json:"readings"`
}

type Configs struct {
	HostMQTT		string
	Topic			string	
	HostInfluxDB 	string	
}

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


func main() {
	flag.Parse()
	fmt.Println("Visualization service started")	
	configs := Configs{*hostMQTT, *topic, *hostIDB}
	fmt.Printf("Current configs:\n %+v\n", configs)

	wg := &sync.WaitGroup{}
	stopped := make(chan struct{})

	ctx := Orchestration(func() {
		close(stopped)
		wg.Wait()
	})

	// influxdb
	clientIDB := influxdb2.NewClient(fmt.Sprintf("http://%s", configs.HostInfluxDB), "UDVHkVrADVF1TpkdCVjaycO9vKJfhjRZeDrcd2nWZN1fzaoGrQiZyxL6ehTjRyj8OGZry8Hsp_fa_4VGLYd-_g== ")

	// mosquitto
	opts := mqtt.NewClientOptions().AddBroker(fmt.Sprintf("tcp://%s", configs.HostMQTT)).SetClientID("visualizationClient")
	opts.SetKeepAlive(60 * time.Second)
	opts.SetDefaultPublishHandler(func(cMQTT mqtt.Client, msg mqtt.Message) {
		go func() {
			select {
			case  <- stopped:
					return
			default:
				wg.Add(1)
	
				var data JsonStruct
				json.Unmarshal(msg.Payload(), &data)
				value, _ := strconv.ParseFloat(data.Readings[0].Value, 64)
				
	
				// origin back to time.Time type
				origin := data.Readings[0].Origin
				exponent := uint64(1000000000)
				second := int64(origin / exponent)
				nanoSecond := int64(origin % exponent)
				timeStamp := time.Unix(second, nanoSecond)
				
				tag := data.Readings[0].ResourceName
	
				writeAPI := clientIDB.WriteAPI("soa","visualization")
				p := influxdb2.NewPointWithMeasurement("stat").
					AddTag("unit", tag).
					AddField("_value", value).
					SetTime(timeStamp)
				writeAPI.WritePoint(p)
				writeAPI.Flush()
	
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
	if token := clientMQTT.Subscribe(configs.Topic, 0x02, nil); token.Wait() && token.Error() != nil {
		fmt.Println(token.Error())
		os.Exit(1)
	}

	select {
	case <-ctx.Done():
		// influxdb
		clientIDB.Close()

		// Unscribe from mosquitto
		if token := clientMQTT.Unsubscribe(configs.Topic); token.Wait() && token.Error() != nil {
			fmt.Println(token.Error())
			os.Exit(1)
		}
		// Disconnect from mosquitto
		clientMQTT.Disconnect(250)

		 time.Sleep(2 * time.Second)
		 fmt.Println("Visualization service ends.")
	}
}

