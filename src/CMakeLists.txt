# -----------------------------------------------------------------------------
#  Library setup
# -----------------------------------------------------------------------------

file(GLOB HEADER_LIST CONFIGURE_DEPENDS "${PROJECT_SOURCE_DIR}/include/*.hpp")

FetchContent_Declare(sdl GIT_REPOSITORY https://github.com/libsdl-org/SDL.git GIT_TAG release-2.0.16)
FetchContent_Declare(sdl-image GIT_REPOSITORY https://github.com/42IN7SPICg/SDL_image.git GIT_TAG re-release-2.0.5)
FetchContent_Declare(entt GIT_REPOSITORY https://github.com/skypjack/entt.git GIT_TAG v3.8.1)

FetchContent_MakeAvailable(sdl)
FetchContent_MakeAvailable(sdl-image)
FetchContent_MakeAvailable(entt)

set(imgui_DIR ${PROJECT_SOURCE_DIR}/extern/imgui/)
set(imgui-sdl_DIR ${PROJECT_SOURCE_DIR}/extern/imgui-sdl)

set(IMGUI
    ${imgui_DIR}/imgui.h
    ${imgui_DIR}/imgui.cpp
    ${imgui_DIR}/imgui_tables.cpp
    ${imgui_DIR}/imgui_internal.h
    ${imgui_DIR}/imgui_widgets.cpp
    ${imgui_DIR}/imgui_draw.cpp
    ${imgui_DIR}/imgui_demo.cpp
    ${imgui_DIR}/backends/imgui_impl_sdl.h
    ${imgui_DIR}/backends/imgui_impl_sdl.cpp
    ${imgui-sdl_DIR}/imgui_sdl.cpp
    ${imgui-sdl_DIR}/imgui_sdl.h)


add_library(virtual-galaxy STATIC
    core/application.cpp
    core/input.cpp
    core/data.cpp
    graphics/color.cpp
    graphics/renderer.cpp
    math/vector4.cpp
    math/vector3.cpp
    math/vector2.cpp
    math/matrix4x4.cpp
    math/utils.cpp
    ${IMGUI}
    ${HEADER_LIST})

target_compile_features(virtual-galaxy PUBLIC cxx_std_17)
target_link_libraries(virtual-galaxy PRIVATE SDL2-static SDL2_image EnTT)

target_include_directories(virtual-galaxy
        PUBLIC
        ../include
        ${sdl_SOURCE_DIR}/include
        ${sdl-image_SOURCE_DIR}
        ${imgui_DIR}
        ${imgui-sdl_DIR}
        ${entt_SOURCE_DIR}/src/entt)

target_compile_features(virtual-galaxy PUBLIC cxx_std_11)


if (MINGW)
    set(dep "${CMAKE_CXX_COMPILER}/../libwinpthread-1.dll"
            "${CMAKE_CXX_COMPILER}/../libgcc_s_seh-1.dll"
            "${CMAKE_CXX_COMPILER}/../libstdc++-6.dll"
            "${CMAKE_CXX_COMPILER}/../zlib1.dll"
            "${CMAKE_CXX_COMPILER}/../libbrotlidec.dll"
            "${CMAKE_CXX_COMPILER}/../libcrypto-1_1-x64.dll"
            "${CMAKE_CXX_COMPILER}/../libssl-1_1-x64.dll"
            "${CMAKE_CXX_COMPILER}/../libzstd.dll"
            "${CMAKE_CXX_COMPILER}/../libbrotlicommon.dll"
            "${CMAKE_CXX_COMPILER}/../libiconv-2.dll"
            "${CMAKE_CXX_COMPILER}/../libintl-8.dll"
            "${CMAKE_CXX_COMPILER}/../libfreetype-6.dll"
            "${CMAKE_CXX_COMPILER}/../libharfbuzz-0.dll"
            "${CMAKE_CXX_COMPILER}/../libbz2-1.dll"
            "${CMAKE_CXX_COMPILER}/../libpng16-16.dll"
            "${CMAKE_CXX_COMPILER}/../libglib-2.0-0.dll"
            "${CMAKE_CXX_COMPILER}/../libgraphite2.dll"
            "${CMAKE_CXX_COMPILER}/../libpcre-1.dll"
            )

    foreach (file ${dep})
        add_custom_command(TARGET virtual-galaxy POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy_if_different
                ${file}
                ${CMAKE_BINARY_DIR}/virtual-galaxy-deps)
    endforeach ()
endif ()

source_group(
  TREE "${PROJECT_SOURCE_DIR}/include"
  PREFIX "Header Files"
  FILES ${HEADER_LIST})
