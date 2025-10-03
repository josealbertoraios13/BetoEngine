#ifndef BETOENGINE_ENGINE_H
#define BETOENGINE_ENGINE_H

#pragma once
#include "Engine/Core/Window.h"
#include "Engine/Graphics/MeshManager.h"
#include "Engine/UI/ImGuiManager.h"

class Engine {
    public:
        Engine();
        virtual ~Engine();

        int Run();

        virtual void Start(){};
        virtual void Update(float deltaTime){};

        BetoEngine::Window& GetWindow();
        ImGuiManager& GetImGuiManager();
        MeshManager& GetMeshManager();

    private:
    ////Estados da aplicação
        void Shutdown() const;

        void ProcessEvents();

        static void BeginFrame();
        void EndFrame() const;

        BetoEngine::Window m_Window;
        ImGuiManager m_ImGuiManager;
        MeshManager m_MeshManager;

        bool m_Running = true;
        float m_Time = 0.0f;
        float m_DeltaTime = 0.0f;

};

#endif
