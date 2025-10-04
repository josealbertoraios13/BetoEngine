#version 330 core

out vec4 FragColor; // Cor de saída
uniform vec4 uColor;
void main() {
    gl_FragColor = uColor;
}
