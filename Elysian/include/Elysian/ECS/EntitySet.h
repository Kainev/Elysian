#pragma once

#include <vector>
#include <unordered_map>
#include <memory>

#include "Elysian/ECS/Types.h"
#include "Elysian/ECS/ComponentArray.h"
#include "Elysian/ECS/ComponentPattern.h"

namespace Elysian
{
	template<std::size_t t_max_components=128>
	class EntitySet
	{
	public:
		EntitySet() {}

		EntitySet(ComponentBitset<t_max_components> pattern, std::size_t max_entities) : m_pattern(pattern)
		{
			const std::vector<ComponentType>& types = pattern.component_types();
			for (int i = 0; i < types.size(); i++)
			{
				m_allocator_indices[types[i]] = i;
				Internal::ComponentAllocator& allocator = m_allocators.emplace_back();
				allocator.intialize(Internal::component_size(types[i]), max_entities);
			}
		}

		template<typename T>
		T* get(std::size_t index) { return m_allocators[m_allocator_indices[component_type<T>()]].get<T>(index); }

		template<typename... Ts>
		EntityID create_entity()
		{
			(m_allocators[m_allocator_indices[component_type<Ts>()]].next<Ts>(), ...);
			//(vec.push_back(m_allocators[m_allocator_indices[component_type<Ts>()]].get<Ts>(m_entity_count)->health), ...);
			m_entity_count++;
			return 0;
		}

	private:
		std::size_t m_entity_count = 0;
		ComponentBitset<t_max_components> m_pattern;

		//std::

		std::array<std::size_t, t_max_components> m_allocator_indices;
		std::vector<Internal::ComponentAllocator> m_allocators;
	};
}
