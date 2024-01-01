#pragma once

#include "this_.hxx"


namespace ap::event::traits {

namespace parent_ = this_;
namespace this_ = parent_::traits;

using Default = void;

template <class = Default> struct Wrapper;

template <class ... T> using Type = typename Wrapper<T ...>::Type;

} // namespace ap::event::traits
