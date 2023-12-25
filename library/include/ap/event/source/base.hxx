#pragma once

#include "base.fwd.hxx"


namespace ap::event::source::base {
inline namespace this_ {

struct Type {
    virtual ~Type();

protected:
    Type() = default;
    Type(Type &&) = default;
    Type & operator = (Type &&) = default;

private:
    Type(Type const &) = delete;
    Type & operator = (Type const &) = delete;
};

} // inline namespace this_
} // namespace ap::event::source::base
