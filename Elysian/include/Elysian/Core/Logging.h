#pragma once

#include <spdlog/spdlog.h>

namespace Elysian
{
	class Logging
	{
	public:
		static void initialize();

		inline static std::shared_ptr<spdlog::logger>& getEngineLogger() { return sEngineLogger; }
		inline static std::shared_ptr<spdlog::logger>& getClientLogger() { return sClientLogger; }
	private:
		static std::shared_ptr<spdlog::logger> sEngineLogger;
		static std::shared_ptr<spdlog::logger> sClientLogger;
	};

	
}

#define ELYSIAN_INTERNAL_TRACE(...)    ::Elysian::Logging::getEngineLogger()->trace(__VA_ARGS__)
#define ELYSIAN_INTERNAL_INFO(...)     ::Elysian::Logging::getEngineLogger()->info(__VA_ARGS__)
#define ELYSIAN_INTERNAL_WARN(...)     ::Elysian::Logging::getEngineLogger()->warn(__VA_ARGS__)
#define ELYSIAN_INTERNAL_ERROR(...)    ::Elysian::Logging::getEngineLogger()->error(__VA_ARGS__)
#define ELYSIAN_INTERNAL_CRITICAL(...) ::Elysian::Logging::getEngineLogger()->critical(__VA_ARGS__)


#define ELYSIAN_TRACE(...)    ::Elysian::Logging::getClientLogger()->trace(__VA_ARGS__)
#define ELYSIAN_INFO(...)     ::Elysian::Logging::getClientLogger()->info(__VA_ARGS__)
#define ELYSIAN_WARN(...)     ::Elysian::Logging::getClientLogger()->warn(__VA_ARGS__)
#define ELYSIAN_ERROR(...)    ::Elysian::Logging::getClientLogger()->error(__VA_ARGS__)
#define ELYSIAN_CRITICAL(...) ::Elysian::Logging::getClientLogger()->critical(__VA_ARGS__)