#include <iostream>
#include <rcli/rcli.hpp>

using namespace rcli;

auto main(int argc, const char *argv[]) -> int
{
	app templi("example", "Generate cool application", "1.9.5");
	templi.add_informations(
		{ { "Author", "RickaPrincy" }, { "Github", "https://github.com/RickaPrincy/rcli" } });

	command init("init",
		"init new project",
		[](command *_init)
		{
			std::cout << "file value: " << _init->get_option_value("file") << "\n";
			std::cout << "another: " << _init->get_option_value("another") << "\n";
			std::cout << "another-value: " << _init->get_option_value("another-value") << "\n";
			std::cout << "test value: " << _init->get_option_value("test") << "\n";
		});

	init.add_option("-f,--file", "Specify file name", "file");
	init.add_option("-t,--test", "test test", "test");

	command hello("hello",
		"say hello",
		[&](command *_hello)
		{ std::cout << "Hello  " << _hello->get_option_value("name") << "\n"; });

	hello.add_option("-n,--name", "Specify your name", "name");

	templi.add_subcommand(&init);
	templi.add_subcommand(&hello);

	return templi.run(argc, argv);
}
