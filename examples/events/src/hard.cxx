#include <cstdint>

#include <string>
#include <variant>
#include <utility>
#include <iostream>
#include <charconv>
#include <functional>
#include <string_view>
#include <type_traits>
#include <system_error>

#include <QTimer>
#include <QCoreApplication>

#include <ap.hxx>


namespace example_ {

// We use 2 event types:
// - `Text` - will be printed to ::std::clog by first event handler
// - `Action` - will be called by second event handler
using Text = ::std::string_view;
using Action = ::std::function<void(void)>;
using Event = ::std::variant<Text, Action>;
using Dispatcher = ::ap::event::Dispatcher<Event>;

// Delayed (via `::QTimer::singleShot`) dispatch wrapper
struct Post final {
    template <class DelayType, class EventType> inline
    auto operator () (DelayType &&delay, EventType &&event) const noexcept(false) {
        ::QTimer::singleShot(::std::forward<DelayType>(delay), [
            this, event_ = ::std::forward<EventType>(event)
        ] { dispatcher_.dispatch(::std::move(event_)); });
    }

    template <class EventType> inline
    auto operator () (EventType &&event) const noexcept(false) {
        return (*this)(0, ::std::forward<EventType>(event));
    }

    inline explicit Post(Dispatcher &dispatcher) noexcept(true): dispatcher_{dispatcher} {}

    Post(Post &&) = default;
    Post(Post const &) = default;

private:
    Post() = delete;

    Dispatcher &dispatcher_;
};

inline static auto ask_delay() noexcept(false) {
    using Value_ = int;
    constexpr static auto const min_ = static_cast<Value_>(0);
    constexpr static auto const max_ = (
        ::std::numeric_limits<Value_>::max() / 1000
    );
    static_assert(min_ < max_);
    ::std::cout << "Enter delay in seconds [" << min_ << ", " << max_ << "]: " << ::std::flush;
    ::std::string text_;
    ::std::getline(::std::cin, text_);
    if (text_.empty()) return -1;
    auto const begin_ = text_.data();
    auto const end_ = begin_ + text_.size();
    Value_ value_;
    auto const parsed_ = ::std::from_chars(
        text_.data(), text_.data() + text_.size(), value_
    );
    if (::std::errc{} != parsed_.ec) return -1;
    if (end_ != parsed_.ptr) return -1;
    if (min_ > value_) return -1;
    if (max_ < value_) return -1;
    return 1000 * value_;
};

} // namespace example_


int main(int argc, char **argv) {
    auto application_ = ::QCoreApplication{argc, argv};

    // Initializing asynchronous event dispatcher
    auto dispatcher_ = ::example_::Dispatcher{};

    // Initializing delayed dispatch wrapper
    auto const post_ = example_::Post{dispatcher_};

    // Attaching first device event handler for text messages
    dispatcher_.subscribe([] (auto const &event) {
        if (! ::std::holds_alternative<example_::Text>(event)) return;
        ::std::clog << ::std::get<example_::Text>(event) << ::std::endl << ::std::flush;
    });

    // Attaching second device event handler for callable actions
    dispatcher_.subscribe([] (auto const &event) {
        if (! ::std::holds_alternative<example_::Action>(event)) return;
        auto const &action_ = ::std::get<example_::Action>(event);
        if (action_) action_();
    });

    // Let's make mini state machine now

    ::std::string name_;

    post_([&] {
        dispatcher_.dispatch("Hello, world!");

        dispatcher_.dispatch([&name_] {
            ::std::clog << "Enter your name: " << ::std::flush;
            ::std::getline(::std::cin, name_);
        });

        if (name_.empty()) name_ = "unnamed";
    });

    post_([&] { dispatcher_.dispatch("Hello, " + name_ + "!"); });

    example_::Action iteration_;

    post_(iteration_ = [&] {
        auto delay_ = example_::ask_delay();

        if (0 == delay_) return post_([&] {
            dispatcher_.dispatch("Bye, " + name_ + "!");
            post_("Now try `nightmare` example!");
            post_([&] { application_.quit(); });
        });

        if (0 < delay_) post_(
            "I'm waiting for " + ::std::to_string(delay_ / 1000) + " seconds now..."
        );

        else delay_ = 0;

        post_(delay_, iteration_);
    });

    // Run it!
    return application_.exec();
}
