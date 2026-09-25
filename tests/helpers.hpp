#pragma once

#include <iostream>
#include <rcli/rcli.hpp>
#include <sstream>
#include <string>
#include <vector>

namespace test
{
	// Captures everything written to std::cout while alive.
	class capture_cout
	{
	private:
		std::ostringstream m_buffer;
		std::streambuf* m_previous;

	public:
		capture_cout() : m_previous(std::cout.rdbuf(m_buffer.rdbuf()))
		{
		}
		capture_cout(const capture_cout&) = delete;
		capture_cout(capture_cout&&) = delete;
		auto operator=(const capture_cout&) -> capture_cout& = delete;
		auto operator=(capture_cout&&) -> capture_cout& = delete;
		~capture_cout()
		{
			std::cout.rdbuf(this->m_previous);
		}

		[[nodiscard]] auto str() const -> std::string
		{
			return this->m_buffer.str();
		}
	};

	// Builds an argv from a list of arguments (program name included).
	class args
	{
	private:
		std::vector<std::string> m_storage;
		std::vector<const char*> m_argv;

	public:
		args(std::initializer_list<std::string> values) : m_storage(values)
		{
			for (const auto& value : this->m_storage)
			{
				this->m_argv.push_back(value.c_str());
			}
			this->m_argv.push_back(nullptr);
		}

		[[nodiscard]] auto argc() const -> int
		{
			return static_cast<int>(this->m_storage.size());
		}

		[[nodiscard]] auto argv() -> const char**
		{
			return this->m_argv.data();
		}
	};

	inline auto contains(const std::string& haystack, const std::string& needle) -> bool
	{
		return haystack.find(needle) != std::string::npos;
	}
}  // namespace test
