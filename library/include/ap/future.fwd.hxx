#pragma once

#include "this_.hxx"

#include "event/traits.hxx"


namespace ap {
namespace future {

namespace parent_ = this_;
namespace this_ = parent_::future;

template <class ... T> using Value = typename parent_::event::traits::Type<T ...>;

template <class = Value<>> struct Type;

} // namespace future

template <class ... T> using Future = future::Type<T ...>;

} // namespace ap
