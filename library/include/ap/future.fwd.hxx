#pragma once

#include "this_.hxx"

#include "event/traits.fwd.hxx"


namespace ap {
namespace future {

namespace parent_ = this_;
namespace this_ = parent_::future;

using DefaultValueType = parent_::event::traits::Default;

template <class = DefaultValueType> struct Type;

} // namespace future

template <class ... T> using Future = future::Type<T ...>;

} // namespace ap
