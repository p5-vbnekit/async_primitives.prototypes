#pragma once

#include "this_.hxx"


namespace ap::event {
inline namespace this_ {
namespace dispatcher {
namespace parent_ = this_;
inline namespace this_ {
namespace parent_ = parent_;

template <class = void> struct Type;

namespace policy_ {
namespace parent_ = this_;
inline namespace this_ {
namespace parent_ = parent_;

struct Type;

} // inline namespace this_
} // namespace policy_

using Policy_ = policy_::Type;

} // inline namespace this_
} // namespace dispatcher

template <class ... T> using Dispatcher = dispatcher::Type<T ...>;

} // inline namespace this_
} // namespace ap::event
