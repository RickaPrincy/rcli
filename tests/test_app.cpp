#include <doctest/doctest.h>

#include <rcli/rcli.hpp>

#include "helpers.hpp"

using namespace rcli;

namespace
{
	auto make_app() -> app
	{
		app a("example", "Generate cool application", "1.9.5");
		a.add_informations({ { "Author", "RickaPrincy" } });
		return a;
	}
}  // namespace

TEST_CASE("constructor takes name, description, version")
{
	const auto a = make_app();
	CHECK(a.get_name() == "example");
	CHECK(a.get_description() == "Generate cool application");
	CHECK(a.get_version() == "1.9.5");
}

TEST_CASE("-v / --version print the version and the informations")
{
	for (const auto* flag : { "-v", "--version" })
	{
		auto a = make_app();
		test::args args{ "example", flag };
		const test::capture_cout out;
		CHECK(a.run(args.argc(), args.argv()) == 0);
		CHECK(out.str() ==
			  " Name: example\n"
			  " Version: 1.9.5\n"
			  " Description: Generate cool application\n"
			  " Author: RickaPrincy\n");
	}
}

TEST_CASE("without arguments the help is printed")
{
	auto a = make_app();
	a.add_subcommand(std::make_shared<command>("init", "init new project", nullptr));
	test::args args{ "example" };
	const test::capture_cout out;
	CHECK(a.run(args.argc(), args.argv()) == 0);
	CHECK(test::contains(out.str(), " Usage: example <command> [options]\n"));
	CHECK(test::contains(out.str(), "\t-v,--version: Show the version\n"));
	CHECK(test::contains(out.str(), " Commands:\n\tinit: init new project\n"));
}

TEST_CASE("run dispatches to subcommands and returns the exit code")
{
	auto a = make_app();
	std::string received;
	command hello(
		"hello", "say hello", [&](command* c) -> void { received = c->get_option_value("name"); });
	hello.add_option("-n,--name", "Your name", "name");
	a.add_subcommand(&hello);

	test::args ok{ "example", "hello", "--name", "bob" };
	CHECK(a.run(ok.argc(), ok.argv()) == 0);
	CHECK(received == "bob");

	const test::capture_cout out;
	test::args unknown{ "example", "nope" };
	CHECK(a.run(unknown.argc(), unknown.argv()) == 1);
}

TEST_CASE("run accepts a non-const argv")
{
	auto a = make_app();
	std::string program = "example";
	std::string flag = "--version";
	char* argv[] = { program.data(), flag.data(), nullptr };  // NOLINT(modernize-avoid-c-arrays)
	const test::capture_cout out;
	CHECK(a.run(2, argv) == 0);
	CHECK(test::contains(out.str(), "Version: 1.9.5"));
}
