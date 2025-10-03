//
// Created by jose_alberto on 02/10/2025.
//

#ifndef BETOENGINE_WINDOW_H
#define BETOENGINE_WINDOW_H

#pragma once

#include <SDL.h>
#include <string>

#include "imgui.h"

namespace BetoEngine {
    class Window {
    public:
        static int width;
        static int height;

        Window() = default;
        ~Window();

        bool Create(const std::string &title);
        void Destroy() const;

        static void SetWindowSize(int width, int height);
        static void BeginFrame();
        void EndFrame() const;

        SDL_Window* GetSDLWindow() const;
        SDL_GLContext GetContext() const;

    private:
        SDL_Window* m_window = nullptr;
        SDL_GLContext m_GLcontext = nullptr;
    };
}
#endif //BETOENGINE_WINDOW_H