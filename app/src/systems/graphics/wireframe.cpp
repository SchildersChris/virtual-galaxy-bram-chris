#include "wireframe.hpp"
#include "../../components/transform.hpp"
#include "../../components/object.hpp"

#include "math/vector3.hpp"
#include "graphics/renderer.hpp"

#include <cmath>
#include <imgui.h>

void Wireframe::init(entt::registry& registry) {
    _registry = &registry;

    auto& renderer = Renderer::getInstance();
    _width = renderer.getWidth();
    _height = renderer.getHeight();
}

void Wireframe::update(float deltaTime) {
    auto& renderer = Renderer::getInstance();

    static float angle = .3f;
    ImGui::Begin("Renderer Window");
    ImGui::SliderFloat("Rotate Y", &angle, -1, 1);
    ImGui::End();

    float mat[16] = {
            std::cos(angle), 0, std::sin(angle), 0,
            0, 1, 0, 0,
            -std::sin(angle), 0, std::cos(angle), 0,
            0, 0, 5, 1
    };
    auto matrix = Matrix4x4(mat);

    for (auto&& [entity, transform, object] : _registry->group<Transform, Object>().each()) {
        for (int i = 0; i < object.Indices.size(); i += 3) {
            Vector3 v0 = object.Vertices[object.Indices[i] - 1];
            Vector3 v1 = object.Vertices[object.Indices[i+1] - 1];
            Vector3 v2 = object.Vertices[object.Indices[i+2] - 1];

            v0 *= matrix;
            v1 *= matrix;
            v2 *= matrix;

            Vector2 r0 = toRaster(v0.proj());
            Vector2 r1 = toRaster(v1.proj());
            Vector2 r2 = toRaster(v2.proj());

            renderer.drawLine(r0, r1, Color::white());
            renderer.drawLine(r1, r2, Color::white());
            renderer.drawLine(r2, r0, Color::white());
        }
    }
}

void Wireframe::terminate() {}

Vector2 Wireframe::toRaster(const Vector2& v) const {
    return {
        (1 + v.X) * 0.5f * static_cast<float>(_width),
        (1 - v.Y) * 0.5f * static_cast<float>(_height)
    };
}