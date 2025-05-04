#include <TColor/TColor.hpp>
#include <memory>
#include <rcli/color_config.hpp>
#include <rcli/command.hpp>
#include <utility>

#include "utils/utils.hpp"

using namespace rcli;

Command::Command(std::string name, std::string description, Callback callback)
{
	_name = name;
	_description = description;
	_callback = callback;
	add_option("-h,--help", "Show this help", "help");
}

std::string Command::get_name()
{
	return _name;
}

std::string Command::get_description()
{
	return _description;
}

bool Command::call_if_matched(std::string text)
{
	if (is_matched(text))
	{
		_callback(this);
		return true;
	}
	return false;
}

bool Command::is_matched(std::string text)
{
	return text == _name;
}

void Command::print_help()
{
	Utils::print_as_key_value(" Usage", _name + " <sub_command> <option option_value>");
	Utils::print_as_key_value(" Description", _description);

	TColor::write(ColorConfig::key, "\n Options:\n");
	for (const auto option : _options)
	{
		Utils::print_as_key_value("\t" + option->get_base_names(), option->get_description());
	}

	if (!_subcommands.empty())
	{
		TColor::write(ColorConfig::key, "\n Commands:\n");
		for (const auto command : _subcommands)
		{
			Utils::print_as_key_value("\t" + command->get_name(), command->get_description());
		}
	}
}

void rcli::Command::add_option(std::string options, std::string description, std::string key_name)
{
	_options.push_back(std::make_shared<rcli::Option>(options, description, key_name));
}

void rcli::Command::add_option(Option *new_option)
{
	_options.push_back(std::make_shared<Option>(*new_option));
}

void rcli::Command::add_subcommand(Command *new_command)
{
	_subcommands.push_back(std::make_shared<Command>(*new_command));
}

std::string Command::get_option_value(std::string key)
{
	if (_options_values.find(key) == _options_values.end())
	{
		return "";
	}
	return _options_values.at(key);
}

void Command::add_informations(std::map<std::string, std::string> informations)
{
	for (const auto &info : informations)
		_informations.insert(info);
}

void rcli::Command::parse(int argc, const char *argv[], int start)
{
	if (start >= argc)
	{
		_callback(this);
		return;
	}

	std::string current_action = argv[start];
	if (current_action == "-h" || current_action == "--help")
	{
		print_help();
		return;
	}

	if (current_action.find("-") == 0)
	{
		if (start + 1 >= argc)
		{
			print_help();
			return;
		}

		for (const auto option : _options)
		{
			std::string key_name = option->get_key_if_matched(current_action);
			if (key_name.empty())
			{
				current_action.erase(0, 1);
				_options_values.insert(std::make_pair(current_action, argv[start + 1]));
			}
			else
			{
				_options_values.insert(std::make_pair(key_name, argv[start + 1]));
			}
			parse(argc, argv, start + 2);
			return;
		}

		print_help();
		return;
	}

	for (const auto command : _subcommands)
	{
		if (command->is_matched(current_action))
		{
			command->parse(argc, argv, start + 1);
			return;
		}
	}

	print_help();
	return;
}
