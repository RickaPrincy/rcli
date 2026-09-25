#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

// Including the library in several translation units of the same binary checks that
// every function defined in the headers is `inline` (no multiple definition errors).
#include <rcli/rcli.hpp>
#include <string>

TEST_CASE("version macro matches its parts")
{
	CHECK(std::string(RCLI_VERSION) == std::to_string(RCLI_VERSION_MAJOR) + "." +
										   std::to_string(RCLI_VERSION_MINOR) + "." +
										   std::to_string(RCLI_VERSION_PATCH));
}
