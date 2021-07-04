set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(
    source_list
    "include/Elysian.h"

    "vendor/glad/glad/glad.h"

    "include/Elysian/Core/pch.h"
    "include/Elysian/Core/Assert.h"
    "include/Elysian/Core/Platform.h"
    "include/Elysian/Core/Logging.h"
    "include/Elysian/Core/Engine.h"
    "include/Elysian/Core/Application.h"
    "include/Elysian/Core/Window.h"
    "include/Elysian/Core/EventManager.h"
    
    "include/Elysian/Input/Keys.h"

    "include/Elysian/Render/GraphicsContext.h"

    "include/Elysian/Platform/GLFWindow.h"
    "include/Elysian/Platform/OpenGL/OGLContext.h"

    "include/Elysian/Event/KeyEvent.h"
    "include/Elysian/Event/MouseEvent.h"
    "include/Elysian/Event/WindowEvent.h"
    

    "src/Elysian/Core/Application.cpp"
    "src/Elysian/Core/Logging.cpp"
    "src/Elysian/Core/Window.cpp"

    "src/Elysian/Render/GraphicsContext.cpp"

    "src/Elysian/Platform/GLFWindow.cpp"
    "src/Elysian/Platform/OpenGL/OGLContext.cpp"

    "vendor/glad/glad.c"

)

add_library(
	Elysian STATIC
	${source_list}
)

function(assign_source_group)
    foreach(_source IN ITEMS ${ARGN})
        if (IS_ABSOLUTE "${_source}")
            file(RELATIVE_PATH _source_rel "${CMAKE_CURRENT_SOURCE_DIR}" "${_source}")
        else()
            set(_source_rel "${_source}")
        endif()
        get_filename_component(_source_path "${_source_rel}" PATH)
        string(REPLACE "/" "\\" _source_path_msvc "${_source_path}")
        source_group("${_source_path_msvc}" FILES "${_source}")
    endforeach()
endfunction(assign_source_group)

assign_source_group(${source_list})

target_include_directories(Elysian PUBLIC vendor/spdlog/include
                                          vendor/glfw/include
                                          vendor/glad
                                          vendor/KHR)

add_subdirectory(vendor/spdlog)
add_subdirectory(vendor/glfw)

target_link_libraries(Elysian PRIVATE glfw)

target_include_directories(Elysian PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")

target_compile_definitions(Elysian PUBLIC ELYSIAN_VERSION_MAJOR=0
                                          ELYSIAN_VERSION_MINOR=1
                                          ELYSIAN_VERSION_PATCH=0
                                          "$<$<CONFIG:DEBUG>:DEBUG_BUILD>")
