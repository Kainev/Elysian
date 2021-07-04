/***********************************************************************|
| Engine.h                                                              |
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

#include "Elysian/Core/Platform.h"
#include "Elysian/Core/Logging.h"
#include "Elysian/Core/Assert.h"
#include "Elysian/Core/Application.h"

#include "Elysian/Core/EventManager.h"
#include "Elysian/Event/KeyEvent.h"
#include "Elysian/Event/MouseEvent.h"
#include "Elysian/Event/WindowEvent.h"

#include "GLFW/glfw3.h"


namespace Elysian
{
	template <typename T>
	void initialize()
	{
		Logging::initialize();
		ELYSIAN_INTERNAL_INFO("Initializing Version {}.{}.{}", ELYSIAN_VERSION_MAJOR, ELYSIAN_VERSION_MINOR, ELYSIAN_VERSION_PATCH);

		std::unique_ptr<T> app = std::make_unique<T>();
		app->run();
	}
}