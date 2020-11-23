#pragma once

#include <vector>
#include <memory>

#include "Elysian/ECS/Types.h"

namespace Elysian
{
	namespace Internal
	{
		class BaseSystem
		{
		public:
			BaseSystem() {}
			virtual void update(double dt) = 0;
		};
	}

	template <class ... T_COMPONENTS>
	class System : public Internal::BaseSystem
	{
	public:
		System() : BaseSystem() {}
	};
}
