#include "Elysian/Core/Logging.h"

#include <spdlog/sinks/stdout_color_sinks.h>

namespace Elysian
{
	std::shared_ptr<spdlog::logger> Logging::s_engine_logger;
	std::shared_ptr<spdlog::logger> Logging::s_client_logger;

	void Logging::initialize()
	{
		spdlog::set_pattern("%^[%T] %n: %v%$");
		s_engine_logger = spdlog::stdout_color_mt("Elysian");
		s_engine_logger->set_level(spdlog::level::trace);

		s_client_logger = spdlog::stdout_color_mt("Client");
		s_client_logger->set_level(spdlog::level::trace);
	}
}