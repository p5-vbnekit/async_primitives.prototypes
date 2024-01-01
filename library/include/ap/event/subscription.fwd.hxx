#pragma once

#include "this_.hxx"


namespace ap::event {
namespace subscription {

namespace parent_ = this_;
namespace this_ = parent_::subscription;

struct Type;

namespace storage {

namespace parent_ = this_;
namespace this_ = parent_::storage;

namespace entry {

namespace parent_ = this_;
namespace this_ = parent_::entry;

struct Type;

} // namespace entry

using Entry = entry::Type;

} // namespace storage
} // namespace subscription

using Subscription = subscription::Type;

} // namespace ap::event
