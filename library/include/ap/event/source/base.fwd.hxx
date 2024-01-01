#pragma once

#include "this_.hxx"


namespace ap::event::source {
namespace base {

namespace parent_ = this_;
namespace this_ = parent_::base;

struct Type;

} // namespace base

using Base = base::Type;

} // namespace ap::event::source
