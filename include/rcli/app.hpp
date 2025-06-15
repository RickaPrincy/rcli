#pragma once

#include <rcli/command.hpp>
#include <string>

namespace rcli
{
	class app : public command
	{
	protected:
		std::string m_version;

	public:
		app(std::string name, std::string version, std::string description);

		virtual auto print_version() -> void;
		auto run(int argc, const char *argv[]) -> int;	// NOLINT(modernize-avoid-c-arrays)
	};
}  // namespace rcli
