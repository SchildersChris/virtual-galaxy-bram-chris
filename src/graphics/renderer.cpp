#include "graphics/renderer.hpp"
#include "graphics/color.hpp"

#include <imgui.h>
#include <imgui_sdl.h>
#include <stdexcept>
#include <memory>

Renderer Renderer::_instance;
Renderer& Renderer::getInstance() {
    return _instance;
}

void Renderer::init(const std::string& title, bool fullscreen, int32 width, int32 height) {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        throw std::runtime_error(SDL_GetError());
    }

    if (!(_window = SDL_CreateWindow(
            title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
            width, height, static_cast<SDL_WindowFlags>(fullscreen) | SDL_WINDOW_VULKAN | SDL_WINDOW_SHOWN))) {
        throw std::runtime_error(SDL_GetError());
    }

    if (!(_renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED))) {
        throw std::runtime_error(SDL_GetError());
    }

    _width = width;
    _height = height;

    ImGui::CreateContext();
    ImGuiSDL::Initialize(_renderer, _width, _height);
}

int32 Renderer::getWidth() const {
    return _width;
}

int32 Renderer::getHeight() const {
    return _height;
}

void Renderer::setClearColor(Color color) {
    _clearColor = color;
}

void Renderer::beginFrame(float deltaTime) {
    SDL_SetRenderDrawColor(_renderer, _clearColor.R, _clearColor.G, _clearColor.B, _clearColor.A);
    SDL_RenderClear(_renderer);

    ImGuiIO& io = ImGui::GetIO();

    int32 mouseX, mouseY;
    uint32 buttons = SDL_GetMouseState(&mouseX, &mouseY);

    io.DeltaTime = deltaTime;
    io.MousePos = ImVec2(static_cast<float>(mouseX), static_cast<float>(mouseY));
    io.MouseDown[0] = buttons & SDL_BUTTON(SDL_BUTTON_LEFT);
    io.MouseDown[1] = buttons & SDL_BUTTON(SDL_BUTTON_RIGHT);

    ImGui::NewFrame();
}

void Renderer::drawTexture(const Texture& texture) {
    SDL_RenderCopy(_renderer, texture._texture, nullptr, nullptr);
}

void Renderer::drawLine(const Vector2& p1, const Vector2& p2, Color color) {
    SDL_SetRenderDrawColor(_renderer, color.R, color.G, color.B, color.A);
    SDL_RenderDrawLineF(_renderer, p1.X, p1.Y, p2.X, p2.Y);
}

void Renderer::endFrame() {
    ImGui::Render();
    ImGuiSDL::Render(ImGui::GetDrawData());

    SDL_RenderPresent(_renderer);
}

void Renderer::terminate() {
    ImGuiSDL::Deinitialize();
    ImGui::DestroyContext();

    SDL_DestroyRenderer(_renderer);
    SDL_DestroyWindow(_window);

    SDL_QuitSubSystem(SDL_INIT_EVERYTHING);
    SDL_Quit();

    _renderer = nullptr;
    _window = nullptr;
}

std::unique_ptr<Texture> Renderer::createTexture(int32 width, int32 height) {
    SDL_Texture* texture;
    if (!(texture = SDL_CreateTexture(
            _renderer,
            SDL_PIXELFORMAT_RGBA8888,
            SDL_TEXTUREACCESS_STREAMING,
            _width, _height))) {
        throw std::runtime_error(SDL_GetError());
    }

    return std::make_unique<Texture>(texture, width, height);
}
