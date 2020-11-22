#include "Elysian/Core/pch.h"
#include "Elysian/Core/application.h"

#include <GLFW/glfw3.h>

namespace Elysian
{
	Application* Application::s_instance = nullptr;

	Application::Application(const std::string& name)
	{
		s_instance = this;
	}

	Application::~Application()
	{
	}

	void Application::exit()
	{
		m_running = false;
	}

	void Application::run()
	{
		while (m_running)
		{
			double time = glfwGetTime();
			double delta = time - m_last_frame_time;
			m_last_frame_time = time;
		}
	}
}