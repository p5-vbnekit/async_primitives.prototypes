#pragma once

#include <exception>

#include "promise.fwd.hxx"

#include "future.hxx"


namespace ap::promise {

template <class ValueType> struct Type final {
    using Value = this_::Value<ValueType>;
    using Future = this_::Future<ValueType>;

    auto future() const noexcept(true);

    template <class T> auto on_cancel(T &&) const noexcept(false);
    template <class ... T> auto set_value(T && ...) noexcept(false);
    template <class T> auto set_exception(T &&) noexcept(false);
};


// c++ template magic: inline implementation part

template <class ValueType>
inline auto Type<ValueType>::future() const noexcept(true) { return Future{}; }

template <class ValueType> template <class T>
inline auto Type<ValueType>::on_cancel(T &&) const noexcept(false) {}

template <class ValueType> template <class ... T>
inline auto Type<ValueType>::set_value(T && ...) noexcept(false) {}

template <class ValueType> template <class T>
inline auto Type<ValueType>::set_exception(T &&) noexcept(false) {}

} // namespace ap::promise
