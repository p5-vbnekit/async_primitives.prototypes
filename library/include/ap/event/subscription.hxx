#pragma once

#include <memory>

#include "subscription.fwd.hxx"


namespace ap::event::subscription {
inline namespace this_ {

using Entry = this_::storage::Entry;
using Pointer = ::std::weak_ptr<this_::storage::Entry>;

struct Type final {
    using Pointer = this_::Pointer;

    bool state() const noexcept(true);

    bool cancel() noexcept(true);
    bool detach() noexcept(true);
    Type && take() noexcept(true);

    inline operator bool () const noexcept(true) { return state(); }

    ~Type();
    explicit Type(Pointer &&) noexcept(false);

    Type() = default;
    Type(Type &&) = default;
    Type(Type const &) = default;

    Type & operator = (Type &&) = default;
    Type & operator = (Type const &) = default;

private:
    friend Entry;
    struct Private_;
    ::std::shared_ptr<Private_> private_ = {};
};

} // inline namespace this_
} // namespace ap::event::subscription
