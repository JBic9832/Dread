#pragma once 

#include "spdlog/spdlog.h"
#include <memory.h>

namespace Dread {
	class Logger {
	public:
		Logger();
		~Logger();

		static void Init();

		inline static std::shared_ptr<spdlog::logger>&  GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>&  GetClientLogger() { return s_ClientLogger; }

	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};
}

// Core logging macors
#define DREAD_CORE_ERROR(...) ::Dread::Logger::GetCoreLogger()->error(__VA_ARGS__);
#define DREAD_CORE_WARN(...)  ::Dread::Logger::GetCoreLogger()->warn(__VA_ARGS__);
#define DREAD_CORE_INFO(...)  ::Dread::Logger::GetCoreLogger()->info(__VA_ARGS__);
#define DREAD_CORE_TRACE(...) ::Dread::Logger::GetCoreLogger()->trace(__VA_ARGS__);

// Client logging macros
#define DREAD_ERROR(...) ::Dread::Logger::GetClientLogger()->error(__VA_ARGS__);
#define DREAD_WARN(...)  ::Dread::Logger::GetClientLogger()->warn(__VA_ARGS__);
#define DREAD_INFO(...)  ::Dread::Logger::GetClientLogger()->info(__VA_ARGS__);
#define DREAD_TRACE(...) ::Dread::Logger::GetClientLogger()->trace(__VA_ARGS__);
