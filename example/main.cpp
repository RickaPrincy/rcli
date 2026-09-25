#include <iostream>
#include <rcli/rcli.hpp>

using namespace rcli;

auto main(int argc, const char* argv[]) -> int
{
	app example("example", "Generate cool application", "1.9.5");
	example.add_informations(
		{ { "Author", "RickaPrincy" }, { "Github", "https://github.com/RickaPrincy/rcli" } });

	command init("init",
		"init new project",
		[](command* _init) -> void
		{
			std::cout << "file value: " << _init->get_option_value("file") << "\n";
			std::cout << "test value: " << _init->get_option_value("test") << "\n";
			std::cout << "force: " << (_init->has_option("force") ? "yes" : "no") << "\n";
			// undeclared options work too: `example init --author me`
			std::cout << "author: " << _init->get_option_value("author") << "\n";
		});

	init.add_option("-f,--file", "Specify file name", "file");
	init.add_option("-t,--test", "test test", "test");
	init.add_flag("--force", "Overwrite existing files", "force");

	command hello("hello",
		"say hello",
		[](command* _hello) -> void
		{ std::cout << "Hello " << _hello->get_option_value("name") << "\n"; });

	hello.add_option("-n,--name", "Specify your name", "name");

	example.add_subcommand(&init);
	example.add_subcommand(&hello);

	return example.run(argc, argv);
}
