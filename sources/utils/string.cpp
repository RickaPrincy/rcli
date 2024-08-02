#include <algorithm>
#include <cctype>
#include <numeric>

#include "utils.hpp"

std::string rcli::Utils::repeat(std::string text, int number)
{
	return number < 1 ? text : text + Utils::repeat(text, --number);
}

std::string rcli::Utils::join(const std::vector<std::string> &values, std::string separator)
{
	return std::accumulate(values.begin() + 1,
		values.end(),
		values.front(),
		[separator](const std::string &acc, const std::string &element)
		{ return acc + separator + element; });
}

bool rcli::Utils::some(std::string text, const std::vector<std::string> &values, bool ignore_case)
{
	return std::find_if(values.begin(),
			   values.end(),
			   [&](const std::string &element) {
				   return ignore_case ? compare_ignore_case(text, element) : text == element;
			   }) != values.end();
}

bool rcli::Utils::compare_ignore_case(std::string text, std::string text2)
{
	return std::equal(text.begin(),
		text.end(),
		text2.begin(),
		text2.end(),
		[](char c1, char c2) { return std::tolower(c1) == std::tolower(c2); });
}

std::string rcli::Utils::uppercase(const std::string text)
{
	std::string result = text;
	for (char &c : result)
		c = std::toupper(c);
	return result;
}

std::string rcli::Utils::lowercase(const std::string text)
{
	std::string result = text;
	for (char &c : result)
		c = std::tolower(c);
	return result;
}

std::string rcli::Utils::clean_text(const std::string text, char symbol)
{
	auto temp_text = text;
	temp_text.erase(std::remove(temp_text.begin(), temp_text.end(), symbol), temp_text.end());
	return temp_text;
}

std::vector<std::string> rcli::Utils::split(const std::string input, std::string delimiter)
{
	std::vector<std::string> tokens;
	size_t start = 0;
	size_t end = input.find(delimiter);

	while (end != std::string::npos)
	{
		tokens.push_back(input.substr(start, end - start));
		start = end + delimiter.length();
		end = input.find(delimiter, start);
	}

	tokens.push_back(input.substr(start));

	return tokens;
}
