#include <grpcpp/grpcpp.h>
#include <string>
#include "notify.grpc.pb.h"

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

    std::cout << "New request: \n[ ";
    bool isFirst = true;
    while (reader->Read(&request)) {
      if (!isFirst) 
        std::cout << "; ";
      std::cout << request.title();
      isFirst = false;
    }            
    std::cout << "]\n";

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