#ifndef APPLICATION_H
#define APPLICATION_H

#include <memory>
#include <algorithm>

#include "Window.h"
#include "vector.h"
#include "Mesh.h"

#define FPS 128
#define FRAME_TRAGET_TIME (1000 / FPS)

class Application {
public:
    Application() = default;
    ~Application() = default;

    void init();
    void run();

private:
    std::unique_ptr<Window> m_window;
    std::unique_ptr<Mesh> m_mesh;

    std::vector<Triangle<vec2_f>> m_trisToDraw;

    void setup();
    void update();
    void render();

    vec3_f m_cameraPos = { 0, 0, -5 };
    vec3_f m_cubeRotation = { 0 };
    float m_fovFactor = 640;

    bool isfacingCamera(const Triangle<vec3_f>& face);
    vec2_f project(const vec3_f& point);

    void dottedLines(uint32_t clr);
};

#endif // !APPLICATION_H
