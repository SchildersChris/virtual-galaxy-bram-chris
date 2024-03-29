# -----------------------------------------------------------------------------
#  Application setup
# -----------------------------------------------------------------------------

file(COPY assets DESTINATION .)

add_executable(app
    src/app.cpp
    src/app.hpp
    src/systems/rendering/rasterizer.cpp
    src/systems/rendering/rasterizer.hpp
    src/systems/rendering/wireframe.cpp
    src/systems/rendering/wireframe.hpp
    src/systems/rendering/collision.cpp
    src/systems/rendering/collision.hpp
    src/systems/rendering/axis.cpp
    src/systems/rendering/axis.hpp
    src/systems/rendering/rendering.cpp
    src/systems/rendering/rendering.hpp
    src/systems/movement.cpp
    src/systems/movement.hpp
    src/systems/rendering-pipeline.cpp
    src/systems/rendering-pipeline.hpp
    src/systems/scene.cpp
    src/systems/scene.hpp
    src/systems/shooting.cpp
    src/systems/shooting.hpp
    src/systems/scaling.cpp
    src/systems/scaling.hpp
    src/components/transform.hpp
    src/components/object.hpp
    src/components/collider.hpp
    src/components/bullet.hpp
    src/utils/wavefront-object.cpp
    src/utils/wavefront-object.hpp
)

target_compile_features(app PRIVATE cxx_std_17)
target_link_libraries(app PRIVATE virtual-galaxy)
target_include_directories(app PUBLIC extern)


if(MINGW)
    add_custom_command(TARGET app PRE_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_BINARY_DIR}/virtual-galaxy-deps/
            $<TARGET_FILE_DIR:app>)
endif()