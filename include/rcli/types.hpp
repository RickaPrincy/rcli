#pragma once

#include <functional>

namespace rcli {
class Command;

using Callback = std::function<void(Command *)>;
} // namespace rcli
