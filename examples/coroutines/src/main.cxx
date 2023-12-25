#include <thread>
#include <iostream>
#include <stdexcept>
#include <coroutine>

#include <ap.hxx>


namespace example_ {

inline static auto switch_to_new_thread_(::std::jthread &out) noexcept(true) {
    struct Awaitable_ final {
        ::std::jthread *p_out;

        inline constexpr static auto await_ready() noexcept(true) { return false; }

        inline auto await_suspend(::std::coroutine_handle<> const &h) const noexcept(false) {
            ::std::jthread &out = *p_out;
            if (out.joinable()) throw ::std::runtime_error("Output jthread parameter not empty");
            out = ::std::jthread([h] { h.resume(); });
            // Potential undefined behavior: accessing potentially destroyed *this
            // ::std::clog << "New thread ID: " << p_out->get_id() << ::std::endl << ::std::flush;
            ::std::clog << "New thread ID: " << out.get_id() << ::std::endl << ::std::flush; // this is OK
        }

        inline constexpr static auto await_resume() noexcept(true) {}
    };

    return Awaitable_{&out};
}

struct Task_ final { struct promise_type final {
    inline constexpr static auto get_return_object() noexcept(true) { return Task_{}; }
    inline constexpr static auto initial_suspend() noexcept(true) { return ::std::suspend_never{}; }
    inline constexpr static auto final_suspend() noexcept(true) { return ::std::suspend_never{}; }
    inline constexpr static auto return_void() noexcept(true) {}
    inline constexpr static auto unhandled_exception() noexcept(true) {}
}; };

Task_ run(::std::jthread &out) {
    ::std::clog << "Coroutine started on thread: " << ::std::this_thread::get_id() << ::std::endl << ::std::flush;
    co_await switch_to_new_thread_(out);
    // awaiter destroyed here
    ::std::clog << "Coroutine resumed on thread: " << ::std::this_thread::get_id() << ::std::endl << ::std::flush;
    throw ::std::runtime_error{"not implemented yet"};
}

} // namespace example_


int main(int, char **) {
    ::std::cerr << "WARNING: Not implemented yet." << ::std::endl << ::std::flush;
    ::std::clog << "This is still not a real example - it's a stub." << ::std::endl << ::std::flush;
    ::std::clog << "Follow https://en.cppreference.com/w/cpp/language/coroutines" << ::std::endl << ::std::flush;

    ::std::jthread out;
    ::example_::run(out);

    return 0;
}
