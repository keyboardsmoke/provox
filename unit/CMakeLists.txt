cmake_minimum_required(VERSION 3.16)
project(unit)

include_directories(${CMAKE_SOURCE_DIR})
include_directories(${CMAKE_SOURCE_DIR}/unit)
include_directories(${CMAKE_SOURCE_DIR}/ext/doctest)

set(UNIT_TESTS
        aabb_test.cpp
        bit_test.cpp
        bit_test.h
        color_test.cpp
        fixed_real.cpp
        ieee754_16.cpp
        ieee754_32.cpp
        ieee754_64.cpp
        obb_test.cpp
        real_test.cpp
        unit.cpp
        vector_test.cpp
)
        
add_definitions(-DUNICODE -D_UNICODE)

add_executable(unit ${UNIT_TESTS})
target_include_directories(unit PUBLIC ${CMAKE_SOURCE_DIR}/provox)
target_link_libraries(unit provox doctest)

set_target_properties(unit PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
)

#[[
if(MSVC)
  target_compile_options(unit PRIVATE /W4 /WX)
else()
  target_compile_options(unit PRIVATE -Wall -Wextra -pedantic -Werror)
endif()
]]#
