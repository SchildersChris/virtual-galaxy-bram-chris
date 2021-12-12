#include "demo.hpp"
#include "../components/transform.hpp"
#include "../components/object.hpp"

void Demo::init(entt::registry& registry) {
    auto entity = registry.create();
    registry.emplace<Transform>(entity, Transform {
        { 0.f, 0.f, 0.f},
        { 0.f, 0.f, 0.f},
        { 0.f, 0.f, 0.f}
    });

    auto object = registry.emplace<Object>(entity, Object {});

    // Adding a triangle object
    object.Vertices.emplace_back(-1.f, -1.f, 1.f); // Left point
    object.Vertices.emplace_back(1.f, -1.f, 1.f); // Right point
    object.Vertices.emplace_back(0.f, 1.f, 1.f); // Top (middle) point
}

void Demo::update(float deltaTime, Buffer& frame) {}

void Demo::terminate() {}
