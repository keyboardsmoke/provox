cmake_minimum_required(VERSION 3.10)
project(provox)

if (NOT MSVC)
    set(CMAKE_EXE_LINKER_FLAGS "-static")
endif()

add_subdirectory(${CMAKE_SOURCE_DIR}/contrib/doctest)
add_subdirectory(${CMAKE_SOURCE_DIR}/imgui)
add_subdirectory(${CMAKE_SOURCE_DIR}/provox)
add_subdirectory(${CMAKE_SOURCE_DIR}/game)
add_subdirectory(${CMAKE_SOURCE_DIR}/unit)
