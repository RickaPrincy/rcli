#ifndef __RCLI_UTILS__
#define __RCLI_UTILS__

#include <numeric>
#include <sstream>
#include <string>
#include <vector>

namespace rcli {
    template <typename T>
    std::string join(const T &values, std::string separator) {
        return std::accumulate(values.begin(), values.end(), std::to_string(*values.begin()),
            [&separator](const auto &a, const auto &b) {
                std::ostringstream oss;
                oss << a << separator << b;
                return oss.str();
            });
    }
}  // namespace rcli

#endif  // !__RCLI_UTILS__
