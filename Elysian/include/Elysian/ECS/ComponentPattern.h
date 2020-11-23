#pragma once

#include <stdint.h>
#include <cstddef>
#include <type_traits>
#include <functional>

#include "Elysian/ECS/Types.h"

namespace Elysian
{
	template<uint32_t t_max_components>
	class ComponentBitset
	{
		using bitset = std::size_t;
	public:
		ComponentBitset() { reset(); }

		void set(ComponentType index);
		void reset();
		bool has_subset(const ComponentBitset<t_max_components>& pattern) const;
		const std::vector<ComponentType>& component_types() { return m_component_types; }

		bool operator==(const ComponentBitset<t_max_components>& rhs) const noexcept;
		bool operator!=(const ComponentBitset<t_max_components>& rhs) const noexcept;
		bool operator<(const ComponentBitset<t_max_components>& rhs) const noexcept;
		bool operator<=(const ComponentBitset<t_max_components>& rhs) const noexcept;

	private:
		bool is_equal(const ComponentBitset<t_max_components>& other) const;

	private:
		inline constexpr static uint32_t bits_per_set = sizeof(bitset) * 8;
		inline constexpr static uint32_t num_bitsets = t_max_components / bits_per_set + (t_max_components % bits_per_set == 0 ? 0 : 1);

		bitset bitsets[num_bitsets];
		std::vector<ComponentType> m_component_types;

		friend struct std::hash<ComponentBitset>;
	};

	template<uint32_t t_max_components>
	inline void ComponentBitset<t_max_components>::set(ComponentType index)
	{
		uint32_t bitset_index = index / bits_per_set;
		bitsets[bitset_index] ^= 1 << (index % bits_per_set);
		m_component_types.push_back(index);
	}


	template<uint32_t t_max_components>
	inline void ComponentBitset<t_max_components>::reset()
	{
		memset(bitsets, 0, num_bitsets * sizeof(bitset));
	}


	template<uint32_t t_max_components>
	inline bool ComponentBitset<t_max_components>::has_subset(const ComponentBitset<t_max_components>& pattern) const
	{
		for (std::size_t i = 0; i < num_bitsets; i++)
			if ((bitsets[i] | pattern.bitsets[i]) != bitsets[i]) return false;
		return true;
	}


	template<uint32_t t_max_components>
	inline bool ComponentBitset<t_max_components>::operator==(const ComponentBitset<t_max_components>& rhs) const noexcept
	{
		return is_equal(rhs);
	}

	template<uint32_t t_max_components>
	inline bool ComponentBitset<t_max_components>::operator!=(const ComponentBitset<t_max_components>& rhs) const noexcept
	{
		std::size_t i = 0;
		for (; i < num_bitsets; i++)
			if (bitsets[i] != rhs.bitsets[i]) break;
		return i != num_bitsets;
	}

	template<uint32_t t_max_components>
	inline bool ComponentBitset<t_max_components>::operator<(const ComponentBitset<t_max_components>& rhs) const noexcept
	{
		return rhs.has_subset(*this) && !is_equal(rhs);
	}

	template<uint32_t t_max_components>
	inline bool ComponentBitset<t_max_components>::operator<=(const ComponentBitset<t_max_components>& rhs) const noexcept
	{
		return rhs.has_subset(*this);
	}

	template<uint32_t t_max_components>
	inline bool ComponentBitset<t_max_components>::is_equal(const ComponentBitset<t_max_components>& other) const
	{
		for (std::size_t i = 0; i < num_bitsets; i++)
			if (bitsets[i] != other.bitsets[i]) return false;
		return true;
	}

	/*********************************************************************************************************************************/
	template<typename... T_Components>
	inline ComponentBitset<128> component_pattern()
	{
		ComponentBitset<128> pattern;
		(pattern.set(component_type<T_Components>()), ...);

		return pattern;
	}

	template<typename... T_Components>
	inline ComponentBitset<128> component_pattern(T_Components... types)
	{
		ComponentBitset<128> pattern;
		(pattern.set(types), ...);

		return pattern;
	}


	template<uint32_t t_max_components, typename... t_components>
	class ComponentTemplate : public ComponentBitset<t_max_components>
	{
	public:
		ComponentTemplate()
		{
			(m_bitset.set(t_components), ...);
		}

	protected:
		/*void instantiate_entity(EntitySet& set)
		{

		}*/

	private:
		ComponentBitset<t_max_components> m_bitset;
	};
}

namespace std
{
	template <uint32_t t_max_components>
	struct hash<Elysian::ComponentBitset<t_max_components>>
	{
		std::size_t operator()(const Elysian::ComponentBitset<t_max_components>& k) const
		{
			std::size_t hash_code = 0;
			for (const auto& bitset : k.bitsets)
				hash_code ^= bitset;
			return hash_code;
		}
	};
}