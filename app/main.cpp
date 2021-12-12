#include "graphics/renderer.hpp"
#include "utils/input.hpp"

int main() {
    auto& renderer = Renderer::getInstance();
    auto& input = Input::getInstance();

    renderer.init("Virtual Galaxy", false, 800, 600);
    input.init();

    renderer.setClearColor(0, 0, 255);

    while (!input.isQuit()) {
        auto buffer = renderer.beginFrame();

        // Draw red line of 100 pixels
        int32 x = 100, y = 100;
        for (int32 i = 0; i < 100; ++i) {
            buffer.setPixel(x + i, y + i, 255, 0, 0, 255);
        }

        renderer.endFrame();
        input.update();
    }

    input.terminate();
    renderer.terminate();
    return 0;
}
