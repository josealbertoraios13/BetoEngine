//
// Created by jose_alberto on 02/10/2025.
//

#include "../../include/Engine/Core/Window.h"

#include <GL/glew.h>

#include "imgui_impl_opengl3.h"
#include "imgui_impl_sdl2.h"

namespace BetoEngine {
    int Window::width = 800;
    int Window::height = 600;

    Window::~Window() {
        Destroy();
    }

    bool Window::Create(const std::string &title) {

        // Initialize SDL
        if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER) != 0) {
            SDL_Log("SDL_Init Error: %s", SDL_GetError());
            return false;
        }

        // Configurações de contexto OpenGL
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

        // Configuração da janela
        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
        SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
        SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

        //Cria a janela
        m_window = SDL_CreateWindow
        (title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);

        if (m_window == nullptr) {
            SDL_Log("SDL_CreateWindow Error: %s", SDL_GetError());
            return false;
        }

        // Cria contexto OpenGL
        m_GLcontext = SDL_GL_CreateContext(m_window);
        SDL_GL_MakeCurrent(m_window, m_GLcontext);
        SDL_GL_SetSwapInterval(1); // Ativa V-Sync

        // Initialize Glew (ou outro carregador de funções OpenGL)
        glewExperimental = GL_TRUE;

        GLenum glewInitResult = glewInit();

        if (glewInitResult != GLEW_OK) {
            SDL_Log("Falha ao inicializar GLEW: %s", glewGetErrorString(glewInitResult));
            return false;
        }

        // Mensagem de sucesso
        SDL_Log("Aplicação inicializada com sucesso!!");
        SDL_Log("OpenGL %s, GLSL %s", glGetString(GL_VERSION), glGetString(GL_SHADING_LANGUAGE_VERSION));

        return true;
    }

    void Window::SetWindowSize(int _width, int _height) {
        width = _width;
        height = _height;
    }


    void Window::Destroy() const{
        // Limpa SDL
        if (m_GLcontext)
            SDL_GL_DeleteContext(m_GLcontext);
        if (m_window)
            SDL_DestroyWindow(m_window);
        SDL_Quit();
    }

    void Window::BeginFrame() {
        // Limpa o buffer de cor e profundidade
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f); //Cor de fundo
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void Window::EndFrame() const{
        //Troca os buffers (Double buffering)
        SDL_GL_SwapWindow(m_window);
    }

    SDL_Window *Window::GetSDLWindow() const {
        return m_window;
    }

    SDL_GLContext Window::GetContext() const {
        return m_GLcontext;
    }
}

