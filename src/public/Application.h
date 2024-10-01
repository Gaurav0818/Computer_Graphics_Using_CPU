#ifndef APPLICATION_H
#define APPLICATION_H

#include <memory>

#include "Window.h"
#include "vector.h"
#include "Mesh.h"

#define FPS 60
#define FRAME_TRAGET_TIME (1000 / FPS)

class Application {
public:
    Application() = default;
    ~Application() = default;

    void init();
    void run();

private:
    std::unique_ptr<Window> m_window = std::make_unique<Window>();

    std::vector<Triangle> m_trisToDraw;

    void setup();
    void update();
    void render();

    vec3 m_cameraPos = { 0, 0, -5 };
    vec3 m_cubeRotation = { 0 };
    float m_fovFactor = 640;
    
    std::unique_ptr<Mesh> m_cubeMesh;

    vec2 project(vec3 point);


    void dottedLines(uint32_t clr);
};

#endif // !APPLICATION_H
