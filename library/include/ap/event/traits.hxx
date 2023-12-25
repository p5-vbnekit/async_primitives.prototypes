#pragma once

#include <type_traits>

#include "traits.fwd.hxx"


namespace ap::event::traits {
inline namespace this_ {

template <class T> struct Wrapper final {
    using Type = ::std::decay_t<T>;
    static_assert(::std::is_same_v<T, Type>);
};

} // inline namespace this_
} // namespace ap::event::traits
