#pragma once

#include "this_.hxx"


namespace ap::event {
inline namespace this_ {
namespace traits {
namespace parent_ = this_;
inline namespace this_ {
namespace parent_ = parent_;

using Default = void;

template <class = Default> struct Wrapper;

template <class ... T> using Type = typename Wrapper<T ...>::Type;

} // inline namespace this_
} // namespace traits
} // inline namespace this_
} // namespace ap::event
