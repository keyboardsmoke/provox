cmake_minimum_required(VERSION 3.10)
project(provox)

include_directories(${CMAKE_SOURCE_DIR})

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(MAIN_HEADERS
        framework.h
        pch.h
        platform.h
        types.h
)

set(MAIN_SOURCES pch.cpp provox.cpp)

set(ENGINE_HEADERS
        Engine/Camera.h
        Engine/Entity.h
        Engine/Voxel.h)

set(ENGINE_SOURCES
        Engine/Camera.cpp
        Engine/Entity.cpp
        Engine/Voxel.cpp)

set(RENDERER_HEADERS Renderer/Renderer.h)
set(RENDERER_SOURCES Renderer/Renderer.cpp)

set(DX9_RENDERER_HEADERS Renderer/DX9Renderer/DX9Renderer.h)
set(DX9_RENDERER_SOURCES Renderer/DX9Renderer/DX9Renderer.cpp)

set(OGL_RENDERER_HEADERS Renderer/GLRenderer/GLRenderer.h)
set(OGL_RENDERER_SOURCES Renderer/GLRenderer/GLRenderer.cpp)

set(TYPES_HEADERS
        Types/AABB2D.h
        Types/AABB3D.h
        Types/Bit.h
        Types/Color.h
        Types/FixedCompactifiedReal.h
        Types/FixedFractionalExponentReal.h
        Types/IEEE754.h
        Types/Matrix.h
        Types/OBB2D.h
        Types/OBB3D.h
        Types/Real.h
        Types/Vector2D.h
        Types/Vector3D.h
        Types/Vector4D.h)

set(TYPES_SOURCES 
        Types/Color.cpp
        Types/Real.cpp)

set(UI_HEADERS 
        UI/UICore.h
        UI/UIDebugWindow.h
        UI/UIStatsWindow.h
        UI/UIWindow.h)

set(UI_SOURCES
        UI/UICore.cpp
        UI/UIStatsWindow.cpp)

set(UI_RENDERERS_HEADERS
        UI/Renderers/DX9UICore.h)

set(UI_RENDERERS_SOURCES
        UI/Renderers/DX9UICore.cpp)

set(WINDOW_HEADERS
        Window/Window.h
        Window/Win32Window.h
        Window/XLibWindow.h)

set(WINDOW_SOURCES
        Window/Window.cpp
        Window/Win32Window.cpp
        Window/XLibWindow.cpp)

if (MSVC)
    source_group("provox" FILES ${MAIN_SOURCES} ${MAIN_HEADERS})
    source_group("provox\\Engine" FILES ${ENGINE_SOURCES} ${ENGINE_HEADERS})
    source_group("provox\\Renderer" FILES ${RENDERER_SOURCES} ${RENDERER_HEADERS})
    source_group("provox\\Renderer\\DX9Renderer" FILES ${DX9_RENDERER_SOURCES} ${DX9_RENDERER_HEADERS})
    source_group("provox\\Renderer\\GLRenderer" FILES ${OGL_RENDERER_SOURCES} ${OGL_RENDERER_HEADERS})
    source_group("provox\\Types" FILES ${TYPES_SOURCES} ${TYPES_HEADERS})
    source_group("provox\\UI" FILES ${UI_SOURCES} ${UI_HEADERS})
    source_group("provox\\UI\\Renderers" FILES ${UI_RENDERERS_SOURCES} ${UI_RENDERERS_HEADERS})
    source_group("provox\\Window" FILES ${WINDOW_SOURCES} ${WINDOW_HEADERS})
endif()

add_library(provox 
        ${MAIN_SOURCES} ${MAIN_HEADERS}
        ${ENGINE_SOURCES} ${ENGINE_HEADERS}
        ${RENDERER_SOURCES} ${RENDERER_HEADERS}
        ${DX9_RENDERER_SOURCES} ${DX9_RENDERER_HEADERS}
        ${OGL_RENDERER_SOURCES} ${OGL_RENDERER_HEADERS}
        ${TYPES_SOURCES} ${TYPES_HEADERS}
        ${UI_SOURCES} ${UI_HEADERS}
        ${UI_RENDERERS_SOURCES} ${UI_RENDERERS_HEADERS}
        ${WINDOW_SOURCES} ${WINDOW_HEADERS}
)

add_definitions(-DUNICODE -D_UNICODE)
target_link_libraries(provox imgui d3d9.lib)
target_include_directories(provox PUBLIC ${CMAKE_SOURCE_DIR}/contrib/imgui)

set_target_properties(provox PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
)

#[[
if(MSVC)
  target_compile_options(provox PRIVATE /W4 /WX)
else()
  target_compile_options(provox PRIVATE -Wall -Wextra -pedantic -Werror)
endif()]]#
