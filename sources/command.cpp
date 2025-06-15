#include <iostream>
#include <rcli/command.hpp>

#include "utils.hpp"

namespace rcli
{
	command::command(std::string name, std::string description, callback callback)
		: m_name(std::move(name)),
		  m_description(std::move(description)),
		  m_callback(std::move(callback))
	{
		this->add_option("-h,--help", "Show this help", "help");
	}

	auto command::get_name() const -> const std::string &
	{
		return this->m_name;
	}

	auto command::get_description() const -> const std::string &
	{
		return this->m_description;
	}

	auto command::call_if_match(const std::string &text) -> bool
	{
		if (this->match(text))
		{
			this->m_callback(this);
			return true;
		}
		return false;
	}

	auto command::match(const std::string &text) -> bool
	{
		return this->m_name == text;
	}

	auto command::print_help() -> void
	{
		utils::print_as_key_value(" Usage", this->m_name + " <sub_command> <option option_value>");
		utils::print_as_key_value(" Description", this->m_description);

		std::cout << color::b_white << "\n Options:\n" << color::reset;
		for (const auto &option : this->m_options)
		{
			utils::print_as_key_value("\t" + option->get_base_name(), option->get_description());
		}

		if (!this->m_subcommands.empty())
		{
			std::cout << color::b_white << "\n Commands:\n" << color::reset;
			for (const auto &command : this->m_subcommands)
			{
				utils::print_as_key_value("\t" + command->get_name(), command->get_description());
			}
		}
	}

	auto command::add_option(std::string options, std::string description, std::string key_name)
		-> void
	{
		this->m_options.push_back(std::make_shared<option>(
			std::move(options), std::move(description), std::move(key_name)));
	}

	auto command::add_option(option *new_option) -> void
	{
		this->m_options.push_back(std::make_shared<option>(*new_option));
	}

	auto command::add_subcommand(command *new_command) -> void
	{
		this->m_subcommands.push_back(std::make_shared<command>(*new_command));
	}

	auto command::get_option_value(const std::string &key) -> std::string
	{
		if (this->m_options_values.find(key) == this->m_options_values.end())
		{
			return "";
		}
		return this->m_options_values.at(key);
	}

	void command::add_informations(std::map<std::string, std::string> informations)
	{
		const auto moved = std::move(informations);
		for (const auto &info : moved)
		{
			this->m_informations.insert(info);
		}
	}

	void command::parse(int argc,
		const char *argv[],	 // NOLINT(modernize-avoid-c-arrays),
		int start)
	{
		if (start >= argc)
		{
			this->m_callback(this);
			return;
		}

		std::string current_action = argv[start];
		if (current_action == "-h" || current_action == "--help")
		{
			print_help();
			return;
		}

		if (current_action.find(std::string("-")) == 0)
		{
			if (start + 1 >= argc)
			{
				print_help();
				return;
			}

			for (const auto &option : this->m_options)
			{
				std::string key_name = option->get_key_if_matched(current_action);
				if (key_name.empty())
				{
					continue;
				}
				else
				{
					this->m_options_values.insert(std::make_pair(key_name, argv[start + 1]));
				}

				parse(argc, argv, start + 2);
				return;
			}
			current_action.erase(0, 1);
			this->m_options_values.insert(std::make_pair(current_action, argv[start + 1]));
			parse(argc, argv, start + 2);
			return;
		}

		for (const auto &command : this->m_subcommands)
		{
			if (command->match(current_action))
			{
				command->parse(argc, argv, start + 1);
				return;
			}
		}

		print_help();
		return;
	}
}  // namespace rcli
