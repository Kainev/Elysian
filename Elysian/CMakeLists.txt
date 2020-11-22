set(
    source_list
    "include/Elysian.h"

    "include/Elysian/Core/Application.h"
    "include/Elysian/Core/pch.h"
    "include/Elysian/Core/Engine.h"
    "include/Elysian/Core/Platform.h"
    "include/Elysian/Core/Assert.h"
    "include/Elysian/Core/Logging.h"

    "src/Elysian/Core/Logging.cpp"
    "src/Elysian/Core/Application.cpp"

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
                                          vendor/glfw/include)

add_subdirectory(vendor/spdlog)
add_subdirectory(vendor/glfw)

target_link_libraries(Elysian PRIVATE glfw)

target_include_directories(Elysian PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")

target_compile_definitions(Elysian PUBLIC ELYSIAN_VERSION_MAJOR=0
                                          ELYSIAN_VERSION_MINOR=1
                                          ELYSIAN_VERSION_PATCH=0
                                          "$<$<CONFIG:DEBUG>:DEBUG_BUILD>")

target_precompile_headers(Elysian PRIVATE "include/Elysian/Core/pch.h")