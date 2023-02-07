package main

import (
	"flag"
	"fmt"
	"io"
	"log"
	"net"

	"google.golang.org/grpc"
	pb "analytics/notify"
)

var (
	port = flag.Int("port", 50051, "The server port")
)

type Server struct {
	pb.UnimplementedNotifierServer
}

func (s *Server) Notify(stream pb.Notifier_NotifyServer) error {
	log.Println("Got new notification stream")
	for {
		title, err := stream.Recv()
		if err == io.EOF {
			return stream.SendAndClose(&pb.NotificationResponse{})
		} 
		if err != nil {
			return err
		}
		log.Printf("%s - ", title)
	}
}

func main() {
	flag.Parse()

	lis, err := net.Listen("tcp", fmt.Sprintf(":%d", *port))
	if err != nil {
		log.Fatalf("failed to listen: %v", err)
	}

	s := grpc.NewServer()
	pb.RegisterNotifierServer(s, &Server{})
	log.Printf("server listening at %v", lis.Addr())
	if err := s.Serve(lis); err != nil {
		log.Fatalf("failed to serve: %v", err)
	}
}