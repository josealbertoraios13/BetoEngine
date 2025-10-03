//
// Created by jose_alberto on 02/10/2025.
//

#ifndef BETOENGINE_IMGUIMANAGER_H
#define BETOENGINE_IMGUIMANAGER_H

#pragma once
#include <vector>

#include "../Graphics/Mesh.h"
#include "Engine/Core/Window.h"

class ImGuiManager {
    public:
    //Para o editor
        static void HierarchyMenu(const std::vector<Mesh*> &objects, bool enable = true);
        static void InspectorMenu(Mesh &obj, bool enable = true);
        static void DebugMenu(bool enable = true);

        void Init(const BetoEngine::Window &window);
        static void Shutdown();

        static void BeginFrame();
        static void EndFrame();

        ImGuiIO* GetIO() const;
    private:
        ImGuiIO* m_imGuiIo = nullptr;


};

#endif //BETOENGINE_IMGUIMANAGER_H