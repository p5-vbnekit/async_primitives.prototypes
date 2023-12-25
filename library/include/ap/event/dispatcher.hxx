#pragma once

#include <memory>
#include <type_traits>

#include "dispatcher.fwd.hxx"

#include "source.hxx"
#include "handler.hxx"


namespace ap::event::dispatcher {
inline namespace this_ {

using Subscription = parent_::Subscription;

template <class ... T> using Base = parent_::Source<T ...>;
template <class ... T> using Handler = parent_::Handler<T ...>;

template <class EventType> struct Type final: Base<EventType> {
    using Base = this_::Base<EventType>;
    using Event = EventType;
    using Handler = this_::Handler<EventType>;
    using Subscription = this_::Subscription;

    template <class ... T> auto dispatch(T && ...);

    Type() noexcept(false);
    Type(Type &&) = default;
    Type & operator = (Type &&) = default;

private:
    this_::Policy_ &policy_;

    Type(Type const &) = delete;
    Type & operator = (Type const &) = delete;

    explicit Type(::std::decay_t<decltype(policy_)> *policy) noexcept(false);
};


// c++ template magic: inline implementation part

namespace policy_ {
inline namespace this_ {
namespace base = parent_::parent_::source::policy;

using Base = base::Type;
using Event = base::Event;
using Handler = base::Handler;
using Subscription = base::Subscription;

struct Type: Base {
    using Event = this_::Event;
    using Handler = this_::Handler;
    using Subscription = this_::Subscription;

    void dispatch(Event const &) noexcept(true);
    virtual Subscription subscribe(Handler &&) noexcept(false) override final;
    virtual void unsubscribe(Subscription const &) noexcept(false) override final;

    Type() noexcept(false);
    ~Type();

    Type(Type &&) = default;
    Type & operator = (Type &&) = default;

private:
    struct Private_;
    ::std::unique_ptr<Private_> private_;

    Type(Type const &) = delete;
    Type & operator = (Type const &) = delete;
};

template <class, class ...> constexpr static bool pass_pointer_condition_() noexcept(true);

} // inline namespace this_
} // namespace policy_


template <class EventType, class ... T>
inline constexpr static bool policy_::this_::pass_pointer_condition_() noexcept(true) {
    if constexpr (1 != sizeof ... (T)) return false;
    else return ::std::is_convertible_v<::std::add_pointer_t<T> ..., EventType const *>;
}

template <class EventType> template <class ... T>
inline auto Type<EventType>::dispatch(T && ... event) {
    if constexpr (::std::is_same_v<EventType, void>) {
        static_assert(0 == sizeof ... (T));
        policy_.dispatch(nullptr);
    }

    else {
        if constexpr (policy_::pass_pointer_condition_<EventType, T ...>()) policy_.dispatch(&event ...);
        else {
            EventType const event_{::std::forward<T>(event) ...};
            policy_.dispatch(&event_);
        }
    }
}

template <class EventType> inline Type<EventType>::Type() noexcept(false): Type{
    new ::std::decay_t<decltype(policy_)>
} {}

template <class EventType> inline Type<EventType>::Type(
    ::std::decay_t<decltype(policy_)> *policy
) noexcept(false): Base{policy}, policy_{*policy} {}

} // inline namespace this_
} // namespace ap::event::dispatcher
