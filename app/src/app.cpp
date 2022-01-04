#include "app.hpp"
#include "systems/scene.hpp"
#include "systems/collision.hpp"
#include "systems/movement.hpp"
#include "systems/graphics/wireframe.hpp"
#include "systems/graphics/rasterizer.hpp"
#include "systems/shooting.hpp"

App::App() : Application("Virtual Galaxy") {
    /*
     * Constructing the application runtime systems
     */
    Systems.emplace_back(std::make_unique<Scene>());
    Systems.emplace_back(std::make_unique<Collision>());
    Systems.emplace_back(std::make_unique<Movement>());
    Systems.emplace_back(std::make_unique<Shooting>());

    Systems.emplace_back(std::make_unique<Rasterizer>(60, 3.f, 100.f));
//    Systems.emplace_back(std::make_unique<Wireframe>(60, 2.f, 100.f));
}

