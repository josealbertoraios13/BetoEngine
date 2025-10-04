# Projeto iniciado por José Alberto Martins Gomes da Silva, durante seu curso de ciência da computação.

Estou desenvolvendo esse projeto com o intuito de aprofundar meus conhecimentos sobre c++, computação gráfica, transformações lineares, e algoritmos para estruturas de dados e simulações simples(Exemplo: Inverse Kinematics - IK).

## Tecnologias usadas

1. C++ - Linguagem de programação.
2. Integrated Development Environment (IDE), Clion - JetBrains.
3. OpenGL.
4. OpenGL Mathematics (GLM).
5. OpenGL Extension Wrangler Library (GLEW)
6. OpenGL Shading Language (GLSL)
7. ImGui (interface UI) - https://github.com/ocornut/imgui.
8. Simple Directmedia Layer 2 (SDL2).

### Exemplo: Triangulo

#### TriangleExample.h
```c++
class TriangleExample : public Engine {
    public:
        TriangleExample() = default;
        ~TriangleExample() override = default;

        void Start() override;
        void Update(float deltaTime) override;
};
```

#### TriangleExample.cpp
```c++
std::shared_ptr<Mesh> triangleMesh;

void TriangleExample::Start() {
    triangleMesh = std::make_shared<Triangle>();

    triangleMesh->transform.scale = glm::vec3(0.5f, 0.5f, 0.5f);
    triangleMesh->SetName("My first triangle");

}

void TriangleExample::Update(float deltaTime) {
    triangleMesh->Draw();
}
```

#### main.cpp
```c++
int main(int argc, char* argv[]) {
    TriangleExample example;
    BetoEngine::Window::SetWindowSize(1280, 720);
    example.Run();
}
```

     