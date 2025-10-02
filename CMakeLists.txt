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

# Cria executável incluindo main.cpp e ImGui
add_executable(BetoEngine
        src/main.cpp
        ${IMGUI_SRC}
)

# Inclui diretórios
target_include_directories(BetoEngine PRIVATE
        ${IMGUI_DIR}
        ${IMGUI_DIR}/backends
        ${SDL2_INCLUDE_DIRS}
        ${GLEW_INCLUDE_DIRS}
        ${OPENGL_INCLUDE_DIR}
)

# Linka bibliotecas
target_link_libraries(BetoEngine
        ${SDL2_LIBRARIES}
        ${GLEW_LIBRARIES}
        ${OPENGL_LIBRARIES}
)