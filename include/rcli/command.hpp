#pragma once

#include <map>
#include <memory>
#include <rcli/option.hpp>
#include <rcli/types.hpp>
#include <string>
#include <vector>

namespace rcli
{
	class Command
	{
	protected:
		std::string _name, _description;
		Callback _callback;
		std::vector<std::shared_ptr<Option>> _options;
		std::vector<std::shared_ptr<Command>> _subcommands;

		std::map<std::string, std::string> _options_values, _informations;

		void parse(int argc, const char *argv[], int start);
		bool is_matched(std::string text);
		bool call_if_matched(std::string text);

		Command() = default;

	public:
		virtual void print_help();

		std::string get_name();
		std::string get_description();
		std::string get_option_value(std::string key);

		void add_option(Option *new_option);
		void add_option(std::string options, std::string description, std::string key_name);
		void add_subcommand(Command *new_command);
		void add_informations(std::map<std::string, std::string> informations);

		Command(std::string name, std::string description, Callback callback);
	};
}  // namespace rcli
