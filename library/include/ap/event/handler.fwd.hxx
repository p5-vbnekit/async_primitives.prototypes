#pragma once

#include "this_.hxx"

#include "traits.fwd.hxx"


namespace ap::event {
namespace handler {

namespace parent_ = this_;
namespace this_ = parent_::handler;

namespace traits {

namespace parent_ = this_;
namespace this_ = parent_::traits;

template <class = parent_::parent_::traits::Default> struct Wrapper;

template <class ... T> using Type = typename Wrapper<T ...>::Type;

} // namespace traits

template <class ... T> using Type = typename traits::Type<T ...>;

} // namespace handler

template <class ... T> using Handler = handler::Type<T ...>;

} // namespace ap::event
