#include <iostream>
#include <string_view>

#include <QTimer>
#include <QCoreApplication>

#include <ap.hxx>


int main(int argc, char **argv) {
    auto application_ = ::QCoreApplication{argc, argv};

    // Initializing asynchronous event dispatcher
    auto dispatcher_ = ::ap::event::Dispatcher<::std::string_view>{};

    // Attaching first device event handler for text messages
    dispatcher_.subscribe([] (auto const &event) {
        ::std::clog << event << ::std::endl << ::std::flush;
    });

    // Sending events
    ::QTimer::singleShot(0, [&dispatcher_] { dispatcher_.dispatch("Hello, world!"); });
    ::QTimer::singleShot(0, [&dispatcher_] { dispatcher_.dispatch("Check out `hard` and `nightmare` examples, noob. =)"); });
    ::QTimer::singleShot(0, ::QCoreApplication::quit);

    // Run it!
    return application_.exec();
}
