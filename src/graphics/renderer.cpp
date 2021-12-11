#include "graphics/renderer.hpp"

Renderer Renderer::_instance;
Renderer& Renderer::GetInstance() {
    return _instance;
}

Frame Renderer::BeginFrame() {
    return Frame(*this);
}
