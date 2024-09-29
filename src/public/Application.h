#ifndef APPLICATION_H
#define APPLICATION_H

#include <memory>

#include "Window.h"
#include "vector.h"

#define NUM_POINTS 9*9*9

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
    std::vector<vec3> cubePoints;
    std::vector<vec2> projectedPoints;

    void setup();
    void update();

    vec3 m_cameraPos = { 0, 0, -3 };
    vec3 m_cubeRotation = { 0 };
    float m_fovFactor = 640;

    vec2 project(vec3 point);

    void dottedLines(uint32_t clr);
    void drawRect(int x1, int y1, int width, int height, uint32_t clr);
    void drawRectPoints(int x1, int y1, int x2, int y2, uint32_t clr);
};

#endif // !APPLICATION_H
