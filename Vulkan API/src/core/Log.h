﻿#pragma once
//-=-=-=-=- SPDLOG -=-=-=-=-
#include <spdlog/spdlog.h>

class Log
{
public:
	static void Init();

	static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
	static std::shared_ptr<spdlog::logger>& GetVMALogger() { return s_VMALogger; }
	static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

private:
	static std::shared_ptr<spdlog::logger> s_CoreLogger;
	static std::shared_ptr<spdlog::logger> s_VMALogger;
	static std::shared_ptr<spdlog::logger> s_ClientLogger;
	
};

//Assert log macros
#ifdef NDEBUG
#define VK_ASSERT(check, msg, ...);
#define VK_CORE_ASSERT(check, msg, ...);
#else
#define VK_ASSERT(check, msg, ...) { if(!(check)){VK_CRITICAL(msg) __debugbreak();} };
#define VK_CORE_ASSERT(check, msg, ...) { if(!(check)){VK_CORE_CRITICAL(msg) __debugbreak();} };
#endif

//Core log macros
#ifdef NDEBUG
#define VK_CORE_TRACE(...);
#define VK_CORE_INFO(...);
#define VK_CORE_WARN(...);
#define VK_CORE_ERROR(...);
#define VK_CORE_CRITICAL(...);
#define VK_CORE_RUNTIME(...);
#else
#define VK_CORE_TRACE(...) ::Log::GetCoreLogger()->trace(__VA_ARGS__);
#define VK_CORE_INFO(...)  ::Log::GetCoreLogger()->info(__VA_ARGS__);
#define VK_CORE_WARN(...)  ::Log::GetCoreLogger()->warn(__VA_ARGS__);
#define VK_CORE_ERROR(...) ::Log::GetCoreLogger()->error(__VA_ARGS__);
#define VK_CORE_CRITICAL(...) ::Log::GetCoreLogger()->critical(__VA_ARGS__);

struct VK_CORE_BENCH
{
	std::chrono::time_point<std::chrono::high_resolution_clock> start;
	std::string name_;
	VK_CORE_BENCH(std::string name) : name_(name)
	{
		start = std::chrono::high_resolution_clock::now();
	}
	~VK_CORE_BENCH()
	{
		std::chrono::duration<double> elapsed_seconds = std::chrono::high_resolution_clock::now() - start;
		auto count = elapsed_seconds.count() * 1000;
		if (count < 1.f)
		{
			
			VK_CORE_WARN("{0} took {1}ms ({2}us)", name_, std::to_string(count), std::to_string(count*1000))
		}
		else
		{
			VK_CORE_WARN("{0} took {1}ms", name_, std::to_string(count))
		}
		
	}
};
//#define VMA_DEBUG_LOG(...) ::Log::GetVMALogger()->warn(__VA_ARGS__)

#define VK_CORE_RUNTIME(x) VK_CORE_CRITICAL(x) throw std::runtime_error("");
#endif

//Client log macros
#define VK_TRACE(...) ::Log::GetClientLogger()->trace(__VA_ARGS__);
#define VK_INFO(...)  ::Log::GetClientLogger()->info(__VA_ARGS__);
#define VK_WARN(...)  ::Log::GetClientLogger()->warn(__VA_ARGS__);
#define VK_ERROR(...) ::Log::GetClientLogger()->error(__VA_ARGS__);
#define VK_CRITICAL(...) ::Log::GetClientLogger()->critical(__VA_ARGS__);