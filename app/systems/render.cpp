#include "render.hpp"

void Render::init(entt::registry& registry) {

}

void Render::update(float deltaTime, Buffer& frame) {
    // Draw red line of 100 pixels
    int32 x = 100, y = 100;
    for (int32 i = 0; i < 100; ++i) {
        frame.setPixel(x + i, y + i, 255, 0, 0, 255);
    }
}
