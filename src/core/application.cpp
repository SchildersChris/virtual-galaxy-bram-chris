#include "core/application.hpp"
#include "graphics/renderer.hpp"
#include "core/input.hpp"

#include "entity/registry.hpp"
#include <chrono>

using ms = std::chrono::duration<float, std::milli>;
using c = std::chrono::steady_clock;

void Application::run() {
    auto& renderer = Renderer::getInstance();
    auto& input = Input::getInstance();

    renderer.init(_title, false, 1920, 1080);
    input.init();

    entt::registry registry;

    /*
     * Initialize systems
     */
    for (auto& s : Systems) {
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
        for (auto& s : Systems) {
            s->update(deltaTime);
        }
        renderer.endFrame();

        auto end = c::now();
        deltaTime = ms(end - start).count();
    }

    /*
     * Shutdown systems
     */
    for (auto& s : Systems) {
        s->terminate();
    }

    input.terminate();
    renderer.terminate();
}

Application::Application(std::string title) : _title(std::move(title)) {}

void Application::quit() {
    SDL_Event event;
    event.type = SDL_QUIT;
    SDL_PushEvent(&event);
}
