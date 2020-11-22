#pragma once


#ifdef DEBUG_BUILD

#ifndef debug_break
#	if defined(_MSC_VER)
#		define debug_break() __debugbreak()
#	elif defined(__has_builtin)
#		if __has_builtin(__builtin_debugtrap)
#			define debug_break() __builtin_debugtrap()
#		elif __has_builtin(__debugbreak)
#			define debug_break() __debugbreak()
#		endif
#	else
#		include <signal.h>
#		if defined(SIGTRAP)
#			define debug_break() raise(SIGTRAP)
#		elif defined(SIGABRT)
#			define debug_break() raise(SIGABRT)
#		else
#			if defined(warning)
#				warning "Unable to determine debug_break for current platform. Break points disabled."
#			else
#				pragma message("Unable to determine debug_break for current platform. Break points disabled.")
#			endif
#			define debug_break()
#		endif
#	endif
#endif

#	define ELYSIAN_ASSERT(x, ...) { if(!(x)) {ELYSIAN_ERROR("Assertion Failed: {0}", __VA_ARGS__); debug_break(); } }
#	define ELYSIAN_INTERNAL_ASSERT(x, ...) { if(!(x)) {ELYSIAN_INTERNAL_ERROR("Assertion Failed: {0}", __VA_ARGS__); debug_break(); } }

#	define ELYSIAN_UNIMPLEMENTED { ELYSIAN_ERROR("UNIMPLEMENTED_FUNCTION"); debug_break(); }
#	define ELYSIAN_INTERNAL_UNIMPLEMENTED { ELYSIAN_INTERNAL_ERROR("UNIMPLEMENTED_FUNCTION"); debug_break(); }

#	define ELYSIAN_ENSURE(x, ...) { if(!(x)) { ELYSIAN_WARN("Ensure Failed: {0}", __VA_ARGS__); } }
#	define ELYSIAN_INTERNAL_ENSURE(x, ...) { if(!(x)) { ELYSIAN_INTERNAL_WARN("Ensure Failed: {0}", __VA_ARGS__); } }
#else
#	ifndef debug_break
#		define debug_break()
#	endif

#	define ELYSIAN_ASSERT(x, ...)
#	define ELYSIAN_INTERNAL_ASSERT(x, ...)

#	define ELYSIAN_UNIMPLEMENTED
#	define ELYSIAN_INTERNAL_UNIMPLEMENTED

#	define ELYSIAN_ENSURE(x, ...)
#	define ELYSIAN_INTERNAL_ENSURE(x, ...)
#endif