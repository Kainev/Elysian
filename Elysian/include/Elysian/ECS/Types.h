#pragma once

#include <stdint.h>
#include <vector>

#include "Elysian/ECS/ComponentArray.h"

namespace Elysian
{
	typedef uint32_t EntityID;
	typedef uint32_t ComponentID;
	typedef uint32_t ComponentType;
}

namespace Elysian
{
	namespace Internal
	{
		inline static std::vector<std::size_t> component_sizes;

		inline ComponentType register_component_type(std::size_t size)
		{
			static ComponentType next_available_type = 0;
			component_sizes.emplace_back( size );
			return next_available_type++;
		}

		inline std::size_t component_size(ComponentType type)
		{
			return component_sizes[type];
		}
	}

	template <typename T>
	ComponentType component_type()
	{
		static ComponentType type = Internal::register_component_type(sizeof(T));
		return type;
	}
}
