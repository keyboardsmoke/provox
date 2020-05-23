cmake_minimum_required(VERSION 3.10)
project(imgui)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

add_library(imgui 
    ${CMAKE_SOURCE_DIR}/contrib/imgui/imconfig.h
    ${CMAKE_SOURCE_DIR}/contrib/imgui/imgui.cpp
    ${CMAKE_SOURCE_DIR}/contrib/imgui/imgui.h
    ${CMAKE_SOURCE_DIR}/contrib/imgui/imgui_demo.cpp
    ${CMAKE_SOURCE_DIR}/contrib/imgui/imgui_draw.cpp
    ${CMAKE_SOURCE_DIR}/contrib/imgui/imgui_internal.h
    ${CMAKE_SOURCE_DIR}/contrib/imgui/imgui_widgets.cpp
    ${CMAKE_SOURCE_DIR}/contrib/imgui/imstb_rectpack.h
    ${CMAKE_SOURCE_DIR}/contrib/imgui/imstb_textedit.h
    ${CMAKE_SOURCE_DIR}/contrib/imgui/imstb_truetype.h
)
target_include_directories(imgui PUBLIC ${CMAKE_SOURCE_DIR}/contrib/imgui)

add_definitions(-DUNICODE -D_UNICODE)

set_target_properties(imgui PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
)
