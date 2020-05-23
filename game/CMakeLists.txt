cmake_minimum_required(VERSION 3.16)
project(game)

set(CMAKE_WIN32_EXECUTABLE ON)

include_directories(${CMAKE_SOURCE_DIR})

set(GAME_FILES
        game.cpp
        game.h
        targetver.h
        framework.h
)

add_definitions(-DUNICODE -D_UNICODE)

add_executable(game ${GAME_FILES})
target_link_libraries(game provox)
target_include_directories(game PUBLIC ${CMAKE_SOURCE_DIR}/provox)

set_target_properties(game PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
)

#[[
if(MSVC)
  target_compile_options(game PRIVATE /W4 /WX)
else()
  target_compile_options(game PRIVATE -Wall -Wextra -pedantic -Werror)
endif()
]]#
