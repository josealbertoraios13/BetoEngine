//
// Created by jose_alberto on 02/10/2025.
//

#include "../../include/Engine/Graphics/Mesh.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/matrix_decompose.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <algorithm>

#include "../../../include/Engine/Graphics/MeshManager.h"
#include "../../../include/Engine/Core/Window.h"


Mesh::Mesh() :  m_color(1, 1, 1, 1), VAO(0), VBO(0), shaderProgram(0){
    SetName("newMesh");
    SetupMesh(); // Configura buffers OpenGl
    SetupShader(); // Compila e linka shaders
};

Mesh::Mesh(const std::vector<float> &verts) : m_verts(verts),  m_color(1, 1, 1, 1), VAO(0), VBO(0), shaderProgram(0){
    SetName("newMesh");
    SetupMesh(); // Configura buffers OpenGl
    SetupShader(); // Compila e linka shaders
}

Mesh::~Mesh() {
    if (VBO) glDeleteBuffers(1, &VBO);
    if (VAO) glDeleteVertexArrays(1, &VAO);
    if (shaderProgram) glDeleteProgram(shaderProgram);
}

void Mesh::Initialize() {
    SetupMesh();
    SetupShader();
}

void Mesh::Draw() {
    //Ativa o programa de shader
    glUseProgram(shaderProgram);

    DefineProjection();

    GLint modelLoc = glGetUniformLocation(shaderProgram, "model");
    GLint colorLoc = glGetUniformLocation(shaderProgram, "uColor");
    glUniform4fv(colorLoc, 1, &m_color[0]);

    transform.localMatrix = LocalMatrix(transform);

    UpdateWorldMatrix();
    if (parent == nullptr) {
        auto it = std::find(MeshManager::m_meshes.begin(), MeshManager::m_meshes.end(), this);

        if ((it == MeshManager::m_meshes.end())) {
            MeshManager::m_meshes.push_back(const_cast<Mesh*>(this));
        }
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(transform.localMatrix));
    }else {
        transform.worldMatrix = parent->transform.worldMatrix * transform.localMatrix;
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(transform.worldMatrix));
    }

    glBindVertexArray(VAO);//Vincula o VAO do mesh
    Render();
    glBindVertexArray(0);//Desvincula o VAO

    // Desenha filhos
    for (const auto& child : children) {
            child->Draw();
    }
}

void Mesh::SetColor(const glm::vec4 &_color) {
    this->m_color = _color;
}

void Mesh::SetName(const std::string &_name) {
    this->m_name = _name;
}
std::string Mesh::GetName() const{
    return this->m_name;
}

void Mesh::AddChild(const std::shared_ptr<Mesh> &child) {
    child->parent = std::shared_ptr<Mesh>(this);
    children.push_back(child);
}

void Mesh::RemoveChild(const std::shared_ptr<Mesh> &child) {
    children.erase(
        std::remove(children.begin(), children.end(), child),
        children.end()
    );
}

//Protected
void Mesh::Render() const{
    // Renderiza os triângulos (3 componentes por vétice, dividido por 3 para número de  vétices)
    glDrawArrays(GL_TRIANGLES, 0, static_cast<GLsizei>(m_verts.size() / 3));
}

void Mesh::DefineProjection() const{
    float aspect = static_cast<float>(BetoEngine::Window::width) / static_cast<float>(BetoEngine::Window::height);
    glm::mat4 projection = glm::ortho(-aspect, aspect, -1.0f, 1.0f, -1.0f, 1.0f);

    GLint projLoc = glGetUniformLocation(shaderProgram, "projection");
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
}

void Mesh::SetupMesh() {

    //Gera VAO e VBO
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO); // Vincula VAO
    glBindBuffer(GL_ARRAY_BUFFER, VBO);// Vincula VBO

    //Envia dados dos vétices para GPU
    glBufferData(GL_ARRAY_BUFFER, static_cast<GLsizeiptr>(m_verts.size() * sizeof(float)), m_verts.data(), GL_STATIC_DRAW);

    //Define layout dos atibrutos de vétices
    //Atributo 0: 3 componentes (x, y, z) do tipo float, sem normalização
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0); //Habilita o atributo 0

    // Limpa bindings (boas práticas)
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}


void Mesh::SetupShader() {
    const char* vertexShaderSource = R"(
                #version 330 core
                layout(location = 0) in vec3 aPos; // Atributo de vértice (posição)
                uniform mat4 model; // matriz de tranformação
                uniform mat4 projection;
                void main(){
                    gl_Position = projection * model * vec4(aPos, 1.0);
                }
            )";

    //Shader fragment: define cor fixa branca
    const char* fragmentShaderSource = R"(
                #version 330 core
                out vec4 FragColor; // Cor de saída
                uniform vec4 uColor;
                void main(){
                    FragColor = uColor; //Branco opaco
                }
            )";

    //Compila vertex shader
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
    glCompileShader(vertexShader);
    CheckCompileErrors(vertexShader, "VERTEX"); //Verifica Erros

    // Compila fragment shader
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
    glCompileShader(fragmentShader);
    CheckCompileErrors(fragmentShader, "FRAGMENT"); // Veridica erros

    // Cria programa de shader e linka os shaders
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    CheckCompileErrors(shaderProgram, "PROGRAM"); // Verifica erros de linking

    // Limpa shaders intermédiarios (já linkados no programa)
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

//Private
glm::mat4 Mesh::LocalMatrix(const Transform &t) {
    glm::mat4 model = glm::mat4(1.0f);

    //Translação
    model = translate(model, t.localPosition);

    //Rotação XYZ (Euler Angles)
    model = rotate(model, glm::radians(t.localRotation.z), glm::vec3(0, 0, 1)); //Z

    //Escala
    model = glm::scale(model, t.localScale);

    return model;
}

void Mesh::UpdateWorldMatrix() {
    //Calcular matriz local
    transform.localMatrix = LocalMatrix(transform);

    if (parent) {
        transform.worldMatrix = parent->transform.worldMatrix * transform.localMatrix;
    }else {
        transform.worldMatrix = transform.localMatrix;
    }

    // Atualiza os valores globais position/rotation/scale a partir da worldMatrix
    // Para simplificar, usamos decomposição (GLM)
    glm::vec3 skew;
    glm::vec4 perspective;
    glm::quat rotationQuat;

    glm::decompose(transform.worldMatrix, transform.scale, rotationQuat, transform.position, skew, perspective);
    transform.rotation = glm::degrees(glm::eulerAngles(rotationQuat));

}

void Mesh::CheckCompileErrors(GLuint shader, const std::string& type ) {
    GLint success;
    char infoLog[512]; // Buffer para mensagens de erro

    if (type != "PROGRAM") {
        // Verifica a compilação do shader
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(shader, 512, nullptr, infoLog);
        }

        return;
    }

    // Verifica linking do programa
    glGetProgramiv(shader, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shader, 512, nullptr, infoLog);
    }
}