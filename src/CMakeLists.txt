# -----------------------------------------------------------------------------
#  Library setup
# -----------------------------------------------------------------------------

file(GLOB HEADER_LIST CONFIGURE_DEPENDS "${PROJECT_SOURCE_DIR}/include/*.hpp")

FetchContent_Declare(sdl GIT_REPOSITORY https://github.com/libsdl-org/SDL.git GIT_TAG release-2.0.16)
FetchContent_Declare(sdl-image GIT_REPOSITORY https://github.com/42IN7SPICg/SDL_image.git GIT_TAG re-release-2.0.5)

FetchContent_MakeAvailable(sdl)
FetchContent_MakeAvailable(sdl-image)

add_library(virtual-galaxy
    math/vector3.cpp
    math/matrix4x4.cpp
    ${HEADER_LIST})

target_compile_features(virtual-galaxy PUBLIC cxx_std_17)
target_link_libraries(virtual-galaxy PRIVATE SDL2 SDL2_image)

target_include_directories(virtual-galaxy
        PUBLIC
        ../include
        PRIVATE
        ${sdl_SOURCE_DIR}/include
        ${sdl-image_SOURCE_DIR}
        ${imgui_DIR}
        ${imgui-sdl_DIR})

target_compile_features(virtual-galaxy PUBLIC cxx_std_11)

source_group(
  TREE "${PROJECT_SOURCE_DIR}/include"
  PREFIX "Header Files"
  FILES ${HEADER_LIST})
