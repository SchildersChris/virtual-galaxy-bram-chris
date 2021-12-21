#ifndef VIRTUAL_GALAXY_TEXTURE_HPP
#define VIRTUAL_GALAXY_TEXTURE_HPP

#include "base.hpp"
#include "utils/color.hpp"

#include "SDL.h"

class Texture {
public:
    struct Stream {
        explicit Stream(Texture& texture);
        void clear(Color color);
        void setPixel(int32 x, int32 y, Color color);
        void setPixel(int32 i, Color color);
        ~Stream();

    private:
        Texture& _texture;
        SDL_Surface* _surface;
        uint32* _pixels;
    };

    explicit Texture(SDL_Texture* texture, int32 width, int32 height);
    Stream lock();
    ~Texture();

private:
    SDL_Texture* _texture;
    int32 _width;
    int32 _height;

    /*
     * Only the renderer should be able to construct the texture class
     * and access internal buffer
     */
    friend class Renderer;
};

#endif //VIRTUAL_GALAXY_TEXTURE_HPP
