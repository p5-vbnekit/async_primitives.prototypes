#pragma once

#include "this_.hxx"

#include "source/base.fwd.hxx"


namespace ap::event {
inline namespace this_ {
namespace source {
inline namespace this_ {

template <class = void> struct Type;

namespace policy {
inline namespace this_ {

struct Type;

} // inline namespace policy
} // namespace policy

using Policy = policy::Type;

} // inline namespace this_
} // namespace source

template <class ... T> using Source = source::Type<T ...>;

} // inline namespace this_
} // namespace ap::event
