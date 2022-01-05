#ifndef VIRTUAL_GALAXY_SCALE_HPP
#define VIRTUAL_GALAXY_SCALE_HPP

struct Scale {
    explicit Scale(float speed = 0.0005f) : Speed(speed) {};

    float Speed;
    float Size {0};
};

#endif //VIRTUAL_GALAXY_SCALE_HPP
