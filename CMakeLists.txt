cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_C_COMPILER "/usr/bin/clang")
set(CMAKE_CXX_COMPILER "/usr/bin/clang++")

project(Application VERSION 1.0)

file(GLOB_RECURSE SRC_FILES src/*.cpp Vendor/src/*.cpp)

add_compile_options(-Wall -Wextra -Wpedantic -g)
add_executable(Application ${SRC_FILES})
target_include_directories(Application PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src ${CMAKE_CURRENT_SOURCE_DIR}/Vendor/include ${CMAKE_CURRENT_SOURCE_DIR}/Vendor/include/imgui)
TARGET_LINK_LIBRARIES(Application ${CMAKE_CURRENT_SOURCE_DIR}/Vendor/lib/libglfw3.a X11 GL openal)

