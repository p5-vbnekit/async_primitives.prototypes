#pragma once

#include "this_.hxx"

#include "source/base.fwd.hxx"


namespace ap::event {
namespace source {

template <class = void> struct Type;

namespace policy {

namespace parent_ = this_;
namespace this_ = parent_::policy;

struct Type;

} // namespace policy

using Policy = policy::Type;

} // namespace source

template <class ... T> using Source = source::Type<T ...>;

} // namespace ap::event
