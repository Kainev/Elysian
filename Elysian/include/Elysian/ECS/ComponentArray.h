#pragma once

#include <cstddef>
#include <cstring>
#include <utility>

namespace Elysian
{
	namespace Internal
	{
		template <typename T, typename ... T_Args>
		inline void Construct_T(T* object, T_Args&&... params)
		{
			new (object)T{ std::forward<T_Args>(params)... };
		}

		template <typename T>
		inline void Destroy_T(void* element)
		{
			static_cast<T*>(element)->T::~T();
		}

		class ComponentAllocator
		{
			using VoidFunction = void(*)(void*);

		public:
			ComponentAllocator() : m_size(0), m_stride(0), m_count(0), m_data(nullptr), m_handles(nullptr) {}
			~ComponentAllocator() {}

			template<typename T>
			void clear()
			{
				m_destructor_t = Destroy_T<T>;

				char* ptr = m_data;
				std::size_t count = m_count;
				for (; count > 0; --count, ptr += m_stride)
					m_destructor_t(ptr);

				free(m_data);
			}

			template<typename T>
			T* next()
			{
				// TODO: Call destructor of last removed index???? Store ptr* of last removed, if(ptr != nullptr) destroy__t
				T* component = (T*)m_data + m_count;
				Construct_T<T>(component); // TODO: Store this as static ?
				m_count++;
				return component;
			}

			template<typename T>
			T* get(std::size_t index)
			{
				T* element = (T*)m_data + index;
				return element;
			}

			void remove(std::size_t index)
			{
				memcpy(m_data + (m_stride * index), m_data + (--m_count * m_stride), m_stride);
			}

			void intialize(std::size_t component_size, std::size_t max_components)
			{
				m_stride = component_size;
				m_size = m_stride * max_components;
				m_data = (char*)malloc(m_size);
			}

		protected:
			std::size_t m_size;
			std::size_t m_stride;
			std::size_t m_count;

			VoidFunction m_constructor_t = nullptr;
			VoidFunction m_destructor_t = nullptr;

			char* m_data = nullptr;
			char* m_handles = nullptr;
		};
	}
}