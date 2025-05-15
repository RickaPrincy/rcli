#include <iostream>
#include <rcli/rcli.hpp>

using namespace rcli;

void ask_gender()
{
	std::string gender = ask_value_in_list_as_number("What is your gender", { "M", "F" });
	std::cout << "your gender is : " << gender << std::endl;
}

int main(int argc, const char *argv[])
{
	ColorConfig::key = TColor::B_GREEN;

	InputConfig config = InputConfig()
							 .text("What your name")
							 .clean(false)
							 .required(true)
							 .default_value("RickaPrincy");

	App templi("example", "Generate cool application", "1.9.5");
	templi.add_informations(
		{ { "Author", "RickaPrincy" }, { "Github", "https://github.com/RickaPrincy/rcli" } });

	Command init("init",
		"init new project",
		[](Command *_init)
		{
			std::cout << "file value: " << _init->get_option_value("file") << std::endl;
			std::cout << "another: " << _init->get_option_value("another") << std::endl;
			std::cout << "another-value: " << _init->get_option_value("another-value") << std::endl;
			std::cout << "test value: " << _init->get_option_value("test") << std::endl;
		});

	init.add_option("-f,--file", "Specify file name", "file");
	init.add_option("-t,--test", "test test", "test");

	Command hello("hello",
		"say hello",
		[&](Command *_hello)
		{
			std::string name = _hello->get_option_value("name");
			if (name.empty())
			{
				name = ask_input_value(config);
			}

			ask_gender();
			std::cout << "Hello  " << name << std::endl;
		});

	hello.add_option("-n,--name", "Specify your name", "name");

	templi.add_subcommand(&init);
	templi.add_subcommand(&hello);
	templi.run(argc, argv);
	return 0;
}
