#include <list>
#include <memory>
#include <utility>
#include <algorithm>
#include <type_traits>

#include <ap.hxx>


namespace ap {
namespace event::subscription {
inline namespace this_ {
namespace storage {
inline namespace this_ {

struct Type;

namespace entry {
inline namespace this_ {

using Pointer = ::std::shared_ptr<Type>;
using Storage = parent_::Type &;
using Adapter = parent_::parent_::Type;
using Handler = parent_::parent_::parent_::source::policy::Handler;

struct Type final {
    using Pointer = this_::Pointer;
    using Adapter = this_::Adapter;
    using Storage = this_::Storage;
    using Handler = this_::Handler;

    Handler handler;
    Storage &storage;

    static Pointer get(Adapter const &) noexcept(true);
};

} // inline namespace this_
} // namespace entry

struct Type final: ::std::list<entry::Pointer> {};

} // inline namespace this_
} // namespace storage

using Storage = storage::Type;

} // inline namespace this_
} // namespace event::subscription

struct event::Subscription::Private_ final {
    bool weak = true;
    ::std::weak_ptr<storage::Entry> entry;

    ~Private_();
};

struct event::dispatcher::Policy_::Private_ final {
    subscription::Storage storage = {};
};


event::source::base::Type::~Type() {}

event::source::policy::Type::~Type() {}

inline event::subscription::storage::entry::Pointer
event::subscription::storage::Entry::get(Adapter const &adapter) noexcept(true) {
    if (! adapter.private_) return nullptr;
    return adapter.private_->entry.lock();
}

bool event::Subscription::state() const noexcept(true) {
    if (! private_) return false;
    return ! private_->entry.expired();
}

bool event::Subscription::cancel() noexcept(true) {
    if (! private_) return false;
    return [private_ = ::std::move(private_)] {
        auto &weak_ = private_->entry;
        if (weak_.expired()) return false;
        auto const shared_ = weak_.lock();
        weak_.reset();
        auto &storage_ = shared_->storage;
        auto const iterator_ = ::std::find(storage_.begin(), storage_.end(), shared_);
        if (storage_.end() == iterator_) return false;
        storage_.erase(iterator_);
        return true;
    } ();
}

bool event::Subscription::detach() noexcept(true) {
    if (! private_) return false;
    private_.reset();
    return true;
}

event::Subscription && event::Subscription::take() noexcept(true) {
    if (private_) private_->weak = false;
    return ::std::move(*this);
}

event::subscription::Type::~Type() {}

event::Subscription::Type(Pointer &&entry) noexcept(false): private_{
    entry.expired() ? nullptr : new ::std::decay_t<decltype(*private_)>{true, ::std::move(entry)}
} {}

event::Subscription::Private_::~Private_() {
    if (weak || entry.expired()) return;
    auto const entry_ = entry.lock();
    auto &storage_ = entry_->storage;
    auto const iterator_ = ::std::find(storage_.begin(), storage_.end(), entry_);
    if (storage_.end() == iterator_) return;
    storage_.erase(iterator_);
}

void event::dispatcher::Policy_::dispatch(Event const &event) noexcept(true) {
    auto const storage_ = private_->storage;
    for (auto const &pointer_: storage_) {
        if (! pointer_) continue;
        auto const &handler_ = pointer_->handler;
        if (! handler_) continue;
        handler_(event);
    }
}

event::dispatcher::policy_::Subscription event::dispatcher::Policy_::subscribe(Handler &&handler) noexcept(false) {
    if (! handler) throw ::std::invalid_argument{"empty handler"};
    auto &storage_ = private_->storage;
    storage_.emplace_back(new subscription::storage::Entry{::std::move(handler), storage_});
    return Subscription{storage_.back()};
}

void event::dispatcher::Policy_::unsubscribe(Subscription const &subscription) noexcept(false) {
    auto const entry_ = subscription::storage::Entry::get(subscription);
    if (! entry_) throw ::std::invalid_argument{"expired subscription"};
    auto &storage_ = private_->storage;
    if (&(entry_->storage) != &storage_) throw ::std::invalid_argument{"alien subscription"};
    auto const iterator_ = ::std::find(storage_.begin(), storage_.end(), entry_);
    if (storage_.end() == iterator_) throw ::std::invalid_argument{"subscription not found"};
    storage_.erase(iterator_);
}

event::dispatcher::policy_::Type::~Type() {}

event::dispatcher::Policy_::Type() noexcept(false): private_{new ::std::decay_t<decltype(*private_)>} {}

} // namespace ap
