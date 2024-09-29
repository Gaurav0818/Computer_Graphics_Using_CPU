#include "Application.h"
#include <stdexcept>

void Application::init() 
{
    m_window->init();
}

void Application::run() 
{
    m_window->setup();
    setup();

    while (m_window->isRunning)
    {
        m_window->processInput();
        update();
        m_window->render();
    }
}


void Application::setup()
{
    cubePoints.resize(NO_POINTS);
    projectedPoints.resize(NO_POINTS);

    int pointCount = 0;

    for(float x = -1; x <=1; x += 0.25)
        for (float y = -1; y <= 1; y += 0.25)
            for (float z = -1; z <= 1; z += 0.25)
            {
                cubePoints[pointCount] = vec3(x, y, z);
                pointCount++;
            }


}

void Application::update()
{
    dottedLines(0xFF555555);

    for (int i = 0; i < NO_POINTS; i++)
    {


        projectedPoints[i] = project(cubePoints[i] - m_cameraPos);
        
        drawRect(
            projectedPoints[i].x, projectedPoints[i].y,
            5, 5,
            0xFFFFFFFF
        );
    }
}

// recives a 3d vector and returns a projected 2d point
vec2 Application::project(vec3 point)
{
    // Ortho Projection
    //return vec2(point.x * m_fovFactor + m_window->getWinWidth()/2, point.y * m_fovFactor + m_window->getWinHeight() / 2);

    // Prespective Projection
    return vec2((point.x * m_fovFactor / point.z) + m_window->getWinWidth() / 2, (point.y * m_fovFactor / point.z) + m_window->getWinHeight() / 2);
}

void Application::dottedLines(uint32_t clr)
{
    for (int y = 0; y < m_window->getWinHeight(); y++) {
        for (int x = 0; x < m_window->getWinWidth(); x++) {
            if (x % 10 == 0 && y % 10 == 0) {
                m_window->drawPixel(x, y, clr);
            }
        }
    }
}

void Application::drawRectPoints(int x1, int y1, int x2, int y2, uint32_t clr)
{
    if (x2 < x1) std::swap(x1, x2);
    if (y2 < y1) std::swap(y1, y2);

    for (int y = y1; y < y2; y++) {
        for (int x = x1; x < x2; x++) {
            m_window->drawPixel(x, y, clr);
        }
    }
}

void Application::drawRect(int x1, int y1, int width, int height, uint32_t clr)
{
    drawRectPoints(x1, y1, x1 + width, y1 + height, clr);
}



