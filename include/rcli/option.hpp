#pragma once

#include <string>
#include <vector>

namespace rcli
{
	class option
	{
	protected:
		std::vector<std::string> m_options{};
		std::string m_base_names{}, m_description{}, m_key_name{};

	public:
		[[nodiscard]] auto get_description() const -> const std::string &;
		[[nodiscard]] auto get_base_name() const -> const std::string &;
		[[nodiscard]] auto get_key_if_matched(const std::string &value) const -> std::string;

		option(std::string options, std::string description, std::string key_name);
	};
}  // namespace rcli
