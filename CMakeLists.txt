cmake_minimum_required(VERSION 3.10)
project(BetoEngine)

set(CMAKE_CXX_STANDARD 14)

# Encontra as bibliotecas
find_package(OpenGL REQUIRED)
find_package(PkgConfig REQUIRED)
pkg_check_modules(SDL2 REQUIRED sdl2)
find_package(GLEW REQUIRED)

# Caminho do ImGui
set(IMGUI_DIR ${CMAKE_SOURCE_DIR}/external/imgui)

# Arquivos do ImGui
set(IMGUI_SRC
        ${IMGUI_DIR}/imgui.cpp
        ${IMGUI_DIR}/imgui_draw.cpp
        ${IMGUI_DIR}/imgui_tables.cpp
        ${IMGUI_DIR}/imgui_widgets.cpp
        ${IMGUI_DIR}/backends/imgui_impl_sdl2.cpp
        ${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp
)

# Fontes da engine
set(ENGINE_SRC
        src/Engine/Engine.cpp
        src/Engine/Core/Window.cpp
        src/Engine/Core/Logger.cpp
        src/Engine/UI/ImGuiManager.cpp
        src/Engine/Graphics/Mesh.cpp
        src/Engine/Graphics/MeshManager.cpp
        src/Engine/Math/Transform.cpp
        src/Engine/Graphics/PrimitiveObjects/Triangle.cpp
        src/Engine/Graphics/PrimitiveObjects/Rectangle.cpp
        src/Engine/Graphics/PrimitiveObjects/Ellipse.cpp
        examples/basic_triangle/TriangleExample.cpp
)

# Cria executável
add_executable(BetoEngine
        src/main.cpp
        ${ENGINE_SRC}
        ${IMGUI_SRC}
)

# Inclui diretórios
target_include_directories(BetoEngine PRIVATE
        ${IMGUI_DIR}
        ${IMGUI_DIR}/backends
        ${SDL2_INCLUDE_DIRS}
        ${GLEW_INCLUDE_DIRS}
        ${OPENGL_INCLUDE_DIR}
        include
)

# Linka bibliotecas
target_link_libraries(BetoEngine
        ${SDL2_LIBRARIES}
        ${GLEW_LIBRARIES}
        ${OPENGL_LIBRARIES}
)

# Define o loader do ImGui para GLEW
add_definitions(-DIMGUI_IMPL_OPENGL_LOADER_GLEW)
