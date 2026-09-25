// rcli v2.1.0 - single header version
// Header-only library to build command line applications in C++17.
// https://github.com/RickaPrincy/rcli - MIT License
//
// GENERATED FILE, DO NOT EDIT: run `python3 tools/amalgamate.py` after changing include/.
#pragma once

// ----- begin rcli.hpp -----

// rcli: header-only library to build command line applications in C++17.
// https://github.com/RickaPrincy/rcli (MIT License)

// ----- begin app.hpp -----

#include <iostream>
#include <string>
#include <utility>

// ----- begin command.hpp -----

#include <functional>
#include <iostream>
#include <map>
#include <memory>
#include <optional>
#include <string>
#include <utility>
#include <vector>

// ----- begin detail.hpp -----

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>
#include <string_view>
#include <vector>

#ifdef _WIN32
#include <io.h>
#else
#include <unistd.h>
#endif

// Internal helpers, not part of the public API.
namespace rcli::detail
{
	inline constexpr std::string_view reset = "\033[0m";
	inline constexpr std::string_view b_white = "\033[1;37m";

	inline auto get_env(const char* name) -> std::string
	{
#ifdef _WIN32
		char* buffer = nullptr;
		std::size_t size = 0;
		std::string value;
		if (_dupenv_s(&buffer, &size, name) == 0 && buffer != nullptr)
		{
			value = buffer;
		}
		std::free(buffer);
		return value;
#else
		const char* value = std::getenv(name);
		return value == nullptr ? std::string{} : std::string(value);
#endif
	}

	// Colors only when stdout is a terminal, NO_COLOR is not set and TERM is not "dumb".
	inline auto use_color() -> bool
	{
#ifdef _WIN32
		const bool tty = _isatty(_fileno(stdout)) != 0;
#else
		const bool tty = isatty(STDOUT_FILENO) != 0;
#endif
		return tty && get_env("NO_COLOR").empty() && get_env("TERM") != "dumb";
	}

	inline auto print_as_key_value(std::ostream& out,
		const std::string& key,
		const std::string& value) -> void
	{
		const bool color = &out == &std::cout && use_color();
		if (color)
		{
			out << b_white;
		}
		out << key << ": ";
		if (color)
		{
			out << reset;
		}
		out << value << "\n";
	}

	inline auto print_title(std::ostream& out, const std::string& title) -> void
	{
		const bool color = &out == &std::cout && use_color();
		out << "\n";
		if (color)
		{
			out << b_white;
		}
		out << title;
		if (color)
		{
			out << reset;
		}
		out << "\n";
	}

	inline auto trim(const std::string& value) -> std::string
	{
		const auto first = value.find_first_not_of(" \t");
		if (first == std::string::npos)
		{
			return {};
		}
		const auto last = value.find_last_not_of(" \t");
		return value.substr(first, last - first + 1);
	}

	inline auto split(const std::string& input, const std::string& delimiter)
		-> std::vector<std::string>
	{
		std::size_t start = 0;
		std::size_t end = input.find(delimiter);
		std::vector<std::string> tokens{};

		while (end != std::string::npos)
		{
			tokens.push_back(input.substr(start, end - start));
			start = end + delimiter.length();
			end = input.find(delimiter, start);
		}
		tokens.push_back(input.substr(start));
		return tokens;
	}

	inline auto is_option(const std::string& arg) -> bool
	{
		return arg.size() > 1 && arg[0] == '-';
	}

	// "--file" -> "file", "-f" -> "f"
	inline auto strip_dashes(const std::string& arg) -> std::string
	{
		const auto first = arg.find_first_not_of('-');
		return first == std::string::npos ? std::string{} : arg.substr(first);
	}
}  // namespace rcli::detail
// ----- end detail.hpp -----
// ----- begin option.hpp -----

#include <algorithm>
#include <string>
#include <utility>
#include <vector>

namespace rcli
{
	// A named option: "-f,--file" matches both `-f` and `--file`, and its value is stored under
	// `key_name` (read it with command::get_option_value(key_name)).
	// A flag takes no value: its value is "true" when present (see command::add_flag).
	class option
	{
	protected:
		std::vector<std::string> m_options{};
		std::string m_base_names{}, m_description{}, m_key_name{};
		bool m_is_flag{ false };

	public:
		option(std::string options,
			std::string description,
			std::string key_name,
			bool is_flag = false)
			: m_base_names(std::move(options)),
			  m_description(std::move(description)),
			  m_key_name(std::move(key_name)),
			  m_is_flag(is_flag)
		{
			for (const auto& name : detail::split(this->m_base_names, ","))
			{
				auto trimmed = detail::trim(name);
				if (!trimmed.empty())
				{
					this->m_options.push_back(std::move(trimmed));
				}
			}
		}

		[[nodiscard]] auto get_description() const -> const std::string&
		{
			return this->m_description;
		}

		// The names as declared, e.g. "-f,--file".
		[[nodiscard]] auto get_base_name() const -> const std::string&
		{
			return this->m_base_names;
		}

		[[nodiscard]] auto get_key_name() const -> const std::string&
		{
			return this->m_key_name;
		}

		// The individual names, e.g. { "-f", "--file" }.
		[[nodiscard]] auto get_names() const -> const std::vector<std::string>&
		{
			return this->m_options;
		}

		[[nodiscard]] auto is_flag() const -> bool
		{
			return this->m_is_flag;
		}

		[[nodiscard]] auto matches(const std::string& value) const -> bool
		{
			return std::find(this->m_options.begin(), this->m_options.end(), value) !=
				   this->m_options.end();
		}

		// The key name when `value` is one of the option names, "" otherwise.
		[[nodiscard]] auto get_key_if_matched(const std::string& value) const -> std::string
		{
			return this->matches(value) ? this->m_key_name : "";
		}
	};
}  // namespace rcli
// ----- end option.hpp -----

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
// ----- end command.hpp -----

namespace rcli
{
	// The root command of a CLI application. Adds -v,--version and -h,--help, and prints the
	// help when called without arguments.
	class app : public command
	{
	protected:
		std::string m_version;

	public:
		app(std::string name, std::string description, std::string version)
			: m_version(std::move(version))
		{
			this->m_name = std::move(name);
			this->m_description = std::move(description);
			this->m_callback = [](command* p_app) -> void { p_app->print_help(); };
			this->add_option("-v,--version", "Show the version", "version");
			this->add_option("-h,--help", "Show this help", "help");
		}

		[[nodiscard]] auto get_version() const -> const std::string&
		{
			return this->m_version;
		}

		virtual auto print_version() -> void
		{
			detail::print_as_key_value(std::cout, " Name", this->m_name);
			detail::print_as_key_value(std::cout, " Version", this->m_version);
			detail::print_as_key_value(std::cout, " Description", this->m_description);

			for (const auto& [key, value] : this->m_informations)
			{
				detail::print_as_key_value(std::cout, " " + key, value);
			}
		}

		// Parses the command line and runs the matching command. Returns the exit code:
		// 0 on success, 1 on invalid input (the help is printed).
		auto run(int argc, const char* argv[]) -> int  // NOLINT(modernize-avoid-c-arrays)
		{
			if (argc == 2 && argv[1] != nullptr)
			{
				const std::string arg = argv[1];
				if (arg == "-v" || arg == "--version")
				{
					this->print_version();
					return 0;
				}
			}

			this->m_usage_path = this->m_name;
			return this->parse(argc, argv, 1);
		}

		// Same as above, for `int main(int argc, char *argv[])`.
		auto run(int argc, char* argv[]) -> int	 // NOLINT(modernize-avoid-c-arrays)
		{
			return this->run(argc,
				const_cast<const char**>(argv));  // NOLINT(cppcoreguidelines-pro-type-const-cast)
		}
	};
}  // namespace rcli
// ----- end app.hpp -----
// ----- begin rcli_config.hpp -----

// Kept for compatibility with rcli <= 2.0: the version now lives in version.hpp.
// ----- begin version.hpp -----

// CMakeLists.txt reads the version from these three lines: keep them in this format.
// NOLINTBEGIN(modernize-macro-to-enum)
#define RCLI_VERSION_MAJOR 2
#define RCLI_VERSION_MINOR 1
#define RCLI_VERSION_PATCH 0
// NOLINTEND(modernize-macro-to-enum)

#define RCLI_STRINGIFY_IMPL(x) #x
#define RCLI_STRINGIFY(x) RCLI_STRINGIFY_IMPL(x)

#define RCLI_VERSION                   \
	RCLI_STRINGIFY(RCLI_VERSION_MAJOR) \
	"." RCLI_STRINGIFY(RCLI_VERSION_MINOR) "." RCLI_STRINGIFY(RCLI_VERSION_PATCH)
// ----- end version.hpp -----
// ----- end rcli_config.hpp -----
// ----- end rcli.hpp -----
