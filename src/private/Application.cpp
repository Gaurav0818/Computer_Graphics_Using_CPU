#include "Application.h"
#include <stdexcept>

void Application::init() 
{
    m_window = std::make_unique<Window>();
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
    m_mesh = std::make_unique<Mesh>();

    m_mesh->loadObjFileDate("assets/f22.obj");
}

void Application::update()
{
    m_window->targetFrameTime(FRAME_TRAGET_TIME);
    dottedLines(0xFF555555);

    m_cubeRotation.x += 0.01;
    m_cubeRotation.y += 0.00;
    m_cubeRotation.z += 0.00;

    m_trisToDraw.clear();
    for (int i = 0; i < m_mesh->faces.size(); i++)
    {
        vec3_i meshFace = m_mesh->faces[i];

        Triangle<vec3_f> faceVertices = {
           m_mesh->vertices[meshFace.x - 1],
           m_mesh->vertices[meshFace.y - 1],
           m_mesh->vertices[meshFace.z - 1]
        };


        // Loop all three vertices of this current face and apply transformations
        for (int j = 0; j < 3; j++)
        {
            faceVertices.points[j].RotateInX(m_cubeRotation.x);
            faceVertices.points[j].RotateInY(m_cubeRotation.y);
            faceVertices.points[j].RotateInZ(m_cubeRotation.z);

            // Translate the vertex away from the camera
            faceVertices.points[j].z -= m_cameraPos.z;

        }

        if (isfacingCamera(faceVertices))
        {
            Triangle<vec2_f> projectedTriangle;
            for (int j = 0; j < 3; j++)
            {
                vec2 projectedPoint = std::move(project(faceVertices.points[j]));

                // apply transformations;
                projectedPoint.x += m_window->getWinWidth() / 2;
                projectedPoint.y += m_window->getWinHeight() / 2;


                projectedTriangle.points[j] = projectedPoint;
            }


            m_trisToDraw.emplace_back(std::move(projectedTriangle));
        }
    }
}

void Application::render()
{
    for (auto& triangle : m_trisToDraw)
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

bool Application::isfacingCamera(const Triangle<vec3_f>& face)
{
    vec3_f ray = m_cameraPos - face.points[0];
    vec3_f ab = face.points[1] - face.points[0];
    vec3_f ac = face.points[2] - face.points[0];
    vec3_f normal = cross(ab, ac);

    return (dot(normal,ray) <= 0) ? false : true;
}

// recives a 3d vector and returns a projected 2d point
vec2_f Application::project(const vec3_f& point)
{
    // Ortho Projection
    //return vec2_f(point.x, point.y) * m_fovFactor;

    return vec2_f(point.x, point.y) * m_fovFactor / point.z;
}

void Application::dottedLines(uint32_t clr)
{
    for (int y = 0; y < m_window->getWinHeight(); y++)
        for (int x = 0; x < m_window->getWinWidth(); x++)
            if (x % 10 == 0 && y % 10 == 0) 
                m_window->drawPixel(x, y, clr);

}

