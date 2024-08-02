#pragma once

#include <rcli/input_config.hpp>
#include <string>
#include <vector>

namespace rcli
{
	std::string ask_input_value(InputConfig config);

	std::string ask_value_in_list(InputConfig config,
		std::vector<std::string> options,
		bool ignore_case = false);

	bool ask_boolean(std::string text, bool default_value = true);

	std::string ask_value_in_list_as_number(std::string text, std::vector<std::string> options);
}  // namespace rcli
