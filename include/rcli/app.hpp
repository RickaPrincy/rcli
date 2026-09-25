#pragma once

#include <iostream>
#include <string>
#include <utility>

#include "command.hpp"
#include "detail.hpp"

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
