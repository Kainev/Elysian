cmake_minimum_required(VERSION 3.12)
project(Elysian VERSION 0.1.0)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

add_subdirectory(Elysian)
add_subdirectory(Application)

set_target_properties(glfw uninstall spdlog 
	PROPERTIES
	FOLDER vendor
)