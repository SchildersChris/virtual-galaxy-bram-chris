#ifndef VIRTUAL_GALAXY_BULLET_HPP
#define VIRTUAL_GALAXY_BULLET_HPP

struct Bullet {
    explicit Bullet(Vector3 heading, float maxAliveMs = 2000.f) : Heading(heading), MaxAliveMs(maxAliveMs), AliveMs(0) {}

    Vector3 Heading;
    float AliveMs;
    float MaxAliveMs;
};

#endif //VIRTUAL_GALAXY_BULLET_HPP
