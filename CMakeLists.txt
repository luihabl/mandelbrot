cmake_minimum_required(VERSION 3.11)
project(mandelbrot)

# C++ version
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(lib/tinysdl)
add_subdirectory(lib/imgui)

add_executable(mandelbrot 
src/main.cpp
${IMGUI_SRC}
)

include_directories(lib/imgui)
target_link_libraries(mandelbrot tinysdl)

if (EXISTS ${SDL2_DLL})
    add_custom_command(
        TARGET mandelbrot POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy ${SDL2_DLL} $<TARGET_FILE_DIR:mandelbrot>)
endif()