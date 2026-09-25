#pragma once

#include <functional>
#include <iostream>
#include <map>
#include <memory>
#include <optional>
#include <string>
#include <utility>
#include <vector>

#include "detail.hpp"
#include "option.hpp"

namespace rcli
{
	class command;

	using callback = std::function<void(command*)>;

	// A command with its options and subcommands. When the command line reaches it, its callback
	// is called with the command itself, so the callback can read the option values.
	//
	// Command line syntax handled by parse():
	//   -f value / --file value / --file=value   declared option (add_option)
	//   -v / --verbose                           declared flag, value "true" (add_flag)
	//   -anything value / --anything value       undeclared option, stored under "anything"
	//   -h / --help                              prints the help of the current command
	//   name                                     runs the subcommand `name` with the rest
	class command
	{
	protected:
		callback m_callback{};
		std::string m_name{}, m_description{};
		std::vector<std::shared_ptr<option>> m_options{};
		std::vector<std::shared_ptr<command>> m_subcommands{};
		std::map<std::string, std::string> m_options_values{}, m_informations{};
		std::string m_usage_path{};	 // e.g. "app init", set while parsing

		[[nodiscard]] auto match(const std::string& text) const -> bool
		{
			return this->m_name == text;
		}

		auto call_if_match(const std::string& text) -> bool
		{
			if (!this->match(text))
			{
				return false;
			}
			this->invoke();
			return true;
		}

		auto invoke() -> void
		{
			if (this->m_callback)
			{
				this->m_callback(this);
			}
			else
			{
				this->print_help();
			}
		}

		[[nodiscard]] auto find_option(const std::string& name) const -> const option*
		{
			for (const auto& current : this->m_options)
			{
				if (current->matches(name))
				{
					return current.get();
				}
			}
			return nullptr;
		}

		// Parses argv[start..argc). Returns 0 on success (or help), 1 on invalid input
		// (unknown command, missing option value), after printing the help.
		// NOLINTNEXTLINE(modernize-avoid-c-arrays)
		auto parse(int argc, const char* argv[], int start) -> int
		{
			int i = start;
			while (i < argc)
			{
				const std::string arg = argv[i] == nullptr ? "" : argv[i];
				if (arg == "-h" || arg == "--help")
				{
					this->print_help();
					return 0;
				}

				if (!detail::is_option(arg))
				{
					for (const auto& subcommand : this->m_subcommands)
					{
						if (subcommand->match(arg))
						{
							subcommand->m_usage_path =
								this->usage_path() + " " + subcommand->m_name;
							return subcommand->parse(argc, argv, i + 1);
						}
					}
					this->print_help();
					return 1;
				}

				std::string name = arg;
				std::optional<std::string> inline_value;
				if (const auto equal = arg.find('='); equal != std::string::npos)
				{
					name = arg.substr(0, equal);
					inline_value = arg.substr(equal + 1);
				}

				const auto* declared = this->find_option(name);
				const auto key =
					declared != nullptr ? declared->get_key_name() : detail::strip_dashes(name);
				if (key.empty())
				{
					this->print_help();
					return 1;
				}

				if (declared != nullptr && declared->is_flag())
				{
					this->m_options_values[key] = inline_value.value_or("true");
					++i;
					continue;
				}

				if (inline_value)
				{
					this->m_options_values[key] = *inline_value;
					++i;
					continue;
				}

				if (i + 1 >= argc)
				{
					this->print_help();
					return 1;
				}
				this->m_options_values[key] = argv[i + 1] == nullptr ? "" : argv[i + 1];
				i += 2;
			}

			this->invoke();
			return 0;
		}

		[[nodiscard]] auto usage_path() const -> std::string
		{
			return this->m_usage_path.empty() ? this->m_name : this->m_usage_path;
		}

		command() = default;

	public:
		command(std::string name, std::string description, callback on_run)
			: m_callback(std::move(on_run)),
			  m_name(std::move(name)),
			  m_description(std::move(description))
		{
			this->add_option("-h,--help", "Show this help", "help");
		}

		command(const command&) = default;
		command(command&&) = default;
		auto operator=(const command&) -> command& = default;
		auto operator=(command&&) -> command& = default;
		virtual ~command() = default;

		virtual auto print_help() -> void
		{
			auto usage = this->usage_path();
			if (!this->m_subcommands.empty())
			{
				usage += " <command>";
			}
			usage += " [options]";
			detail::print_as_key_value(std::cout, " Usage", usage);
			detail::print_as_key_value(std::cout, " Description", this->m_description);

			detail::print_title(std::cout, " Options:");
			for (const auto& current : this->m_options)
			{
				detail::print_as_key_value(
					std::cout, "\t" + current->get_base_name(), current->get_description());
			}

			if (!this->m_subcommands.empty())
			{
				detail::print_title(std::cout, " Commands:");
				for (const auto& subcommand : this->m_subcommands)
				{
					detail::print_as_key_value(
						std::cout, "\t" + subcommand->get_name(), subcommand->get_description());
				}
			}
		}

		[[nodiscard]] auto get_name() const -> const std::string&
		{
			return this->m_name;
		}

		[[nodiscard]] auto get_description() const -> const std::string&
		{
			return this->m_description;
		}

		// Value given on the command line for `key`, "" when absent. Flags are "true" when present.
		[[nodiscard]] auto get_option_value(const std::string& key) const -> std::string
		{
			const auto it = this->m_options_values.find(key);
			return it == this->m_options_values.end() ? "" : it->second;
		}

		[[nodiscard]] auto has_option(const std::string& key) const -> bool
		{
			return this->m_options_values.count(key) != 0;
		}

		[[nodiscard]] auto get_options_values() const -> const std::map<std::string, std::string>&
		{
			return this->m_options_values;
		}

		[[nodiscard]] auto get_options() const -> const std::vector<std::shared_ptr<option>>&
		{
			return this->m_options;
		}

		[[nodiscard]] auto get_subcommands() const -> const std::vector<std::shared_ptr<command>>&
		{
			return this->m_subcommands;
		}

		// Copies the option: the same option object can be added to several commands.
		auto add_option(option* new_option) -> void
		{
			if (new_option != nullptr)
			{
				this->m_options.push_back(std::make_shared<option>(*new_option));
			}
		}

		// Option taking a value: "-f,--file" -> `-f value`, `--file value` or `--file=value`.
		auto add_option(std::string options, std::string description, std::string key_name) -> void
		{
			this->m_options.push_back(std::make_shared<option>(
				std::move(options), std::move(description), std::move(key_name)));
		}

		// Option without value: get_option_value(key_name) is "true" when it is present.
		auto add_flag(std::string options, std::string description, std::string key_name) -> void
		{
			this->m_options.push_back(std::make_shared<option>(
				std::move(options), std::move(description), std::move(key_name), true));
		}

		// Copies the command: add its options and subcommands *before* adding it.
		auto add_subcommand(command* new_command) -> void
		{
			if (new_command != nullptr)
			{
				this->m_subcommands.push_back(std::make_shared<command>(*new_command));
			}
		}

		// Shares the command: later changes to it are visible.
		auto add_subcommand(std::shared_ptr<command> new_command) -> void
		{
			if (new_command != nullptr)
			{
				this->m_subcommands.push_back(std::move(new_command));
			}
		}

		// Extra lines shown by app::print_version (author, website, ...).
		auto add_informations(std::map<std::string, std::string> informations) -> void
		{
			for (auto& info : informations)
			{
				this->m_informations.insert(std::move(info));
			}
		}
	};
}  // namespace rcli
