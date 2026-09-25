#include <doctest/doctest.h>

#include <memory>
#include <rcli/rcli.hpp>

#include "helpers.hpp"

using namespace rcli;

namespace
{
	// Exposes the protected parse() so that commands can be tested without an app.
	class testable_command : public command
	{
	public:
		using command::command;
		using command::parse;
	};

	struct recorder
	{
		int calls = 0;
		std::map<std::string, std::string> values;

		auto callback() -> rcli::callback
		{
			return [this](command* c) -> void
			{
				++this->calls;
				this->values = c->get_options_values();
			};
		}
	};

	auto run(testable_command& c, std::initializer_list<std::string> arguments) -> int
	{
		test::args a(arguments);
		return c.parse(a.argc(), a.argv(), 1);
	}
}  // namespace

TEST_CASE("declared options take the next argument as value")
{
	recorder r;
	testable_command c("init", "Init", r.callback());
	c.add_option("-f,--file", "File", "file");
	c.add_option("-t,--test", "Test", "test");

	CHECK(run(c, { "prog", "-f", "a.txt", "--test", "x" }) == 0);
	CHECK(r.calls == 1);
	CHECK(r.values == std::map<std::string, std::string>{ { "file", "a.txt" }, { "test", "x" } });
	CHECK(c.get_option_value("file") == "a.txt");
	CHECK(c.get_option_value("missing").empty());
	CHECK(c.has_option("file"));
	CHECK_FALSE(c.has_option("missing"));
}

TEST_CASE("--name=value syntax")
{
	recorder r;
	testable_command c("init", "Init", r.callback());
	c.add_option("-f,--file", "File", "file");

	CHECK(run(c, { "prog", "--file=a=b.txt", "-dyn=1" }) == 0);
	CHECK(c.get_option_value("file") == "a=b.txt");
	CHECK(c.get_option_value("dyn") == "1");
}

TEST_CASE("undeclared options are stored without their dashes")
{
	recorder r;
	testable_command c("generate", "Generate", r.callback());

	CHECK(run(c, { "prog", "-project_name", "demo", "--author", "me", "-with-dash", "v" }) == 0);
	CHECK(c.get_option_value("project_name") == "demo");
	CHECK(c.get_option_value("author") == "me");
	CHECK(c.get_option_value("with-dash") == "v");
}

TEST_CASE("flags take no value")
{
	recorder r;
	testable_command c("build", "Build", r.callback());
	c.add_flag("-V,--verbose", "Verbose", "verbose");
	c.add_option("-o,--output", "Output", "output");

	CHECK(run(c, { "prog", "--verbose", "-o", "out" }) == 0);
	CHECK(c.get_option_value("verbose") == "true");
	CHECK(c.get_option_value("output") == "out");

	testable_command c2("build", "Build", r.callback());
	c2.add_flag("-V,--verbose", "Verbose", "verbose");
	CHECK(run(c2, { "prog", "--verbose=false" }) == 0);
	CHECK(c2.get_option_value("verbose") == "false");

	testable_command c3("build", "Build", r.callback());
	c3.add_flag("-V,--verbose", "Verbose", "verbose");
	CHECK(run(c3, { "prog" }) == 0);
	CHECK_FALSE(c3.has_option("verbose"));
}

TEST_CASE("an option without value prints the help and fails")
{
	recorder r;
	testable_command c("init", "Init", r.callback());
	c.add_option("-f,--file", "File", "file");

	const test::capture_cout out;
	CHECK(run(c, { "prog", "-f" }) == 1);
	CHECK(r.calls == 0);
	CHECK(test::contains(out.str(), "Usage: init [options]"));
}

TEST_CASE("unknown commands and stray arguments print the help and fail")
{
	recorder r;
	testable_command c("hello", "Hello", r.callback());

	const test::capture_cout out;
	CHECK(run(c, { "prog", "nope" }) == 1);
	CHECK(run(c, { "prog", "-n", "bob", "extra" }) == 1);
	CHECK(run(c, { "prog", "--", "x" }) == 1);
	CHECK(r.calls == 0);
}

TEST_CASE("-h / --help print the help without calling the callback")
{
	recorder r;
	testable_command c("hello", "Say hello", r.callback());
	c.add_option("-n,--name", "Your name", "name");

	const test::capture_cout out;
	CHECK(run(c, { "prog", "-n", "bob", "--help" }) == 0);
	CHECK(r.calls == 0);
	const auto help = out.str();
	CHECK(test::contains(help, " Usage: hello [options]\n"));
	CHECK(test::contains(help, " Description: Say hello\n"));
	CHECK(test::contains(help, "\t-n,--name: Your name\n"));
	CHECK(test::contains(help, "\t-h,--help: Show this help\n"));
	CHECK_FALSE(test::contains(help, "\033["));	 // no colors when not writing to a terminal
}

TEST_CASE("subcommands receive the rest of the arguments")
{
	recorder parent_r;
	recorder child_r;
	testable_command parent("tool", "Tool", parent_r.callback());
	command child("child", "Child", child_r.callback());
	child.add_option("-n,--name", "Name", "name");
	parent.add_subcommand(&child);

	CHECK(run(parent, { "prog", "-g", "global", "child", "-n", "bob" }) == 0);
	CHECK(parent_r.calls == 0);
	CHECK(child_r.calls == 1);
	CHECK(child_r.values == std::map<std::string, std::string>{ { "name", "bob" } });
	CHECK(parent.get_option_value("g") == "global");
}

TEST_CASE("nested subcommands and usage path")
{
	recorder r;
	testable_command root("tool", "Tool", r.callback());
	auto remote = std::make_shared<command>("remote", "Remotes", r.callback());
	root.add_subcommand(remote);
	remote->add_subcommand(std::make_shared<command>("add", "Add a remote", r.callback()));

	CHECK(run(root, { "prog", "remote", "add" }) == 0);
	CHECK(r.calls == 1);

	const test::capture_cout out;
	CHECK(run(root, { "prog", "remote", "add", "-h" }) == 0);
	CHECK(test::contains(out.str(), "Usage: tool remote add [options]"));
}

TEST_CASE("add_subcommand(command*) copies, add_subcommand(shared_ptr) shares")
{
	recorder r;
	testable_command root("tool", "Tool", r.callback());

	command copied("copied", "Copied", r.callback());
	root.add_subcommand(&copied);
	copied.add_option("-x,--x", "added after", "x");  // not visible: root holds a copy

	auto shared = std::make_shared<command>("shared", "Shared", r.callback());
	root.add_subcommand(shared);
	shared->add_flag("-y,--y", "added after", "y");	 // visible

	CHECK(root.get_subcommands().at(0)->get_options().size() == 1);	 // only -h
	CHECK(root.get_subcommands().at(1)->get_options().size() == 2);

	CHECK(run(root, { "prog", "shared", "-y" }) == 0);
	CHECK(shared->get_option_value("y") == "true");
}

TEST_CASE("add_option(option*) copies the option, null pointers are ignored")
{
	recorder r;
	option shared_option("-t,--template", "Template", "template_path");
	testable_command a("a", "A", r.callback());
	testable_command b("b", "B", r.callback());
	a.add_option(&shared_option);
	b.add_option(&shared_option);
	a.add_option(nullptr);
	a.add_subcommand(static_cast<command*>(nullptr));

	CHECK(run(a, { "prog", "-t", "x" }) == 0);
	CHECK(run(b, { "prog", "--template", "y" }) == 0);
	CHECK(a.get_option_value("template_path") == "x");
	CHECK(b.get_option_value("template_path") == "y");
	CHECK(a.get_subcommands().empty());
}

TEST_CASE("a command without callback prints its help")
{
	testable_command c("empty", "Empty", nullptr);
	const test::capture_cout out;
	CHECK(run(c, { "prog" }) == 0);
	CHECK(test::contains(out.str(), "Usage: empty [options]"));
}

TEST_CASE("the last value of a repeated option wins")
{
	recorder r;
	testable_command c("c", "C", r.callback());
	CHECK(run(c, { "prog", "-a", "1", "-a", "2" }) == 0);
	CHECK(c.get_option_value("a") == "2");
}
