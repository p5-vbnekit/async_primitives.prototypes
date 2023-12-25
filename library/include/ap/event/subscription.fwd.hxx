#pragma once

#include "this_.hxx"


namespace ap::event {
inline namespace this_ {
namespace subscription {
namespace parent_ = this_;
inline namespace this_ {
namespace parent_ = parent_;

struct Type;

namespace storage {
namespace parent_ = this_;
inline namespace this_ {
namespace parent_ = parent_;
namespace entry {
namespace parent_ = this_;
inline namespace this_ {
namespace parent_ = parent_;

struct Type;

} // inline namespace this_
} // namespace entry

using Entry = entry::Type;

} // inline namespace this_
} // namespace storage
} // inline namespace this_
} // namespace subscription

using Subscription = subscription::Type;

} // inline namespace this_
} // namespace ap::event
