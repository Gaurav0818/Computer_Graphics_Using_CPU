#ifndef APPLICATION_H
#define APPLICATION_H

#include <memory>

#include "Window.h"
#include "vector.h"

#define NO_POINTS 9*9*9

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
    float m_fovFactor = 600;


    vec2 project(vec3 point);

    void dottedLines(uint32_t clr);
    void drawRect(int x1, int y1, int width, int height, uint32_t clr);
    void drawRectPoints(int x1, int y1, int x2, int y2, uint32_t clr);
};

#endif // !APPLICATION_H
