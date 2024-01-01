#pragma once

#include "this_.hxx"


namespace ap::event {
namespace dispatcher {

namespace parent_ = this_;
namespace this_ = parent_::dispatcher;

template <class = void> struct Type;

namespace policy_ {

namespace parent_ = this_;
namespace this_ = parent_::policy_;

struct Type;

} // namespace policy_

using Policy_ = policy_::Type;

} // namespace dispatcher

template <class ... T> using Dispatcher = dispatcher::Type<T ...>;

} // namespace ap::event
