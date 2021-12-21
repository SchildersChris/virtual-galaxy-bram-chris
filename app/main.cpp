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
     * Setup application and systems
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

    /*
     * Initialize systems
     */
    for (auto& s : systems) {
        s->init(registry);
    }

    /*
     * Main loop
     */
    float deltaTime = 0.f;
    while (!input.isQuit()) {
        auto start = c::now();

        input.update();

        renderer.beginFrame(deltaTime);
        for (auto& s : systems) {
            s->update(deltaTime);
        }
        renderer.endFrame();

        auto end = c::now();
        deltaTime = ms(end - start).count();
    }

    /*
     * Shutdown systems
     */
    for (auto& s : systems) {
        s->terminate();
    }

    input.terminate();
    renderer.terminate();
    return 0;
}
