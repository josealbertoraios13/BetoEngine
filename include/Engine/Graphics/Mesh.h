//
// Created by jose_alberto on 02/10/2025.
//

#ifndef BETOENGINE_MESH_H
#define BETOENGINE_MESH_H

#pragma once

#include <GL/glew.h>
#include <string>
#include <memory>
#include <vector>

#include "../Math/Transform.h"

class Mesh {
    public:
        // Construtores / Destrutores
        Mesh();
        explicit Mesh(const std::vector<float>& verts);
        virtual ~Mesh();

        // Métodos principais
        void Initialize();
        void Draw();

        // Encapsulamento
        void SetColor(const glm::vec4& _color);

        void SetName(const std::string& _name);
        std::string GetName() const;

        // Hierarquia
        void AddChild(const std::shared_ptr<Mesh>& _child);
        void RemoveChild(const std::shared_ptr<Mesh>& _child);

        Transform transform;
        std::shared_ptr<Mesh> parent;
        std::vector<std::shared_ptr<Mesh>> children;

    protected:
        virtual void Render() const;
        void DefineProjection() const;

        void SetupMesh();
        void SetupShader();

        std::vector<float> m_verts;
        std::string m_name;
        glm::vec4 m_color;

    private:
        GLuint VAO, VBO;
        GLuint shaderProgram;

        static glm::mat4 LocalMatrix(const Transform& t);

        void UpdateWorldMatrix();

        static void CheckCompileErrors(GLuint shader, const std::string& type);
};

#endif //BETOENGINE_MESH_H