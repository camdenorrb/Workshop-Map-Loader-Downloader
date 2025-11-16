cmake_minimum_required(VERSION 3.20)

project(WorkshopMapLoader LANGUAGES CXX)

if(NOT WIN32)
    message(FATAL_ERROR "WorkshopMapLoader can only be built on Windows.")
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(BAKKESMOD_SDK_PATH "" CACHE PATH "Path to the bakkesmodsdk folder (contains include/ and lib/)")
if(NOT BAKKESMOD_SDK_PATH)
    if(DEFINED ENV{BAKKESMOD_SDK_PATH})
        set(BAKKESMOD_SDK_PATH $ENV{BAKKESMOD_SDK_PATH})
    else()
        message(FATAL_ERROR "Set BAKKESMOD_SDK_PATH to the root of your bakkesmodsdk installation.")
    endif()
endif()

if(NOT EXISTS "${BAKKESMOD_SDK_PATH}/include/bakkesmod/plugin/bakkesmodplugin.h")
    message(FATAL_ERROR "BAKKESMOD_SDK_PATH (${BAKKESMOD_SDK_PATH}) does not look like a valid bakkesmodsdk directory.")
endif()

set(LIBRARIES_USED_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Pluginx64/LibrariesUsed")

set(SOURCES
    Pluginx64/pch.cpp
    Pluginx64/WorkshopMapLoader.cpp
    Pluginx64/WorkshopMapLoaderGUI.cpp
    Pluginx64/WorkshopMapLoaderSettingsGUI.cpp
    Pluginx64/Gamepad.cpp
    Pluginx64/IMGUI/imgui.cpp
    Pluginx64/IMGUI/imgui_demo.cpp
    Pluginx64/IMGUI/imgui_draw.cpp
    Pluginx64/IMGUI/imgui_widgets.cpp
    Pluginx64/IMGUI/imgui_impl_dx11.cpp
    Pluginx64/IMGUI/imgui_impl_win32.cpp
    Pluginx64/IMGUI/imgui_additions.cpp
    Pluginx64/IMGUI/imguivariouscontrols.cpp
    Pluginx64/IMGUI/imgui_rangeslider.cpp
    Pluginx64/IMGUI/imgui_searchablecombo.cpp
    Pluginx64/IMGUI/imgui_timeline.cpp
)

add_library(WorkshopMapLoader SHARED ${SOURCES})

target_include_directories(WorkshopMapLoader PRIVATE
    Pluginx64
    Pluginx64/IMGUI
    "${LIBRARIES_USED_DIR}/include"
    "${BAKKESMOD_SDK_PATH}/include"
)

target_link_directories(WorkshopMapLoader PRIVATE
    "${LIBRARIES_USED_DIR}/lib"
    "${BAKKESMOD_SDK_PATH}/lib"
)

target_link_libraries(WorkshopMapLoader PRIVATE
    pluginsdk
    cpr
    jsoncpp
    libcurl
    zlib
    urlmon
    Ws2_32
    Crypt32
    Wldap32
    Advapi32
    Normaliz
    Xinput
    Shell32
    User32
    d3d11
    dxgi
    d3dcompiler
)

if(MSVC)
    add_compile_options(/MP /W3 /wd4996)
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
endif()

target_precompile_headers(WorkshopMapLoader PRIVATE Pluginx64/pch.h)

set_target_properties(WorkshopMapLoader PROPERTIES
    OUTPUT_NAME WorkshopMapLoader
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/plugins"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/plugins"
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/plugins"
)
