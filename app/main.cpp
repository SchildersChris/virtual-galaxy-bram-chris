#include "graphics/renderer.hpp"
#include "utils/input.hpp"
#include "systems/system.hpp"
#include "systems/demo.hpp"
#include "systems/movement.hpp"
#include "systems/render.hpp"
#include "systems/collision.hpp"

#include <memory>

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

    /*
     * Runtime
     */
    while (!input.isQuit()) {
        input.update();
        auto frame = renderer.beginFrame();

        // Todo: Add delta time
        for (auto& s : systems) {
            s->update(0.f, frame);
        }

        renderer.endFrame();
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
