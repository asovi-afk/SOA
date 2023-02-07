// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: notify.proto

#ifndef GOOGLE_PROTOBUF_INCLUDED_notify_2eproto
#define GOOGLE_PROTOBUF_INCLUDED_notify_2eproto

#include <limits>
#include <string>

#include <google/protobuf/port_def.inc>
#if PROTOBUF_VERSION < 3021000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers. Please update
#error your headers.
#endif
#if 3021006 < PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers. Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/port_undef.inc>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/metadata_lite.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>  // IWYU pragma: export
#include <google/protobuf/extension_set.h>  // IWYU pragma: export
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>
#define PROTOBUF_INTERNAL_EXPORT_notify_2eproto
PROTOBUF_NAMESPACE_OPEN
namespace internal {
class AnyMetadata;
}  // namespace internal
PROTOBUF_NAMESPACE_CLOSE

// Internal implementation detail -- do not use these members.
struct TableStruct_notify_2eproto {
  static const uint32_t offsets[];
};
extern const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_notify_2eproto;
namespace notify {
class NotificationRequest;
struct NotificationRequestDefaultTypeInternal;
extern NotificationRequestDefaultTypeInternal _NotificationRequest_default_instance_;
class NotificationResponse;
struct NotificationResponseDefaultTypeInternal;
extern NotificationResponseDefaultTypeInternal _NotificationResponse_default_instance_;
}  // namespace notify
PROTOBUF_NAMESPACE_OPEN
template<> ::notify::NotificationRequest* Arena::CreateMaybeMessage<::notify::NotificationRequest>(Arena*);
template<> ::notify::NotificationResponse* Arena::CreateMaybeMessage<::notify::NotificationResponse>(Arena*);
PROTOBUF_NAMESPACE_CLOSE
namespace notify {

// ===================================================================

class NotificationRequest final :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:notify.NotificationRequest) */ {
 public:
  inline NotificationRequest() : NotificationRequest(nullptr) {}
  ~NotificationRequest() override;
  explicit PROTOBUF_CONSTEXPR NotificationRequest(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized);

  NotificationRequest(const NotificationRequest& from);
  NotificationRequest(NotificationRequest&& from) noexcept
    : NotificationRequest() {
    *this = ::std::move(from);
  }

  inline NotificationRequest& operator=(const NotificationRequest& from) {
    CopyFrom(from);
    return *this;
  }
  inline NotificationRequest& operator=(NotificationRequest&& from) noexcept {
    if (this == &from) return *this;
    if (GetOwningArena() == from.GetOwningArena()
  #ifdef PROTOBUF_FORCE_COPY_IN_MOVE
        && GetOwningArena() != nullptr
  #endif  // !PROTOBUF_FORCE_COPY_IN_MOVE
    ) {
      InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* GetDescriptor() {
    return default_instance().GetMetadata().descriptor;
  }
  static const ::PROTOBUF_NAMESPACE_ID::Reflection* GetReflection() {
    return default_instance().GetMetadata().reflection;
  }
  static const NotificationRequest& default_instance() {
    return *internal_default_instance();
  }
  static inline const NotificationRequest* internal_default_instance() {
    return reinterpret_cast<const NotificationRequest*>(
               &_NotificationRequest_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    0;

  friend void swap(NotificationRequest& a, NotificationRequest& b) {
    a.Swap(&b);
  }
  inline void Swap(NotificationRequest* other) {
    if (other == this) return;
  #ifdef PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetOwningArena() != nullptr &&
        GetOwningArena() == other->GetOwningArena()) {
   #else  // PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetOwningArena() == other->GetOwningArena()) {
  #endif  // !PROTOBUF_FORCE_COPY_IN_SWAP
      InternalSwap(other);
    } else {
      ::PROTOBUF_NAMESPACE_ID::internal::GenericSwap(this, other);
    }
  }
  void UnsafeArenaSwap(NotificationRequest* other) {
    if (other == this) return;
    GOOGLE_DCHECK(GetOwningArena() == other->GetOwningArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  NotificationRequest* New(::PROTOBUF_NAMESPACE_ID::Arena* arena = nullptr) const final {
    return CreateMaybeMessage<NotificationRequest>(arena);
  }
  using ::PROTOBUF_NAMESPACE_ID::Message::CopyFrom;
  void CopyFrom(const NotificationRequest& from);
  using ::PROTOBUF_NAMESPACE_ID::Message::MergeFrom;
  void MergeFrom( const NotificationRequest& from) {
    NotificationRequest::MergeImpl(*this, from);
  }
  private:
  static void MergeImpl(::PROTOBUF_NAMESPACE_ID::Message& to_msg, const ::PROTOBUF_NAMESPACE_ID::Message& from_msg);
  public:
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  const char* _InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) final;
  uint8_t* _InternalSerialize(
      uint8_t* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const final;
  int GetCachedSize() const final { return _impl_._cached_size_.Get(); }

  private:
  void SharedCtor(::PROTOBUF_NAMESPACE_ID::Arena* arena, bool is_message_owned);
  void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(NotificationRequest* other);

  private:
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "notify.NotificationRequest";
  }
  protected:
  explicit NotificationRequest(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                       bool is_message_owned = false);
  public:

  static const ClassData _class_data_;
  const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*GetClassData() const final;

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kTitleFieldNumber = 1,
  };
  // string title = 1;
  void clear_title();
  const std::string& title() const;
  template <typename ArgT0 = const std::string&, typename... ArgT>
  void set_title(ArgT0&& arg0, ArgT... args);
  std::string* mutable_title();
  PROTOBUF_NODISCARD std::string* release_title();
  void set_allocated_title(std::string* title);
  private:
  const std::string& _internal_title() const;
  inline PROTOBUF_ALWAYS_INLINE void _internal_set_title(const std::string& value);
  std::string* _internal_mutable_title();
  public:

  // @@protoc_insertion_point(class_scope:notify.NotificationRequest)
 private:
  class _Internal;

  template <typename T> friend class ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper;
  typedef void InternalArenaConstructable_;
  typedef void DestructorSkippable_;
  struct Impl_ {
    ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr title_;
    mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  };
  union { Impl_ _impl_; };
  friend struct ::TableStruct_notify_2eproto;
};
// -------------------------------------------------------------------

class NotificationResponse final :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:notify.NotificationResponse) */ {
 public:
  inline NotificationResponse() : NotificationResponse(nullptr) {}
  ~NotificationResponse() override;
  explicit PROTOBUF_CONSTEXPR NotificationResponse(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized);

  NotificationResponse(const NotificationResponse& from);
  NotificationResponse(NotificationResponse&& from) noexcept
    : NotificationResponse() {
    *this = ::std::move(from);
  }

  inline NotificationResponse& operator=(const NotificationResponse& from) {
    CopyFrom(from);
    return *this;
  }
  inline NotificationResponse& operator=(NotificationResponse&& from) noexcept {
    if (this == &from) return *this;
    if (GetOwningArena() == from.GetOwningArena()
  #ifdef PROTOBUF_FORCE_COPY_IN_MOVE
        && GetOwningArena() != nullptr
  #endif  // !PROTOBUF_FORCE_COPY_IN_MOVE
    ) {
      InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* GetDescriptor() {
    return default_instance().GetMetadata().descriptor;
  }
  static const ::PROTOBUF_NAMESPACE_ID::Reflection* GetReflection() {
    return default_instance().GetMetadata().reflection;
  }
  static const NotificationResponse& default_instance() {
    return *internal_default_instance();
  }
  static inline const NotificationResponse* internal_default_instance() {
    return reinterpret_cast<const NotificationResponse*>(
               &_NotificationResponse_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    1;

  friend void swap(NotificationResponse& a, NotificationResponse& b) {
    a.Swap(&b);
  }
  inline void Swap(NotificationResponse* other) {
    if (other == this) return;
  #ifdef PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetOwningArena() != nullptr &&
        GetOwningArena() == other->GetOwningArena()) {
   #else  // PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetOwningArena() == other->GetOwningArena()) {
  #endif  // !PROTOBUF_FORCE_COPY_IN_SWAP
      InternalSwap(other);
    } else {
      ::PROTOBUF_NAMESPACE_ID::internal::GenericSwap(this, other);
    }
  }
  void UnsafeArenaSwap(NotificationResponse* other) {
    if (other == this) return;
    GOOGLE_DCHECK(GetOwningArena() == other->GetOwningArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  NotificationResponse* New(::PROTOBUF_NAMESPACE_ID::Arena* arena = nullptr) const final {
    return CreateMaybeMessage<NotificationResponse>(arena);
  }
  using ::PROTOBUF_NAMESPACE_ID::Message::CopyFrom;
  void CopyFrom(const NotificationResponse& from);
  using ::PROTOBUF_NAMESPACE_ID::Message::MergeFrom;
  void MergeFrom( const NotificationResponse& from) {
    NotificationResponse::MergeImpl(*this, from);
  }
  private:
  static void MergeImpl(::PROTOBUF_NAMESPACE_ID::Message& to_msg, const ::PROTOBUF_NAMESPACE_ID::Message& from_msg);
  public:
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  const char* _InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) final;
  uint8_t* _InternalSerialize(
      uint8_t* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const final;
  int GetCachedSize() const final { return _impl_._cached_size_.Get(); }

  private:
  void SharedCtor(::PROTOBUF_NAMESPACE_ID::Arena* arena, bool is_message_owned);
  void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(NotificationResponse* other);

  private:
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "notify.NotificationResponse";
  }
  protected:
  explicit NotificationResponse(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                       bool is_message_owned = false);
  public:

  static const ClassData _class_data_;
  const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*GetClassData() const final;

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kMsgFieldNumber = 1,
  };
  // string msg = 1;
  void clear_msg();
  const std::string& msg() const;
  template <typename ArgT0 = const std::string&, typename... ArgT>
  void set_msg(ArgT0&& arg0, ArgT... args);
  std::string* mutable_msg();
  PROTOBUF_NODISCARD std::string* release_msg();
  void set_allocated_msg(std::string* msg);
  private:
  const std::string& _internal_msg() const;
  inline PROTOBUF_ALWAYS_INLINE void _internal_set_msg(const std::string& value);
  std::string* _internal_mutable_msg();
  public:

  // @@protoc_insertion_point(class_scope:notify.NotificationResponse)
 private:
  class _Internal;

  template <typename T> friend class ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper;
  typedef void InternalArenaConstructable_;
  typedef void DestructorSkippable_;
  struct Impl_ {
    ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr msg_;
    mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  };
  union { Impl_ _impl_; };
  friend struct ::TableStruct_notify_2eproto;
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// NotificationRequest

// string title = 1;
inline void NotificationRequest::clear_title() {
  _impl_.title_.ClearToEmpty();
}
inline const std::string& NotificationRequest::title() const {
  // @@protoc_insertion_point(field_get:notify.NotificationRequest.title)
  return _internal_title();
}
template <typename ArgT0, typename... ArgT>
inline PROTOBUF_ALWAYS_INLINE
void NotificationRequest::set_title(ArgT0&& arg0, ArgT... args) {
 
 _impl_.title_.Set(static_cast<ArgT0 &&>(arg0), args..., GetArenaForAllocation());
  // @@protoc_insertion_point(field_set:notify.NotificationRequest.title)
}
inline std::string* NotificationRequest::mutable_title() {
  std::string* _s = _internal_mutable_title();
  // @@protoc_insertion_point(field_mutable:notify.NotificationRequest.title)
  return _s;
}
inline const std::string& NotificationRequest::_internal_title() const {
  return _impl_.title_.Get();
}
inline void NotificationRequest::_internal_set_title(const std::string& value) {
  
  _impl_.title_.Set(value, GetArenaForAllocation());
}
inline std::string* NotificationRequest::_internal_mutable_title() {
  
  return _impl_.title_.Mutable(GetArenaForAllocation());
}
inline std::string* NotificationRequest::release_title() {
  // @@protoc_insertion_point(field_release:notify.NotificationRequest.title)
  return _impl_.title_.Release();
}
inline void NotificationRequest::set_allocated_title(std::string* title) {
  if (title != nullptr) {
    
  } else {
    
  }
  _impl_.title_.SetAllocated(title, GetArenaForAllocation());
#ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
  if (_impl_.title_.IsDefault()) {
    _impl_.title_.Set("", GetArenaForAllocation());
  }
#endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  // @@protoc_insertion_point(field_set_allocated:notify.NotificationRequest.title)
}

// -------------------------------------------------------------------

// NotificationResponse

// string msg = 1;
inline void NotificationResponse::clear_msg() {
  _impl_.msg_.ClearToEmpty();
}
inline const std::string& NotificationResponse::msg() const {
  // @@protoc_insertion_point(field_get:notify.NotificationResponse.msg)
  return _internal_msg();
}
template <typename ArgT0, typename... ArgT>
inline PROTOBUF_ALWAYS_INLINE
void NotificationResponse::set_msg(ArgT0&& arg0, ArgT... args) {
 
 _impl_.msg_.Set(static_cast<ArgT0 &&>(arg0), args..., GetArenaForAllocation());
  // @@protoc_insertion_point(field_set:notify.NotificationResponse.msg)
}
inline std::string* NotificationResponse::mutable_msg() {
  std::string* _s = _internal_mutable_msg();
  // @@protoc_insertion_point(field_mutable:notify.NotificationResponse.msg)
  return _s;
}
inline const std::string& NotificationResponse::_internal_msg() const {
  return _impl_.msg_.Get();
}
inline void NotificationResponse::_internal_set_msg(const std::string& value) {
  
  _impl_.msg_.Set(value, GetArenaForAllocation());
}
inline std::string* NotificationResponse::_internal_mutable_msg() {
  
  return _impl_.msg_.Mutable(GetArenaForAllocation());
}
inline std::string* NotificationResponse::release_msg() {
  // @@protoc_insertion_point(field_release:notify.NotificationResponse.msg)
  return _impl_.msg_.Release();
}
inline void NotificationResponse::set_allocated_msg(std::string* msg) {
  if (msg != nullptr) {
    
  } else {
    
  }
  _impl_.msg_.SetAllocated(msg, GetArenaForAllocation());
#ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
  if (_impl_.msg_.IsDefault()) {
    _impl_.msg_.Set("", GetArenaForAllocation());
  }
#endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  // @@protoc_insertion_point(field_set_allocated:notify.NotificationResponse.msg)
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__
// -------------------------------------------------------------------


// @@protoc_insertion_point(namespace_scope)

}  // namespace notify

// @@protoc_insertion_point(global_scope)

#include <google/protobuf/port_undef.inc>
#endif  // GOOGLE_PROTOBUF_INCLUDED_GOOGLE_PROTOBUF_INCLUDED_notify_2eproto
