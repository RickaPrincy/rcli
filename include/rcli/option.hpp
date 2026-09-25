#pragma once

#include <algorithm>
#include <string>
#include <utility>
#include <vector>

#include "detail.hpp"

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
