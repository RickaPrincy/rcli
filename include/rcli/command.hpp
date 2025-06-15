#pragma once

#include <functional>
#include <map>
#include <memory>
#include <rcli/option.hpp>
#include <string>
#include <vector>

namespace rcli
{
	class command;

	using callback = std::function<void(command *)>;

	class command
	{
	protected:
		callback m_callback{};
		std::string m_name{}, m_description{};
		std::vector<std::shared_ptr<option>> m_options{};
		std::vector<std::shared_ptr<command>> m_subcommands{};
		std::map<std::string, std::string> m_options_values{}, m_informations{};

		auto match(const std::string &text) -> bool;
		auto call_if_match(const std::string &text) -> bool;
		auto parse(int argc, const char *argv[], int start)	 // NOLINT(modernize-avoid-c-arrays)
			-> void;

		command() = default;

	public:
		virtual auto print_help() -> void;

		[[nodiscard]] auto get_name() const -> const std::string &;
		[[nodiscard]] auto get_description() const -> const std::string &;
		[[nodiscard]] auto get_option_value(const std::string &key) -> std::string;

		auto add_option(option *new_option) -> void;
		auto add_option(std::string options, std::string description, std::string key_name) -> void;

		auto add_subcommand(command *new_command) -> void;
		auto add_informations(std::map<std::string, std::string> informations) -> void;

		command(std::string name, std::string description, callback callback);
	};
}  // namespace rcli
