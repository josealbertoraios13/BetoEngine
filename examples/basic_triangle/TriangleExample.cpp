//
// Created by jose_alberto on 03/10/2025.
//

#include "TriangleExample.h"

#include "Engine/Graphics/PrimitiveObjects/Triangle.h"

std::shared_ptr<Mesh> triangleMesh;

void TriangleExample::Start() {
    triangleMesh = std::make_shared<Triangle>();

    triangleMesh->transform.scale = glm::vec3(0.5f, 0.5f, 0.5f);
    triangleMesh->SetName("My first triangle");

}

void TriangleExample::Update(float deltaTime) {
    triangleMesh->Draw();
}
