#include "Elysian/Core/Logging.h"

#include <spdlog/sinks/stdout_color_sinks.h>

namespace Elysian
{
	std::shared_ptr<spdlog::logger> Logging::sEngineLogger;
	std::shared_ptr<spdlog::logger> Logging::sClientLogger;

	void Logging::initialize()
	{
		spdlog::set_pattern("%^[%T] %n: %v%$");
		sEngineLogger = spdlog::stdout_color_mt("Elysian");
		sEngineLogger->set_level(spdlog::level::trace);

		sClientLogger = spdlog::stdout_color_mt("Client");
		sClientLogger->set_level(spdlog::level::trace);
	}
}