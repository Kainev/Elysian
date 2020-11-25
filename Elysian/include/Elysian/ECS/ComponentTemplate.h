#pragma once

#include <stdint.h>
#include <cstddef>
#include <type_traits>
#include <functional>

#include "Elysian/ECS/Types.h"
#include "Elysian/ECS/ComponentPattern.h"

namespace Elysian
{
	namespace Internal
	{
		template<typename T>
		struct has_create_entity_method
		{
		private:
			template<typename U>
			static auto test(int) -> decltype(std::declval<U>().create_entity() == 1, std::true_type());

			template<typename>
			static auto test(...)->std::false_type;

		public:
			static constexpr bool value = std::is_same<decltype(test<T>(0)), std::true_type>::value;
		};
	}

	template<std::size_t t_max_components, typename... t_components>
	class ComponentTemplate : public ComponentBitset<t_max_components>
	{
	public:
		ComponentTemplate()
		{
			(set(component_type<t_components>()), ...);
		}

	private:
		template <typename T>
		void instantiate_entity(T& entity_set) const
		{
			static_assert(Internal::has_create_entity_method<T>().value);

			entity_set.create_entity<t_components...>();
		}

		template<std::size_t t_max_components, std::size_t t_max_entities>
		friend class Scene;
	};
}
