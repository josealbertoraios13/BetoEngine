//
// Created by jose_alberto on 02/10/2025.
//

#include "../../include/Engine/UI/ImGuiManager.h"

#include <functional>
#include <vector>

#include "imgui.h"
#include "imgui_impl_opengl3.h"
#include "imgui_impl_sdl2.h"
#include "../../../include/Engine/Core/Logger.h"
#include "../../include/Engine/Graphics/Mesh.h"


void ImGuiManager::Init(const BetoEngine::Window &window) {
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    m_imGuiIo = &ImGui::GetIO();
    m_imGuiIo->ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable keyboard controls

    // Setup Plataform/Renderer backends
    ImGui_ImplSDL2_InitForOpenGL(window.GetSDLWindow(), window.GetContext());
    ImGui_ImplOpenGL3_Init("#version 330");

    // Configura estilo do ImGui (opcional)
    ImGui::StyleColorsDark();
}

ImGuiIO* ImGuiManager::GetIO() const {
    return m_imGuiIo;
}

void ImGuiManager::HierarchyMenu(const std::vector<Mesh*> &objects, bool enable) {
    ImGui::SetNextWindowSize(ImVec2(300, 600));
    ImGui::Begin("Hierarchy", nullptr, ImGuiWindowFlags_NoResize);

    if (ImGui::TreeNode("Cena")) {
        static Mesh* selected = nullptr;

        // Função recursiva para mostrar objetos e filhos
        std::function<void(Mesh*)> ShowNode;
        ShowNode = [&](Mesh* obj) {
            ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_OpenOnArrow;

            // Se não tiver filhos, marca como folha
            if (obj->children.empty()) {
                flags |= ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen;
            }

            if (selected == obj) {
                flags |= ImGuiTreeNodeFlags_Selected;
            }

            bool nodeOpen = ImGui::TreeNodeEx(obj->GetName().c_str(), flags);

            // Seleção do item
            if (ImGui::IsItemClicked()) {
                selected = (selected == obj) ? nullptr : obj;
            }

            // Se tiver filhos e o nó estiver aberto, chama recursivamente
            if (!obj->children.empty() && nodeOpen) {
                for (auto& child : obj->children) {
                    ShowNode(child.get());
                }
                ImGui::TreePop();
            }
        };

        // Exibe todos os objetos da cena
        for (auto* obj : objects) {
            ShowNode(obj);
        }

        // Inspector para o objeto selecionado
        if (selected) {
            InspectorMenu(*selected);
        }

        ImGui::TreePop();
    }

    ImGui::End();
}


void ImGuiManager::InspectorMenu(Mesh &obj, bool enable) {
    ImGui::SetNextWindowSize(ImVec2(300, 600));
    ImGui::Begin("Inspector", nullptr, ImGuiWindowFlags_NoResize);
    ImGui::Text("To %s", obj.GetName().c_str());
    ImGui::LabelText("", "Transform: ");
    ImGui::LabelText("Position:", "");
    ImGui::LabelText("", "X: ");
    ImGui::SameLine();
    ImGui::InputFloat("##X:", &obj.transform.localPosition.x);
    ImGui::SliderFloat("##x", &obj.transform.localPosition.x, -5.0f, 5.0f);
    ImGui::LabelText("", "Y: ");
    ImGui::SameLine();
    ImGui::InputFloat("##Y:", &obj.transform.localPosition.y);
    ImGui::SliderFloat("##y", &obj.transform.localPosition.y, -5.0f, 5.0f);
    ImGui::LabelText("", "Z: ");
    ImGui::SameLine();
    ImGui::InputFloat("##Z:", &obj.transform.localPosition.z);
    ImGui::SliderFloat("##z", &obj.transform.localPosition.z, -2000.0f, 2000.0f);

    ImGui::LabelText("Rotation:", "");
    ImGui::LabelText("", "rX: ");
    ImGui::SameLine();
    ImGui::InputFloat("##rX:", &obj.transform.localRotation.x);
    ImGui::LabelText("", "rY: ");
    ImGui::SameLine();
    ImGui::InputFloat("##rY:", &obj.transform.localRotation.y);
    ImGui::LabelText("", "rZ: ");
    ImGui::SameLine();
    ImGui::InputFloat("##rZ:", &obj.transform.localRotation.z);
    ImGui::SliderFloat("##rz", &obj.transform.localRotation.z, -360.0f, 360.0f);

    ImGui::LabelText("Scales:", "");
    ImGui::LabelText("", "Width: ");
    ImGui::SameLine();
    ImGui::InputFloat("##Width:", &obj.transform.localScale.x);
    ImGui::SliderFloat("##Width", &obj.transform.localScale.x, -10.0f, 10.0f);
    ImGui::LabelText("", "Height: ");
    ImGui::SameLine();
    ImGui::InputFloat("##Height:", &obj.transform.localScale.y);
    ImGui::SliderFloat("##Height", &obj.transform.localScale.y, -10.0f, 10.0f);
    ImGui::LabelText("", "Forward: ");
    ImGui::SameLine();
    ImGui::InputFloat("##Forward:", &obj.transform.localScale.z);

    ImGui::End();
}

void ImGuiManager::DebugMenu(bool enable) {
    if (enable == false) {
        return;
    }

    ImGui::SetNextWindowSize(ImVec2(300, 140));
    ImGui::Begin("Debug", nullptr, ImGuiWindowFlags_NoResize);
    ImGuiIO& io = ImGui::GetIO();
    ImGui::Text("FPS: %.1f", io.Framerate);

    ImGui::BeginChild("Messages", ImVec2(0, 0), true, ImGuiWindowFlags_AlwaysVerticalScrollbar);

    for (auto &ms: Logger::logs) {
        ImGui::Text("%s", ms.c_str());
    }

    ImGui::EndChild();

    ImGui::End();
}

void ImGuiManager::Shutdown() {
    //Limpa ImGui
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();
}

void ImGuiManager::BeginFrame() {
    // Inicia um novo frame de ImGui
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();
}

void ImGuiManager::EndFrame() {
    // Renderiza ImGui
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

