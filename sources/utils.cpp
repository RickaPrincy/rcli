#include "utils.hpp"

#include <algorithm>
#include <cctype>

namespace rcli::utils
{
	auto some(const std::string &text, const std::vector<std::string> &values, bool ignore_case)
		-> bool
	{
		return std::find_if(values.begin(),
				   values.end(),
				   [ignore_case, text = text](const std::string &element)
				   {
					   return ignore_case ? compare_ignore_case(text, element) : text == element;
				   }) != values.end();
	}

	auto compare_ignore_case(const std::string &text, std::string text2) -> bool
	{
		return std::equal(text.begin(),
			text.end(),
			text2.begin(),
			text2.end(),
			[](char c1, char c2) { return std::tolower(c1) == std::tolower(c2); });
	}

	auto split(const std::string &input, const std::string &delimiter) -> std::vector<std::string>
	{
		size_t start = 0;
		size_t end = input.find(delimiter);
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
}  // namespace rcli::utils
