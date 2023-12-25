#include <string>
#include <utility>
#include <iostream>
#include <type_traits>

#include <QTimer>
#include <QCoreApplication>

#include <ap.hxx>


struct Example_ final {
    // Base type of `event dispatcher` is `event source`.
    // Let's make this interface public so that users can subscribe/unsubscribe while preventing `dispatch` call.
    inline auto & events() const noexcept(true) {
        // `KISS` says `static_cast<::ap::event::Source<::std::string> &>(dispatcher_)`
        // but we use type aliases whenever possible because `DRY`.
        return static_cast<::std::decay_t<decltype(dispatcher_)>::Base &>(dispatcher_);
    }

    // An alternative "wrap" way - nothing to explain. =)
    template <class T> inline auto watch(T &&handler) const noexcept(false) {
        return dispatcher_.subscribe(::std::forward<T>(handler));
    }

    // Lets declare `send` method for simulating asynchronous engine machinery of application.
    template <class ... T> inline auto send(T && ... event)
        noexcept(false) // our `event` (`::std::string`) `constructor` may throw `::std::bad_alloc` in `in_place` mode
    {
        // 1. `dispatch(...)` method supports `in_place` construction
        //    but if `event` argument is convertible to `EventType const &` it should be passed by reference.
        // 2. `dispatch` method throws exceptions only in `in_place` mode if `event constructor` throws something.
        //    if you want `noexcept(true)` here, you should replace `::std::string` (`event`) with `::std::string_view`.
        dispatcher_.dispatch(::std::forward<T>(event) ...);
    }

private:
    // Better to declare `events()` method as `const`.
    mutable ::ap::event::Dispatcher<::std::string> dispatcher_ = {};
};


int main(int argc, char **argv) {
    auto application_ = ::QCoreApplication{argc, argv};

    // Initializing event counter
    auto counter_ = 0;

    // Initializing our asynchronous i/o device
    auto example_ = ::Example_{};

    // A painfully familiar, but so dearly loved phrase by all of us... =)
    constexpr static auto const * const hello_message_ = "Hello, world!";

    ::QTimer::singleShot(0, [&example_] {
        ::std::clog
            << "first ::QTimer::singleShot handler: sending initial event - \"" << hello_message_ << "\"" << ::std::endl
        << ::std::flush;
        example_.send(hello_message_);
    });

    ::QTimer::singleShot(1000, [&example_] {
        ::std::clog
            << "second ::QTimer::singleShot handler: sending `empty event` (should be handled as `stop request`)" << ::std::endl
        << ::std::flush;
        example_.send(); // same as `send(nullptr)` or `send(::std::string{})`
    });

    auto attached_weak_subscription_ = example_.watch([&] (auto &&event) {
        ::std::clog
            << "attached weak subscription: counter = " << counter_
            << ", event = \"" << ::std::forward<decltype(event)>(event) << "\"" << ::std::endl
        << ::std::flush;
        throw ::std::runtime_error{"this exception will be ignored"};
    });

    // all copies of subscription will become `strong` if any of them is increased through `take()` method
    auto first_strong_subscription_ = example_.watch([&] (auto &&) {
        ::std::clog << "strong subscription: counter = " << counter_ << ::std::endl << ::std::flush;
        counter_++;
    }).take(); // <-- we call `take()` here (`*this rvalue` returned, you can `move` it) - now our subscription is `strong`.

    auto second_strong_subscription_ = first_strong_subscription_;

    example_.watch([&] (auto &&event) {
        // handlers should be called in order of `subscribe(...)` calls
        ::std::clog
            << "first detached weak subscription: counter = " << counter_
            << ", event = \"" << event << "\"" << ::std::endl
        << ::std::flush;

        if (attached_weak_subscription_.state()) { // is subscription attached and not expired?
            // explicit `cancel()` method call, because subscription is weak
            attached_weak_subscription_.cancel();
            ::std::clog
                << "first detached weak subscription: attached weak subscription cancelled, handler disabled"
            << ::std::endl << ::std::flush;
            return;
        }

        if (first_strong_subscription_) { // `operator bool` is `state()`
            first_strong_subscription_ = {}; // same effect as `detach()`
            ::std::clog
                << "first detached weak subscription: first strong subscription reference detached, handler still alive"
            << ::std::endl << ::std::flush;
            return;
        }

        if (second_strong_subscription_) {
            // `strong` subscription will be canceled if all copies detached
            second_strong_subscription_.detach();
            ::std::clog
                << "first detached weak subscription: second strong subscription reference detached, handler disabled"
            << ::std::endl << ::std::flush;
        }
    });

    // subscribe via `event source` interface
    example_.events().subscribe([&] (auto const &event) noexcept(false) {
        // `empty event` is our reason for stop
        if (event.empty()) ::QTimer::singleShot(0, [&] {
            // this message will be passed by reference in `zero-copy` mode
            // same behavior if you pass an instance of a derived event (in this case::std::string) class
            example_.send(::std::string{"Bye, DRY!"});
            // ofcourse better to use `::std::decay_t<decltype(test_.events())>::Event` because `DRY`
            example_.send(::std::decay_t<decltype(example_.events())>::Event{"Bye, KISS!"});
            ::std::clog << "second detached weak subscription: shutting down" << ::std::endl << ::std::flush;
            application_.quit();
            return;
        });

        if (hello_message_ == event) {
            example_.send("this is direct recursive call");
            ::QTimer::singleShot(0, [&example_] { example_.send("this is queued loop call"); });
        }
    });

    return application_.exec();
}
