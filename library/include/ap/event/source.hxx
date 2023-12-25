#pragma once

#include <memory>
#include <stdexcept>
#include <type_traits>

#include "source.fwd.hxx"
#include "subscription.fwd.hxx"

#include "handler.hxx"
#include "source/base.hxx"


namespace ap::event::source {

using Subscription = parent_::Subscription;

template <class ... T> using Handler = parent_::Handler<T ...>;

template <class EventType> struct Type: Base {
    using Event = EventType;
    using Policy = this_::Policy;
    using Handler = this_::Handler<EventType>;
    using Subscription = this_::Subscription;

    auto unsubscribe(Subscription const &) noexcept(false);
    template <class T> auto subscribe(T &&) noexcept(false);

protected:
    template <class T, class = ::std::enable_if_t<! ::std::is_base_of_v<Type, ::std::decay_t<T>>>>
    inline explicit Type(T &&policy) noexcept(false): policy_{::std::forward<T>(policy)} {
        if (! policy_) throw ::std::invalid_argument{"policy is null"};
    }

    Type(Type &&) = default;
    Type & operator = (Type &&) = default;

private:
    ::std::unique_ptr<Policy> policy_;

    Type() = delete;
    Type(Type const &) = delete;
    Type & operator = (Type const &) = delete;
};


// c++ template magic: inline implementation part

namespace policy {

using Event = void const *;
using Handler = parent_::Handler<Event>;
using Subscription = parent_::Subscription;

struct Type {
    using Handler = this_::Handler;
    using Subscription = this_::Subscription;

    virtual Subscription subscribe(Handler &&) noexcept(false) = 0;
    virtual void unsubscribe(Subscription const &) noexcept(false) = 0;
    virtual ~Type();
};

} // namespace policy

using Policy = policy::Type;


template <class EventType>
inline auto Type<EventType>::unsubscribe(
    Subscription const &subscription
) noexcept(false) { policy_->unsubscribe(subscription); }

template <class EventType> template <class T>
inline auto Type<EventType>::subscribe(T &&handler) noexcept(false) {
    auto &&handler_ = [&handler] () -> decltype(auto) {
        if constexpr (::std::is_same_v<Handler, ::std::decay_t<T>>) return ::std::forward<T>(handler);
        else return Handler{::std::forward<T>(handler)};
    } ();
    if (! handler_) throw ::std::invalid_argument{"empty handler"};
    return policy_->subscribe([handler_ = ::std::move(handler_)] (auto const &event) { try {
        if constexpr (::std::is_same_v<T, void>) handler_();
        else handler_(*static_cast<EventType const *>(event));
    } catch (...) {}});
}

} // namespace ap::event::source
