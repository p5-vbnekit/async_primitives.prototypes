#pragma once

#include "this_.hxx"

#include "traits.fwd.hxx"


namespace ap::event {
inline namespace this_ {
namespace handler {
namespace parent_ = this_;
inline namespace this_ {
namespace parent_ = parent_;
namespace traits {
namespace parent_ = this_;
inline namespace this_ {
namespace parent_ = parent_;

template <class = parent_::parent_::traits::Default> struct Wrapper;

template <class ... T> using Type = typename Wrapper<T ...>::Type;

} // inline namespace this_
} // namespace traits

template <class ... T> using Type = typename traits::Type<T ...>;

} // inline namespace this_
} // namespace handler

template <class ... T> using Handler = handler::Type<T ...>;

} // inline namespace this_
} // namespace ap::event
