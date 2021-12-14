#include "graphics/renderer.hpp"
#include "utils/input.hpp"
#include "systems/system.hpp"
#include "systems/demo.hpp"
#include "systems/movement.hpp"
#include "systems/render.hpp"
#include "systems/collision.hpp"

#include <memory>
#include <chrono>

using ms = std::chrono::duration<float, std::milli>;
using c = std::chrono::steady_clock;

int main() {
    /*
     * Setup
     */
    std::vector<std::unique_ptr<System>> systems;

    systems.emplace_back(std::make_unique<Demo>());
    systems.emplace_back(std::make_unique<Collision>());
    systems.emplace_back(std::make_unique<Movement>());
    systems.emplace_back(std::make_unique<Render>());

    auto& renderer = Renderer::getInstance();
    auto& input = Input::getInstance();

    renderer.init("Virtual Galaxy", false, 1920, 1080);
    input.init();

    entt::registry registry;

    for (auto& s : systems) {
        s->init(registry);
    }

    auto deltaTime = 0.f;

    /*
     * Main loop
     */
    while (!input.isQuit()) {
        auto start = c::now();

        input.update();

        renderer.beginFrame(deltaTime);
        // Todo: Add delta time
        for (auto& s : systems) {
            s->update(deltaTime);
        }
        renderer.endFrame();

        auto end = c::now();
        deltaTime = ms(end - start).count();
    }

    /*
     * Shutdown
     */
    for (auto& s : systems) {
        s->terminate();
    }

    input.terminate();
    renderer.terminate();
    return 0;
}
