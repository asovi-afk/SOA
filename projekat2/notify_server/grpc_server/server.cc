#include <grpcpp/grpcpp.h>
#include <string>
#include "notify.grpc.pb.h"
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <ctime>

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::ServerReader;
using grpc::Status;

using notify::NotificationResponse;
using notify::NotificationRequest;
using notify::Notifier;

// Server Implementation
class NotifierImplementation final : public Notifier::Service {
  Status Notify(ServerContext* context, ServerReader<NotificationRequest>* reader,
                     NotificationResponse* reply) override {
    NotificationRequest request;

    // std::cout i printf u ovom delu koda ne stampaju izlaz vidljiv docker-compose-u. 
    // Zato se parametri loguju u logs.txt fajlu.
    // Fajl se moze pratiti pozivom 'notification_logs.sh' skripte sa konzole host-a.
    std::ofstream log_file;
    log_file.open("logs.txt");
    std::time_t now = std::time(nullptr);
    char timestamp[64];
    std::strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", std::localtime(&now));
    log_file << "[" << timestamp << "] New request: [ ";
    
    std::cout << "New request: \n[ ";
    printf("New request: \n[ ");
    bool isFirst = true;
    while (reader->Read(&request)) {
      if (!isFirst) {
        printf("; ");
        std::cout << "; ";
        log_file << "; ";
      }
      std::cout << request.title();
      printf("%s", request.title());
      log_file << request.title();
      isFirst = false;
    }            

    std::cout << "]\n";
    printf("]\n");
    log_file << "]\n";
    log_file.close();
    // reply msg postoji kao potvrda da je gRPC uspesno izvrsena.
    reply->set_msg("Opet Jovo nanovo!");
    return Status::OK;
  }
};

void RunServer() {
  std::string server_address("0.0.0.0:50051");
  NotifierImplementation service;

  ServerBuilder builder;
  // Listen on the given address without any authentication mechanism
  builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
  // Register "service" as the instance through which
  // communication with client takes place
  builder.RegisterService(&service);

  // Assembling the server
  std::unique_ptr<Server> server(builder.BuildAndStart());
  std::cout << "Server listening on port: " << server_address << std::endl;

  server->Wait();
}

int main(int argc, char** argv) {
  RunServer();
  return 0;
}