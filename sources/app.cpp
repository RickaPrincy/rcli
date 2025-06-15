#include <cstdlib>
#include <rcli/app.hpp>
#include <rcli/command.hpp>

#include "utils.hpp"

namespace rcli
{

	app::app(std::string name, std::string description, std::string version)
	{
		this->m_name = std::move(name);
		this->m_version = std::move(version);
		this->m_description = std::move(description);
		this->m_callback = [](command *p_app) { p_app->print_help(); };
		this->add_option("-v,--version", "Show the version", "version");
		this->add_option("-h,--help", "Show this help", "help");
	}

	auto app::run(int argc, const char *argv[])	 // NOLINT(modernize-avoid-c-arrays)
		-> int
	{
		if (argc == 2)
		{
			std::string arg = argv[1];
			if (arg == "-v" || arg == "--version")
			{
				this->print_version();
				return 0;
			}
		}

		this->parse(argc, argv, 1);
		return 0;
	}

	void app::print_version()
	{
		utils::print_as_key_value(" Name", this->m_name);
		utils::print_as_key_value(" Version", this->m_version);
		utils::print_as_key_value(" Description", this->m_description);

		for (const auto &[key, value] : this->m_informations)
		{
			utils::print_as_key_value(" " + key, value);
		}
	}
}  // namespace rcli
