#ifndef VIRTUAL_GALAXY_COLLIDER_HPP
#define VIRTUAL_GALAXY_COLLIDER_HPP

#include <functional>

struct Collider {
    explicit Collider(std::function<void(entt::entity)> onCollide) : OnCollide(std::move(onCollide)) {}

    std::function<void(entt::entity)> OnCollide;
};

#endif //VIRTUAL_GALAXY_COLLIDER_HPP
