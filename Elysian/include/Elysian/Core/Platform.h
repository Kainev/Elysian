#pragma once

#ifdef _WIN32
	#ifdef _WIN64
		// Windows x64 Specific
		#define ELYSIAN_PLATFORM_WIN64
	#else
		// Windows x86 Specific
		#define ELYSIAN_PLATFORM_WIN86
		#error "Unsupported Platform: Windows x86"
	#endif
#elif defined(__APPLE__) || defined(__MACH__)
	#include <TargetConditionals.h>

	#if TARGET_IPHONE_SIMULATOR == 1
		#define ELYSIAN_PLATFORM_IOS_SIMULATOR
		#error "Unsupported Platform: IOS Simulator"
	#elif TARGET_OS_IPHONE == 1
		#define ELYSIAN_PLATFORM_IOS
		#error "Unsupported Platform: IOS"
	#elif TARGET_OS_MAC == 1
		#define ELYSIAN_PLATFORM_MAC
		#error "Unsupported Platform: MacOS"
	#else
		#error "Unknown Apple Platform"
	#endif
#elif defined(__ANDROID__)
	#define ELYSIAN_PLATFORM_ANDROID
	#error "Unsupported Platform: Android"
#elif defined(__linux__) || defined(__linux) || defined(linux)
	#define ELYSIAN_PLATFORM_LINUX
	#error "Unsupported Platform: Linux"
#else
	#error "Unknown Platform"
#endif
