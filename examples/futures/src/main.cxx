#include <stdexcept>

#include <QCoreApplication>

#include <ap.hxx>


namespace example_ {

inline static auto stub() noexcept(false) { throw ::std::runtime_error{"not implemented yet"}; }

} // namespace example_


int main(int argc, char **argv) {
    auto application_ = ::QCoreApplication{argc, argv};
    ::example_::stub();
    return application_.exec();
}
