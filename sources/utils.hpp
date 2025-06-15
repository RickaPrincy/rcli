#pragma once

#include <iostream>
#include <string>
#include <vector>

namespace rcli::color
{
	constexpr const char *reset = "\033[0m";
	constexpr const char *b_white = "\033[1;37m";
}  // namespace rcli::color

namespace rcli::utils
{
	auto some(const std::string &text,
		const std::vector<std::string> &values,
		bool ignore_case = false) -> bool;

	auto split(const std::string &input, const std::string &delimiter) -> std::vector<std::string>;

	auto compare_ignore_case(const std::string &text, std::string text2) -> bool;

	inline auto print_as_key_value(const std::string &key, const std::string &value) -> void
	{
		std::cout << color::b_white << key << ": " << color::reset << value << "\n";
	}
}  // namespace rcli::utils
