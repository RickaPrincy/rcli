#pragma once

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
