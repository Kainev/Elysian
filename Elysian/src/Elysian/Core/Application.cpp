#include "Elysian/Core/pch.h"
#include "Elysian/Core/application.h"

#include "glad/glad.h"
#include <GLFW/glfw3.h>

#include "Elysian/Core/Window.h"
#include "Elysian/Core/EventManager.h"

#include "Elysian/Event/WindowEvent.h"

namespace Elysian
{
	Application* Application::s_instance = nullptr;

	Application::Application(const std::string& name)
	{
		initialize();
	}

	void Application::initialize()
	{
		ELYSIAN_INTERNAL_ASSERT(!s_instance, "Multiple Elysian Applications instantiated!");

		s_instance = this;
		m_window = Window::create();

		EventManager::listen<WindowCloseEvent>([this](WindowCloseEvent* event) { this->exit(); });
	}

	void Application::run()
	{
		while (m_running)
		{
			m_window->update();

			double time = glfwGetTime();
			double delta = time - m_last_frame_time;
			m_last_frame_time = time;
		}
	}

	void Application::exit()
	{
		m_running = false;
	}
}