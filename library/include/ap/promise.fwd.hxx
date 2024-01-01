#pragma once

#include "this_.hxx"

#include "future.fwd.hxx"


namespace ap {
namespace promise {

namespace parent_ = this_;
namespace this_ = parent_::promise;

using DefaultValueType = parent_::future::DefaultValueType;

template <class = DefaultValueType> struct Type;

} // namespace promise

template <class ... T> using Promise = promise::Type<T ...>;

} // namespace ap
