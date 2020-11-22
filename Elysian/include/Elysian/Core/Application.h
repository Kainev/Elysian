#pragma once

#include <memory>


namespace Elysian
{
	class Application
	{
	public:
		Application(const std::string& name = "Elysian Application");
		virtual ~Application();
		
		static Application& instance() { return *s_instance; }

		void exit();
	private:
		void run();

	private:
		static Application* s_instance;

		bool m_running = true;
		double m_last_frame_time = 0.0;
	};
}