#include <graphics/color.hpp>
#include <stdexcept>
#include "graphics/texture.hpp"

#include "SDL.h"

Texture::Stream::Stream(Texture& texture) : _texture(texture), _surface(nullptr), _pixels(nullptr) {
    if (SDL_LockTextureToSurface(texture._texture, nullptr, &_surface)) {
        throw std::runtime_error(SDL_GetError());
    }
    _pixels = static_cast<uint32*>(_surface->pixels);
}

void Texture::Stream::setPixel(int32 x, int32 y, Color color) {
    _pixels[x + y * _texture._width] = static_cast<uint32>(color);
}

void Texture::Stream::setPixel(int32 i, Color color) {
    _pixels[i] = static_cast<uint32>(color);
}

void Texture::Stream::clear(Color color) {
    SDL_FillRect(_surface, nullptr, static_cast<uint32>(color));
}

Texture::Stream::~Stream() {
    _surface = nullptr;
    _pixels = nullptr;
    SDL_UnlockTexture(_texture._texture);
}

Texture::Texture(SDL_Texture* texture, int32 width, int32 height) :
        _texture(texture), _width(width), _height(height) {}

Texture::Stream Texture::lock() {
    return Texture::Stream(*this);
}

Texture::~Texture() {
    SDL_DestroyTexture(_texture);
}
