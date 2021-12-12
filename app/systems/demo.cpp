#include "demo.hpp"

#include "math/vector3.hpp"

void Demo::init(entt::registry& registry) {
    Vector3 triangle[3] = {
            {-1.f, -1.f, 1.f}, // Left
            {1.f, -1.f, 1.f}, // Right
            {0.f, 1.f, 1.f} // Top
    };
}

void Demo::update(float deltaTime, Buffer& frame) {

}
