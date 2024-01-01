#pragma once

#include <functional>
#include <type_traits>

#include "handler.fwd.hxx"

#include "traits.hxx"


namespace ap::event::handler::traits {

template <class T> struct Wrapper {
    using Type = ::std::function<void(typename parent_::parent_::traits::Type<T> const &)>;
};

} // namespace ap::event::handler::traits
