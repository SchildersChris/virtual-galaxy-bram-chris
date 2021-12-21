#include "app.hpp"
#include "systems/scene.hpp"
#include "systems/collision.hpp"
#include "systems/movement.hpp"
#include "systems/render.hpp"

App::App() : Application("Virtual Galaxy") {
    /*
     * Constructing the application runtime systems
     */
    Systems.emplace_back(std::make_unique<Scene>());
    Systems.emplace_back(std::make_unique<Collision>());
    Systems.emplace_back(std::make_unique<Movement>());
    Systems.emplace_back(std::make_unique<Render>());
}
