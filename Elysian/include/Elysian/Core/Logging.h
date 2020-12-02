#pragma once

#include <spdlog/spdlog.h>

namespace Elysian
{
	class Logging
	{
	public:
		static void initialize();

		inline static std::shared_ptr<spdlog::logger>& engine_logger() { return s_engine_logger; }
		inline static std::shared_ptr<spdlog::logger>& client_logger() { return s_client_logger; }
	private:
		static std::shared_ptr<spdlog::logger> s_engine_logger;
		static std::shared_ptr<spdlog::logger> s_client_logger;
	};	
}

#define ELYSIAN_INTERNAL_TRACE(...)    ::Elysian::Logging::engine_logger()->trace(__VA_ARGS__)
#define ELYSIAN_INTERNAL_INFO(...)     ::Elysian::Logging::engine_logger()->info(__VA_ARGS__)
#define ELYSIAN_INTERNAL_WARN(...)     ::Elysian::Logging::engine_logger()->warn(__VA_ARGS__)
#define ELYSIAN_INTERNAL_ERROR(...)    ::Elysian::Logging::engine_logger()->error(__VA_ARGS__)
#define ELYSIAN_INTERNAL_CRITICAL(...) ::Elysian::Logging::engine_logger()->critical(__VA_ARGS__)


#define ELYSIAN_TRACE(...)    ::Elysian::Logging::client_logger()->trace(__VA_ARGS__)
#define ELYSIAN_INFO(...)     ::Elysian::Logging::client_logger()->info(__VA_ARGS__)
#define ELYSIAN_WARN(...)     ::Elysian::Logging::client_logger()->warn(__VA_ARGS__)
#define ELYSIAN_ERROR(...)    ::Elysian::Logging::client_logger()->error(__VA_ARGS__)
#define ELYSIAN_CRITICAL(...) ::Elysian::Logging::client_logger()->critical(__VA_ARGS__)