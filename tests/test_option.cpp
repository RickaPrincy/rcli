#include <doctest/doctest.h>

#include <rcli/rcli.hpp>

using namespace rcli;

TEST_CASE("option names are split on commas and trimmed")
{
	const option o("-s, --scope", "Scope", "scope");
	CHECK(o.get_names() == std::vector<std::string>{ "-s", "--scope" });
	CHECK(o.get_base_name() == "-s, --scope");
	CHECK(o.get_description() == "Scope");
	CHECK(o.get_key_name() == "scope");
	CHECK_FALSE(o.is_flag());
}

TEST_CASE("get_key_if_matched")
{
	const option o("-f,--file", "File", "file");
	CHECK(o.get_key_if_matched("-f") == "file");
	CHECK(o.get_key_if_matched("--file") == "file");
	CHECK(o.get_key_if_matched("-file").empty());
	CHECK(o.get_key_if_matched("f").empty());
}

TEST_CASE("flag options")
{
	const option o("-V,--verbose", "Verbose", "verbose", true);
	CHECK(o.is_flag());
	CHECK(o.matches("--verbose"));
}
