//
// Created by jose_alberto on 03/10/2025.
//
#include "../../../../include/Engine/Graphics/PrimitiveObjects/Ellipse.h"
#include "../../../../include/Engine.h"
#include <cmath>

Ellipse::Ellipse() {
    // --- Cria vértices unitários ---
    m_verts.clear();
    m_verts.push_back(0.0f); // centro x
    m_verts.push_back(0.0f); // centro y
    m_verts.push_back(0.0f); // centro z

    int segments = 180;
    float angleStep = 2.0f * M_PI / segments;

    for (int i = 0; i <= segments; i++) {
        float angle = i * angleStep;
        float x = 0.5f * cos(angle);
        float y = 0.5f * sin(angle);

        m_verts.push_back(x);
        m_verts.push_back(y);
        m_verts.push_back(0.0f);
    }

    SetName("newEllipse");

    // --- Agora inicializa o VAO/VBO ---
    Initialize();
}

void Ellipse::Render() const{
    // Renderiza os triângulos (3 componentes por vétice, dividido por 3 para número de  vétices)
    glDrawArrays(GL_TRIANGLE_FAN, 0, static_cast<GLsizei>(m_verts.size() / 3));
    glBindVertexArray(0);//Desvincula o VAO
}