# -----------------------------------------------------------------------------
#  Application setup
# -----------------------------------------------------------------------------

file(COPY assets DESTINATION .)

add_executable(app
    src/app.cpp
    src/app.hpp
    src/pipelines/object/rasterizer.cpp
    src/pipelines/object/rasterizer.hpp
    src/pipelines/object/wireframe.cpp
    src/pipelines/object/wireframe.hpp
    src/pipelines/object/collision.cpp
    src/pipelines/object/collision.hpp
    src/pipelines/object/axis.cpp
    src/pipelines/object/axis.hpp
    src/systems/movement.cpp
    src/systems/movement.hpp
    src/systems/object-pipeline.cpp
    src/systems/object-pipeline.hpp
    src/systems/scene.cpp
    src/systems/scene.hpp
    src/systems/shooting.cpp
    src/systems/shooting.hpp
    src/components/transform.hpp
    src/components/object.hpp
    src/components/bullet.hpp
    src/utils/wavefront-object.cpp
    src/utils/wavefront-object.hpp
)

target_compile_features(app PRIVATE cxx_std_17)
target_link_libraries(app PRIVATE virtual-galaxy)
target_include_directories(app PUBLIC extern)