#include <graphics/renderer.hpp>
#include "render.hpp"
#include "../components/transform.hpp"
#include "../components/object.hpp"

void Render::init(entt::registry& registry) {
    _registry = &registry;

    // Setup z-buffer algorithm
    auto& renderer = Renderer::getInstance();

    _zBufferSize = renderer.getWidth() * renderer.getHeight();
    _zBuffer = new float[_zBufferSize];
}

void Render::update(float deltaTime, Buffer& frame) {
    if (!_registry || !_zBuffer) { return; }

    for (std::size_t i = 0; i < _zBufferSize; ++i) {
        _zBuffer[i] = far;
    }

    for (auto&& [entity, transform, object] : _registry->group<Transform, Object>().each()) {

    }

    // Draw red line of 100 pixels
//    int32 x = 100, y = 100;
//    for (int32 i = 0; i < 100; ++i) {
//        frame.setPixel(x + i, y + i, 255, 0, 0, 255);
//    }
}

void Render::terminate() {
    delete[] _zBuffer;
}
