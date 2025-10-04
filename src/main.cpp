#include "../examples/basic_triangle/TriangleExample.h"

int main(int argc, char* argv[]) {
    /*startup for your program
     *Example:
     *Engine engine;
     *engine.GetWindow().SetWindowSize(1280, 720);
     *engine.Run();*/

    TriangleExample example;
    BetoEngine::Window::SetWindowSize(1280, 720);
    example.Run();

}
