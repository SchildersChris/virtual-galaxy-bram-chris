#include <math/utils.hpp>
#include <imgui.h>
#include "rendering-pipeline.hpp"
#include "../components/camera.hpp"
#include "../components/transform.hpp"

#include "graphics/renderer.hpp"

void RenderingPipeline::init(entt::registry& registry) {
    _registry = &registry;

    auto& renderer = Renderer::getInstance();
    _projection = utils::getProjectionMatrix(
            _fov, _near, _far,static_cast<float>(renderer.getWidth()) / static_cast<float>(renderer.getHeight()));

    for (auto& elem : Elements) {
        elem->init(registry, _near, _far);
    }
}

void RenderingPipeline::update(float deltaTime) {
    if (!_registry) { return; }


    auto&& [_, camTrans, camera] = *_registry->view<Transform, Camera>().each().begin();

    ImGui::Begin("Rendering Pipeline");

    ImGui::SliderFloat("Look At X", &camera.LookAt.X, -5.f, 5.f);
    ImGui::SliderFloat("Look At Y", &camera.LookAt.Y, -5.f, 5.f);
    ImGui::SliderFloat("Look At Z", &camera.LookAt.Z, -5.f, 5.f);

    for (auto& elem : Elements) {
        elem->update(deltaTime);
    }
    ImGui::End();

    auto vp = _projection * camTrans.getMatrix() * calculateCamera(camera);

    for (auto&& [entity, transform, object] : _registry->group<Transform, Object>().each()) {
        auto m = transform.getMatrix();

        for (auto& elem : Elements) {
            elem->updateObject(entity, vp, m, object);
        }
    }

}

void RenderingPipeline::terminate() {
    for (auto& elem : Elements) {
        elem->terminate();
    }
}

Matrix4x4 RenderingPipeline::calculateCamera(const Camera& camera) {
    auto direction = camera.Eye - camera.LookAt;

    auto up = Vector3 { 0, 1, 0 };
    auto right = up.cross(direction).normalize();
    up = direction.cross(right).normalize();

    return Matrix4x4::lookAt(right, up, direction);
}
