#pragma once

#include <vector>
#include <unordered_map>
#include <memory>

#include "Elysian/ECS/Types.h"
#include "Elysian/ECS/ComponentPattern.h"
#include "Elysian/ECS/ComponentTemplate.h"
#include "Elysian/ECS/System.h"
#include "Elysian/ECS/EntitySet.h"
#include "Elysian/Core/Profiler.h"

namespace Elysian
{
	template<std::size_t t_max_components=128, std::size_t t_max_entities=10000>
	class Scene
	{
		using EntitySets = std::unordered_map<ComponentBitset<t_max_components>, EntitySet<t_max_components>>;
		using Systems = std::vector<std::unique_ptr<Internal::BaseSystem>>;

	public:
		Scene() {}
		void update(double dt);
		void unload();

		template<class T>
		T* register_system();

		template<typename ... T_ComponentTypes>
		ComponentTemplate<t_max_components, T_ComponentTypes...> preregister_entity_definition(std::size_t max_entities=t_max_entities)
		{
			ComponentTemplate<t_max_components, T_ComponentTypes...> component_template;
			m_entity_sets[component_template] = EntitySet<t_max_components>(component_template, max_entities);
			return component_template;
		}

		template<typename ... T_COMPONENTS>
		EntityID create_entity();

		template<typename T>
		EntityID create_entity(const T& component_template);

		template<typename ... T_COMPONENTS>
		void attach_components(const EntityID& entity_id);

		template<typename ... T_COMPONENT_TYPES>
		void attach_components(const EntityID& entity_id, const ComponentBitset<t_max_components>& pattern);

		template<typename ... T_COMPONENTS>
		void detach_components(const EntityID& entity_id);

		template<typename ... T_COMPONENT_TYPES>
		void detach_components(const EntityID& entity_id, const ComponentBitset<t_max_components>& pattern);

	private:
		EntitySets m_entity_sets;
		Systems m_systems;
	};

	template<std::size_t t_max_components, std::size_t MAX_ENTITIES>
	inline void Scene<t_max_components, MAX_ENTITIES>::update(double dt)
	{
		for (auto& system : m_systems)
			system->update(dt);
	}

	template<std::size_t t_max_components, std::size_t MAX_ENTITIES>
	inline void Scene<t_max_components, MAX_ENTITIES>::unload()
	{

	}

	template<std::size_t t_max_components, std::size_t MAX_ENTITIES>
	template<class T>
	inline T* Scene<t_max_components, MAX_ENTITIES>::register_system()
	{
		return static_cast<T*>(m_systems.emplace_back(std::move(std::make_unique<T>())).get());
	}


	template<std::size_t t_max_components, std::size_t MAX_ENTITIES>
	template<typename ...T_COMPONENTS>
	inline EntityID Scene<t_max_components, MAX_ENTITIES>::create_entity()
	{
		ComponentBitset<t_max_components> pattern;

		(pattern.set(component_type<T_COMPONENTS>()), ...);

		if (m_entity_sets.find(pattern) == m_entity_sets.end())
			m_entity_sets[pattern] = EntitySet<t_max_components>(pattern);
		
		m_entity_sets[pattern].create_entity<T_COMPONENTS...>();
		return EntityID();
	}

	template<std::size_t t_max_components, std::size_t t_max_entities>
	template<typename T>
	inline EntityID Scene<t_max_components, t_max_entities>::create_entity(const T& component_template)
	{
		component_template.instantiate_entity(m_entity_sets[component_template]);
		return EntityID();
	}


	template<std::size_t t_max_components, std::size_t MAX_ENTITIES>
	template<typename ...T_COMPONENTS>
	inline void Scene<t_max_components, MAX_ENTITIES>::attach_components(const EntityID& entity_id)
	{

	}

	template<std::size_t t_max_components, std::size_t MAX_ENTITIES>
	template<typename ...T_COMPONENT_TYPES>
	inline void Scene<t_max_components, MAX_ENTITIES>::attach_components(const EntityID& entity_id, const ComponentBitset<t_max_components>& pattern)
	{

	}


	template<std::size_t t_max_components, std::size_t MAX_ENTITIES>
	template<typename ...T_COMPONENTS>
	inline void Scene<t_max_components, MAX_ENTITIES>::detach_components(const EntityID& entity_id)
	{

	}


	template<std::size_t t_max_components, std::size_t MAX_ENTITIES>
	template<typename ...T_COMPONENT_TYPES>
	inline void Scene<t_max_components, MAX_ENTITIES>::detach_components(const EntityID& entity_id, const ComponentBitset<t_max_components>& pattern)
	{

	}
}
