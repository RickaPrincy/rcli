#include <rcli/option.hpp>

#include "utils.hpp"

namespace rcli
{
	option::option(std::string options, std::string description, std::string key_name)	// NOLINT
		: m_description(std::move(description)),
		  m_key_name(std::move(key_name))
	{
		this->m_base_names = options;
		this->m_options = utils::split(options, ",");
	}

	auto option::get_key_if_matched(const std::string &value) const -> std::string
	{
		if (utils::some(value, this->m_options))
		{
			return this->m_key_name;
		}
		return "";
	}

	auto option::get_description() const -> const std::string &
	{
		return this->m_description;
	}

	auto option::get_base_name() const -> const std::string &
	{
		return this->m_base_names;
	}
}  // namespace rcli
