#pragma once

#include "CGHacker/Core/Base.h"

//https://github.com/gabime/spdlog/issues/660
// The include order is the matter
#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>

namespace CG {

class Log {
public:
  static void Init();

  static Ref<spdlog::logger> &GetCoreLogger() { return s_CoreLogger; }
  static Ref<spdlog::logger> &GetClientLogger() { return s_ClientLogger; }

private:
  static Ref<spdlog::logger> s_CoreLogger;
  static Ref<spdlog::logger> s_ClientLogger;
};

} // namespace Hazel

// Core log macros
#define CG_CORE_TRACE(...) ::CG::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define CG_CORE_INFO(...) ::CG::Log::GetCoreLogger()->info(__VA_ARGS__)
#define CG_CORE_WARN(...) ::CG::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define CG_CORE_ERROR(...) ::CG::Log::GetCoreLogger()->error(__VA_ARGS__)
#define CG_CORE_CRITICAL(...)                                              \
  ::CG::Log::GetCoreLogger()->critical(__VA_ARGS__)

// Client log macros
#define CG_TRACE(...) ::CG::Log::GetClientLogger()->trace(__VA_ARGS__)
#define CG_INFO(...) ::CG::Log::GetClientLogger()->info(__VA_ARGS__)
#define CG_WARN(...) ::CG::Log::GetClientLogger()->warn(__VA_ARGS__)
#define CG_ERROR(...) ::CG::Log::GetClientLogger()->error(__VA_ARGS__)
#define CG_CRITICAL(...)                                                   \
  ::CG::Log::GetClientLogger()->critical(__VA_ARGS__)
