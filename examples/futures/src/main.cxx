#include <cstdint>

#include <string>
#include <iostream>
#include <stdexcept>
#include <string_view>
#include <type_traits>

#include <QTimer>
#include <QCoreApplication>

#include <ap.hxx>


namespace example_ {

#if 0
inline static auto parse_age(::std::string_view const &) noexcept(false) {
    return static_cast<::std::size_t>(0);
}

inline static auto validate_name(::std::string &) noexcept(false) {
    return false;
}

inline static auto validate_language(::std::string const &) noexcept(false) {
    return false;
}
#endif

} // namespace example_


int main(int argc, char **argv) {
    auto application_ = ::QCoreApplication{argc, argv};

#if 0
    ::ap::Promise<::std::string> initial_promise_;

    auto const final_future_ = promise_.then([
        &future_ = ::ap::future::from_promise(initial_promise_)
    ] {
        struct Data_ {
            ::std::decay_t<decltype(future.get())> name;
        } data_ {.name = ::std::move(future.get())};

        try {
            if (example_::validate_name_(data_.name)) ::std::clog
                << "your name modified to \"" << data_.name << "\""
            << ::std::endl << ::std::flush;
        }

        catch(...) { return ::ap::future::from_exception(::std::current_exception()); }

        return ::ap::future::from_value(::std::move(data_));

    }) >> [] (auto &&future) {
        struct Data_ {
            ::std::size_t age;
            ::std::decay_t<decltype(future.get())> name;
        } data_ {.name = ::std::move(future.get().name)};

        ::std::clog << "Hello, " << data_.name << "!" << ::std::endl << ::std::flush;

        if constexpr(true) {
            ::std::string text_;
            ::std::clog << "Enter your age: " << ::std::flush;
            ::std::getline(::std::cin, text_);
            data_.age = example_::parse_age(::std::move(text_));
        }

        return ::ap::future::from_value(::std::move(data_));
    } >> [&] (auto &&future) {
        struct Data_: ::std::decay_t<decltype(future.get())> {
            ::std::string language;
        };

        ::ap::Promise<Data_> promise_;

        ::QTimer::singleShot(0, [promise_, future_ = ::std::move(future)] { promise_ << Data_({
            .age = future.get().age,
            .name = ::std::move(future.get().name),
            .language = [] {
                ::std::string text_;
                ::std::clog << "Enter your preferred programming language: " << ::std::flush;
                ::std::getline(::std::cin, text_);
                if (example_::validate_language(text_)) ::std::clog
                    << "preferred programming language interpreted as \"" << text_ << "\""
                << ::std::end << ::std::flush;
                return ::std::move(text_);
            } ()
        }); });

        return promise_;
    } >> [] (auto &future) {
        auto &&data_ = ::std::move(future.get());
        ::std::clog << "Bye, " << ::std::move(data_.name) << " - " << data_.age << " years old"
            << " " << ::std::move(data_.language) << " programmer!"
        << ::std::endl << ::std::flush;
    } >> [&application_] { application_.quit(); } >> [] (auto const &future) { future.get(); };

    ::QTimer::singleShot(0, [&promise_ = initial_promise_] {
        try {
            ::std::clog << "Hello, world!" << ::std::endl << ::std::flush;
            ::std::string name_;
            ::std::clog << "Enter your name: " << ::std::flush;
            ::std::getline(::std::cin, data_.name);
            promise_ << ::std::move(name_);
        } catch (...) { promise_.set_exception(::std::current_exception()); }
    });
#endif

    auto const exit_code_ = application_.exec();

#if 0
    if (! final_future_.ready()) throw ::std::logic_error{"future is not ready"};

    if (final_future_.exception()) {
        final_future_.get();
        throw ::std::logic_error{"future exception expected"};
    }
#endif

    return exit_code_;
}
