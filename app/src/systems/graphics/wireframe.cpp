#include "wireframe.hpp"
#include "../../components/transform.hpp"
#include "../../components/object.hpp"
#include "../../components/camera.hpp"

#include "math/vector3.hpp"
#include "graphics/renderer.hpp"
#include "math/utils.hpp"

#include <imgui.h>

Wireframe::Wireframe(float fov, float near, float far) : _projection(utils::getProjectionMatrix(near, far, fov)) {}

void Wireframe::init(entt::registry& registry) {
    _registry = &registry;

    auto& renderer = Renderer::getInstance();
    _width = renderer.getWidth();
    _height = renderer.getHeight();
}

void Wireframe::update(float deltaTime) {
    auto& renderer = Renderer::getInstance();

    auto&& [_, camTrans] = *_registry->view<Transform, Camera>().each().begin();

    static bool drawAxis = true;

    ImGui::Begin("Renderer");
    ImGui::Checkbox("Test", &drawAxis);
    if (ImGui::CollapsingHeader("Camera Transform")) {
        ImGui::Text("Translation");
        ImGui::SliderFloat("Tx", &camTrans.Translation.X, -10, 10);
        ImGui::SliderFloat("Ty", &camTrans.Translation.Y, -10, 10);
        ImGui::SliderFloat("Tz", &camTrans.Translation.Z, -10, 10);
        ImGui::Text("Rotation");
        ImGui::SliderFloat("Rx", &camTrans.Rotation.X, -10, 10);
        ImGui::SliderFloat("Ry", &camTrans.Rotation.Y, -10, 10);
        ImGui::SliderFloat("Rz", &camTrans.Rotation.Z, -10, 10);
        ImGui::Text("Scale");
        ImGui::SliderFloat("Sx", &camTrans.Scale.X, -10, 10);
        ImGui::SliderFloat("Sy", &camTrans.Scale.Y, -10, 10);
        ImGui::SliderFloat("Sz", &camTrans.Scale.Z, -10, 10);
    }
    ImGui::End();
    auto vp = camTrans.GetMatrix() * _projection;

    for (auto&& [entity, transform, object] : _registry->group<Transform, Object>().each()) {
        auto mvp = (transform.GetMatrix() * vp);

        for (int i = 0; i < object.Indices.size(); i += 3) {
            Vector3 v0 = object.Vertices[object.Indices[i] - 1];
            Vector3 v1 = object.Vertices[object.Indices[i+1] - 1];
            Vector3 v2 = object.Vertices[object.Indices[i+2] - 1];

            v0 *= mvp;
            v1 *= mvp;
            v2 *= mvp;

            if (v0.Z == 0 || v1.Z == 0 || v2.Z == 0) {
                continue;
            }

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