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
        render();                   // write to color buffer.. from app side.

        m_window->render();         // let window perform requied thinngs 
                                    //-> convert color buffer to image 
                                    //-> set image as renderTraget 
                                    //-> swap buffers
                                    //-> clear color buffer
    }
}


void Application::setup()
{
    m_cubeMesh = std::make_unique<Mesh>();
}

void Application::update()
{
    m_window->targetFrameTime(FRAME_TRAGET_TIME);
    dottedLines(0xFF555555);

    m_cubeRotation.x += 0.01;
    m_cubeRotation.y += 0.01;
    m_cubeRotation.z += 0.01;

    m_trisToDraw.clear();
    for (int i = 0; i < N_MESH_FACES; i++)
    {
        face3 meshFace = m_cubeMesh->meshFaces[i];

        vec3 faceVertices[3] = {
            m_cubeMesh->meshVertices[meshFace.x - 1],
            m_cubeMesh->meshVertices[meshFace.y - 1],
            m_cubeMesh->meshVertices[meshFace.z - 1]
        };

        Triangle projectedTriangle;

        // Loop all three vertices of this current face and apply transformations
        for (int j = 0; j < 3; j++)
        {
            faceVertices[j].RotateInX(m_cubeRotation.x);
            faceVertices[j].RotateInY(m_cubeRotation.y);
            faceVertices[j].RotateInZ(m_cubeRotation.z);

            // Translate the vertex away from the camera

            faceVertices[j].z -= m_cameraPos.z;

            vec2 projectedPoint = std::move(project(faceVertices[j]));

            // apply transformations;
            projectedPoint.x += m_window->getWinWidth() / 2;
            projectedPoint.y += m_window->getWinHeight() / 2;
            

            projectedTriangle.points[j] = projectedPoint;
        }

        m_trisToDraw.emplace_back(std::move(projectedTriangle));
    }
}

void Application::render()
{
    for (Triangle& triangle : m_trisToDraw)
    {
        m_window->drawLine(
            triangle.points[0].x, triangle.points[0].y,
            triangle.points[1].x, triangle.points[1].y,
            0xFFFFFF00
        );
        m_window->drawLine(
            triangle.points[2].x, triangle.points[2].y,
            triangle.points[1].x, triangle.points[1].y,
            0xFFFFFF00
        );
        m_window->drawLine(
            triangle.points[2].x, triangle.points[2].y,
            triangle.points[0].x, triangle.points[0].y,
            0xFFFFFF00
        );
    }
}

// recives a 3d vector and returns a projected 2d point
vec2 Application::project(vec3 point)
{
    // Ortho Projection
    //return vec2(point.x * m_fovFactor + m_window->getWinWidth()/2, point.y * m_fovFactor + m_window->getWinHeight() / 2);

    // Prespective Projection
    return vec2(point.x, point.y) * m_fovFactor / point.z;
}

void Application::dottedLines(uint32_t clr)
{
    for (int y = 0; y < m_window->getWinHeight(); y++)
        for (int x = 0; x < m_window->getWinWidth(); x++)
            if (x % 10 == 0 && y % 10 == 0) 
                m_window->drawPixel(x, y, clr);

}

