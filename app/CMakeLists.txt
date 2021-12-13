# -----------------------------------------------------------------------------
#  Application setup
# -----------------------------------------------------------------------------

FetchContent_Declare(entt GIT_REPOSITORY https://github.com/skypjack/entt.git GIT_TAG v3.8.1)
FetchContent_MakeAvailable(entt)

add_executable(app
    main.cpp
    systems/system.hpp
    systems/movement.cpp
    systems/movement.hpp
    systems/render.cpp
    systems/render.hpp
    systems/collision.cpp
    systems/collision.hpp
    systems/demo.cpp
    systems/demo.hpp
    components/transform.hpp
    components/object.hpp
)

target_compile_features(app PRIVATE cxx_std_17)
target_link_libraries(app PRIVATE virtual-galaxy)
target_include_directories(app PUBLIC ../extern ${entt_SOURCE_DIR}/src/entt)