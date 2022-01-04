# -----------------------------------------------------------------------------
#  Application setup
# -----------------------------------------------------------------------------

file(COPY assets DESTINATION .)

add_executable(app
    src/app.cpp
    src/app.hpp
    src/systems/graphics/rasterizer.cpp
    src/systems/graphics/rasterizer.hpp
    src/systems/graphics/wireframe.cpp
    src/systems/graphics/wireframe.hpp
    src/systems/movement.cpp
    src/systems/movement.hpp
    src/systems/collision.cpp
    src/systems/collision.hpp
    src/systems/scene.cpp
    src/systems/scene.hpp
        src/systems/view.cpp
        src/systems/view.hpp
    src/components/transform.hpp
    src/components/object.hpp
    src/utils/wavefront-object.cpp
    src/utils/wavefront-object.hpp
)

target_compile_features(app PRIVATE cxx_std_17)
target_link_libraries(app PRIVATE virtual-galaxy)
target_include_directories(app PUBLIC extern)