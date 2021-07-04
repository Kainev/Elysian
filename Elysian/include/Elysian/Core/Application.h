/***********************************************************************|
| Application.h                                                         |
|-----------------------------------------------------------------------|
|                               ELYSIAN                                 |
|                   https://github.com/kainev/Elysian                   |
|-----------------------------------------------------------------------|
| Copyright © 2020 Kaine van Gemert                                     |
|                                                                       |
| Permission is hereby granted, free of charge, to any person obtaining |
| a  copy  of  this software  and  associated  documentation files (the |
| “Software”),  to deal in the Software without restriction,  including |
| without limitation the rights to use,  copy,  modify,  merge, publish,|
| distribute,  sublicense,  and/or sell copies of the Software,  and to |
| permit  persons  to whom the Software is furnished to do so,  subject |
| to the following conditions:                                          |
|                                                                       |
| The  above  copyright  notice  and  this  permission  notice shall be |
| included in all copies or substantial portions of the Software.       |
|                                                                       |
| THE  SOFTWARE  IS  PROVIDED “AS IS”,  WITHOUT  WARRANTY OF ANY  KIND, |
| EXPRESS OR IMPLIED,  INCLUDING BUT NOT  LIMITED TO  THE WARRANTIES OF |
| MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.|
| IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR  ANY |
| CLAIM, DAMAGES OR OTHER LIABILITY,  WHETHER IN AN ACTION OF CONTRACT, |
| TORT  OR OTHERWISE,  ARISING FROM,  OUT OF OR IN  CONNECTION WITH THE |
| SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.                |
************************************************************************/

#pragma once

#include <memory>
#include "Window.h"


namespace Elysian
{
	class Window;

	class Application
	{
	public:
		Application(const std::string& name = "Elysian Application");
		virtual	~Application() = default;
		
		static auto instance() -> Application& { return *s_instance; }
		void exit();


	private:
		void run();
		void initialize();

	private:
		static Application* s_instance;
		std::unique_ptr<Window> m_window;

		bool m_running = true;
		double m_last_frame_time = 0.0;

		template <typename T>
		friend void initialize(); // Engine.h
	};
}