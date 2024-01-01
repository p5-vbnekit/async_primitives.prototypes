#pragma once

#include <exception>

#include "future.fwd.hxx"


namespace ap::future {

using Exception = ::std::exception_ptr;

template <class ValueType> struct Type final {
    using Value = this_::Value<ValueType>;
    using Exception = this_::Exception;

    auto state() const noexcept(true);
    auto cancelled() const noexcept(true);

    auto & value() const noexcept(false);
    auto exception() const noexcept(true);
    auto * pointer() const noexcept(true);

    auto detach() noexcept(true);
    auto && take() noexcept(true);
    auto const && take() const noexcept(true);

    auto cancel() const noexcept(true);
    template <class T> auto then(T &&) const noexcept(false);
};

} // namespace ap::future
