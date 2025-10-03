//
// Created by jose_alberto on 02/10/2025.
//

#include "../../include/Engine.h"

#include <SDL_log.h>
#include <SDL_timer.h>

#include "imgui_impl_sdl2.h"

Engine::Engine() = default;

Engine::~Engine() {
    Shutdown();
}

int Engine::Run() {

    // Inicialização
    if (!m_Window.Create("BetoEngine")) {
        SDL_Log("Failed to initialize");
        return -1;
    }

    m_ImGuiManager.Init(m_Window);

    // Chama o Start Uma vez para o setup Inicial do usuário
    Start();

    // Loop principal
    Uint64 now = SDL_GetPerformanceCounter();

    while (m_Running) {
        Uint64 last = 0;
        // Calcula o deltaTime em segundos
        m_DeltaTime = static_cast<float>(static_cast<double>(now - last) * 1000 / static_cast<double>(SDL_GetPerformanceFrequency()));

        //Fase de Processamento
        ProcessEvents(); // Processa Input SDL_Event

        //Fase de Renderização
        BeginFrame(); //Limpa o buffer, inicia frame ImGui

        //Para o editor (ImGui)
        ImGuiManager::HierarchyMenu(MeshManager::m_meshes);
        ImGuiManager::DebugMenu();

        //Fase de Atualização
        // Chama o Update() definido pelo usuário,passando o deltaTime
        Update(m_DeltaTime);

        EndFrame();// Renderiza ImGui, swap buffers
    }

    // Limpeza
    Shutdown();
    return 0;
}

BetoEngine::Window &Engine::GetWindow() {
    return m_Window;
}

ImGuiManager &Engine::GetImGuiManager() {
    return m_ImGuiManager;
}

MeshManager &Engine::GetMeshManager() {
    return m_MeshManager;
}


// privates

void Engine::Shutdown() const{
    // Limpa ImGui
    ImGuiManager::Shutdown();

    // Limpa SDL
    m_Window.Destroy();
}

void Engine::ProcessEvents() {
    SDL_Event event;

    while (SDL_PollEvent(&event)) {
        //Processa eventos para o ImGui
        ImGui_ImplSDL2_ProcessEvent(&event);

        // Processa eventos para a aplicação
        switch (event.type) {
            case SDL_QUIT:
                m_Running = false;
                break;
            case SDL_WINDOWEVENT:
                if (event.window.event == SDL_WINDOWEVENT_CLOSE && event.window.windowID == SDL_GetWindowID(m_Window.GetSDLWindow())) {
                    m_Running = false;
                }
                break;
            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_ESCAPE){
                    m_Running = false;
                }
                break;
            default:
                break;
        }
    }
}

void Engine::BeginFrame() {
    // Limpa o buffer de cor e profundidade
    BetoEngine::Window::BeginFrame();

    // Inicia um novo frame do ImGui
    ImGuiManager::BeginFrame();
}

void Engine::EndFrame() const{
    // Renderiza o ImGui
    ImGuiManager::EndFrame();

    m_Window.EndFrame();
}




