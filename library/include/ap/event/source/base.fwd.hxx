#pragma once

#include "this_.hxx"


namespace ap::event::source {
inline namespace this_ {
namespace base {
namespace parent_ = this_;
inline namespace this_ {
namespace parent_ = parent_;

struct Type;

} // inline namespace this_
} // namespace base

using Base = base::Type;

} // inline namespace this_
} // namespace ap::event::source
