#version 330 core

layout(location = 0) in vec3 aPos; // Atributo de vétice (posição)

uniform mat4 model; // Matriz de transformação
uniform mat4 projection;

void main() {
    gl_Position = projection * model * vec4(aPos, 1.0);
}
