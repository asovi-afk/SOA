// Generated by the gRPC C++ plugin.
// If you make any local change, they will be lost.
// source: notify.proto
#ifndef GRPC_notify_2eproto__INCLUDED
#define GRPC_notify_2eproto__INCLUDED

#include "notify.pb.h"

#include <functional>
#include <grpcpp/generic/async_generic_service.h>
#include <grpcpp/support/async_stream.h>
#include <grpcpp/support/async_unary_call.h>
#include <grpcpp/impl/codegen/client_callback.h>
#include <grpcpp/impl/codegen/client_context.h>
#include <grpcpp/impl/codegen/completion_queue.h>
#include <grpcpp/impl/codegen/message_allocator.h>
#include <grpcpp/impl/codegen/method_handler.h>
#include <grpcpp/impl/codegen/proto_utils.h>
#include <grpcpp/impl/codegen/rpc_method.h>
#include <grpcpp/impl/codegen/server_callback.h>
#include <grpcpp/impl/codegen/server_callback_handlers.h>
#include <grpcpp/impl/codegen/server_context.h>
#include <grpcpp/impl/codegen/service_type.h>
#include <grpcpp/impl/codegen/status.h>
#include <grpcpp/impl/codegen/stub_options.h>
#include <grpcpp/impl/codegen/sync_stream.h>

namespace notify {

class Notifier final {
 public:
  static constexpr char const* service_full_name() {
    return "notify.Notifier";
  }
  class StubInterface {
   public:
    virtual ~StubInterface() {}
    // client-side streaming RPC
    std::unique_ptr< ::grpc::ClientWriterInterface< ::notify::NotificationRequest>> Notify(::grpc::ClientContext* context, ::notify::NotificationResponse* response) {
      return std::unique_ptr< ::grpc::ClientWriterInterface< ::notify::NotificationRequest>>(NotifyRaw(context, response));
    }
    std::unique_ptr< ::grpc::ClientAsyncWriterInterface< ::notify::NotificationRequest>> AsyncNotify(::grpc::ClientContext* context, ::notify::NotificationResponse* response, ::grpc::CompletionQueue* cq, void* tag) {
      return std::unique_ptr< ::grpc::ClientAsyncWriterInterface< ::notify::NotificationRequest>>(AsyncNotifyRaw(context, response, cq, tag));
    }
    std::unique_ptr< ::grpc::ClientAsyncWriterInterface< ::notify::NotificationRequest>> PrepareAsyncNotify(::grpc::ClientContext* context, ::notify::NotificationResponse* response, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncWriterInterface< ::notify::NotificationRequest>>(PrepareAsyncNotifyRaw(context, response, cq));
    }
    class async_interface {
     public:
      virtual ~async_interface() {}
      // client-side streaming RPC
      virtual void Notify(::grpc::ClientContext* context, ::notify::NotificationResponse* response, ::grpc::ClientWriteReactor< ::notify::NotificationRequest>* reactor) = 0;
    };
    typedef class async_interface experimental_async_interface;
    virtual class async_interface* async() { return nullptr; }
    class async_interface* experimental_async() { return async(); }
   private:
    virtual ::grpc::ClientWriterInterface< ::notify::NotificationRequest>* NotifyRaw(::grpc::ClientContext* context, ::notify::NotificationResponse* response) = 0;
    virtual ::grpc::ClientAsyncWriterInterface< ::notify::NotificationRequest>* AsyncNotifyRaw(::grpc::ClientContext* context, ::notify::NotificationResponse* response, ::grpc::CompletionQueue* cq, void* tag) = 0;
    virtual ::grpc::ClientAsyncWriterInterface< ::notify::NotificationRequest>* PrepareAsyncNotifyRaw(::grpc::ClientContext* context, ::notify::NotificationResponse* response, ::grpc::CompletionQueue* cq) = 0;
  };
  class Stub final : public StubInterface {
   public:
    Stub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options = ::grpc::StubOptions());
    std::unique_ptr< ::grpc::ClientWriter< ::notify::NotificationRequest>> Notify(::grpc::ClientContext* context, ::notify::NotificationResponse* response) {
      return std::unique_ptr< ::grpc::ClientWriter< ::notify::NotificationRequest>>(NotifyRaw(context, response));
    }
    std::unique_ptr< ::grpc::ClientAsyncWriter< ::notify::NotificationRequest>> AsyncNotify(::grpc::ClientContext* context, ::notify::NotificationResponse* response, ::grpc::CompletionQueue* cq, void* tag) {
      return std::unique_ptr< ::grpc::ClientAsyncWriter< ::notify::NotificationRequest>>(AsyncNotifyRaw(context, response, cq, tag));
    }
    std::unique_ptr< ::grpc::ClientAsyncWriter< ::notify::NotificationRequest>> PrepareAsyncNotify(::grpc::ClientContext* context, ::notify::NotificationResponse* response, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncWriter< ::notify::NotificationRequest>>(PrepareAsyncNotifyRaw(context, response, cq));
    }
    class async final :
      public StubInterface::async_interface {
     public:
      void Notify(::grpc::ClientContext* context, ::notify::NotificationResponse* response, ::grpc::ClientWriteReactor< ::notify::NotificationRequest>* reactor) override;
     private:
      friend class Stub;
      explicit async(Stub* stub): stub_(stub) { }
      Stub* stub() { return stub_; }
      Stub* stub_;
    };
    class async* async() override { return &async_stub_; }

   private:
    std::shared_ptr< ::grpc::ChannelInterface> channel_;
    class async async_stub_{this};
    ::grpc::ClientWriter< ::notify::NotificationRequest>* NotifyRaw(::grpc::ClientContext* context, ::notify::NotificationResponse* response) override;
    ::grpc::ClientAsyncWriter< ::notify::NotificationRequest>* AsyncNotifyRaw(::grpc::ClientContext* context, ::notify::NotificationResponse* response, ::grpc::CompletionQueue* cq, void* tag) override;
    ::grpc::ClientAsyncWriter< ::notify::NotificationRequest>* PrepareAsyncNotifyRaw(::grpc::ClientContext* context, ::notify::NotificationResponse* response, ::grpc::CompletionQueue* cq) override;
    const ::grpc::internal::RpcMethod rpcmethod_Notify_;
  };
  static std::unique_ptr<Stub> NewStub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options = ::grpc::StubOptions());

  class Service : public ::grpc::Service {
   public:
    Service();
    virtual ~Service();
    // client-side streaming RPC
    virtual ::grpc::Status Notify(::grpc::ServerContext* context, ::grpc::ServerReader< ::notify::NotificationRequest>* reader, ::notify::NotificationResponse* response);
  };
  template <class BaseClass>
  class WithAsyncMethod_Notify : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithAsyncMethod_Notify() {
      ::grpc::Service::MarkMethodAsync(0);
    }
    ~WithAsyncMethod_Notify() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status Notify(::grpc::ServerContext* /*context*/, ::grpc::ServerReader< ::notify::NotificationRequest>* /*reader*/, ::notify::NotificationResponse* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    void RequestNotify(::grpc::ServerContext* context, ::grpc::ServerAsyncReader< ::notify::NotificationResponse, ::notify::NotificationRequest>* reader, ::grpc::CompletionQueue* new_call_cq, ::grpc::ServerCompletionQueue* notification_cq, void *tag) {
      ::grpc::Service::RequestAsyncClientStreaming(0, context, reader, new_call_cq, notification_cq, tag);
    }
  };
  typedef WithAsyncMethod_Notify<Service > AsyncService;
  template <class BaseClass>
  class WithCallbackMethod_Notify : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithCallbackMethod_Notify() {
      ::grpc::Service::MarkMethodCallback(0,
          new ::grpc::internal::CallbackClientStreamingHandler< ::notify::NotificationRequest, ::notify::NotificationResponse>(
            [this](
                   ::grpc::CallbackServerContext* context, ::notify::NotificationResponse* response) { return this->Notify(context, response); }));
    }
    ~WithCallbackMethod_Notify() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status Notify(::grpc::ServerContext* /*context*/, ::grpc::ServerReader< ::notify::NotificationRequest>* /*reader*/, ::notify::NotificationResponse* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    virtual ::grpc::ServerReadReactor< ::notify::NotificationRequest>* Notify(
      ::grpc::CallbackServerContext* /*context*/, ::notify::NotificationResponse* /*response*/)  { return nullptr; }
  };
  typedef WithCallbackMethod_Notify<Service > CallbackService;
  typedef CallbackService ExperimentalCallbackService;
  template <class BaseClass>
  class WithGenericMethod_Notify : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithGenericMethod_Notify() {
      ::grpc::Service::MarkMethodGeneric(0);
    }
    ~WithGenericMethod_Notify() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status Notify(::grpc::ServerContext* /*context*/, ::grpc::ServerReader< ::notify::NotificationRequest>* /*reader*/, ::notify::NotificationResponse* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
  };
  template <class BaseClass>
  class WithRawMethod_Notify : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithRawMethod_Notify() {
      ::grpc::Service::MarkMethodRaw(0);
    }
    ~WithRawMethod_Notify() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status Notify(::grpc::ServerContext* /*context*/, ::grpc::ServerReader< ::notify::NotificationRequest>* /*reader*/, ::notify::NotificationResponse* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    void RequestNotify(::grpc::ServerContext* context, ::grpc::ServerAsyncReader< ::grpc::ByteBuffer, ::grpc::ByteBuffer>* reader, ::grpc::CompletionQueue* new_call_cq, ::grpc::ServerCompletionQueue* notification_cq, void *tag) {
      ::grpc::Service::RequestAsyncClientStreaming(0, context, reader, new_call_cq, notification_cq, tag);
    }
  };
  template <class BaseClass>
  class WithRawCallbackMethod_Notify : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithRawCallbackMethod_Notify() {
      ::grpc::Service::MarkMethodRawCallback(0,
          new ::grpc::internal::CallbackClientStreamingHandler< ::grpc::ByteBuffer, ::grpc::ByteBuffer>(
            [this](
                   ::grpc::CallbackServerContext* context, ::grpc::ByteBuffer* response) { return this->Notify(context, response); }));
    }
    ~WithRawCallbackMethod_Notify() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status Notify(::grpc::ServerContext* /*context*/, ::grpc::ServerReader< ::notify::NotificationRequest>* /*reader*/, ::notify::NotificationResponse* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    virtual ::grpc::ServerReadReactor< ::grpc::ByteBuffer>* Notify(
      ::grpc::CallbackServerContext* /*context*/, ::grpc::ByteBuffer* /*response*/)  { return nullptr; }
  };
  typedef Service StreamedUnaryService;
  typedef Service SplitStreamedService;
  typedef Service StreamedService;
};

}  // namespace notify


#endif  // GRPC_notify_2eproto__INCLUDED
