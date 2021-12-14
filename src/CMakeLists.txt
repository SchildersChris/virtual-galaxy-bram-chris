# -----------------------------------------------------------------------------
#  Library setup
# -----------------------------------------------------------------------------

file(GLOB HEADER_LIST CONFIGURE_DEPENDS "${PROJECT_SOURCE_DIR}/include/*.hpp")

FetchContent_Declare(sdl GIT_REPOSITORY https://github.com/libsdl-org/SDL.git GIT_TAG release-2.0.16)
FetchContent_Declare(sdl-image GIT_REPOSITORY https://github.com/42IN7SPICg/SDL_image.git GIT_TAG re-release-2.0.5)

FetchContent_MakeAvailable(sdl)
FetchContent_MakeAvailable(sdl-image)

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


add_library(virtual-galaxy
    math/vector3.cpp
    math/vector2.cpp
    math/matrix4x4.cpp
    graphics/renderer.cpp
    utils/input.cpp
    utils/color.cpp
    utils/data.cpp
    ${IMGUI}
    ${HEADER_LIST})

target_compile_features(virtual-galaxy PUBLIC cxx_std_17)
target_link_libraries(virtual-galaxy PRIVATE SDL2 SDL2_image)

target_include_directories(virtual-galaxy
        PUBLIC
        ../include
        ${sdl_SOURCE_DIR}/include
        ${sdl-image_SOURCE_DIR}
        ${imgui_DIR}
        ${imgui-sdl_DIR})

target_compile_features(virtual-galaxy PUBLIC cxx_std_11)

source_group(
  TREE "${PROJECT_SOURCE_DIR}/include"
  PREFIX "Header Files"
  FILES ${HEADER_LIST})
