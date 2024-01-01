#pragma once

#include "this_.hxx"

#include "future.fwd.hxx"


namespace ap {
namespace promise {

namespace parent_ = this_;
namespace this_ = parent_::promise;

template <class ... T> using Future = parent_::Future<T ...>;
template <class ... T> using Value = typename parent_::future::Value<T ...>;

template <class = Value<>> struct Type;

} // namespace promise

template <class ... T> using Promise = promise::Type<T ...>;

} // namespace ap
