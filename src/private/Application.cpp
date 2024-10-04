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
    m_window->targetFrameTime(FRAME_TRAGET_TIME);

    m_mesh = std::make_unique<Mesh>();

    m_mesh->loadObjFileDate("assets/cube.obj");

    m_window->setClearClr(0xFF000000);

    m_window->enableRenderType(ERenderType::eRenderFill);
    m_window->enableRenderType(ERenderType::eRenderWireframe);
    m_window->enableRenderType(ERenderType::eRenderVertex);
    m_window->enableRenderType(ERenderType::ePrespectiveProj);
    m_window->enableRenderType(ERenderType::eCullBackFace);
    //m_window->enbleRenderType(ERenderType::eCullFrontFace);
}

void Application::update()
{
    if (m_window->isKeyPressed(Key::NUM_1))
    {
        if(m_window->isEnabled(ERenderType::eRenderFill))
            m_window->disableRenderType(ERenderType::eRenderFill);
        else
            m_window->enableRenderType(ERenderType::eRenderFill);
    }
    if (m_window->isKeyPressed(Key::NUM_2))
    {
        if (m_window->isEnabled(ERenderType::eRenderWireframe))
            m_window->disableRenderType(ERenderType::eRenderWireframe);
        else
            m_window->enableRenderType(ERenderType::eRenderWireframe);
    }
    if (m_window->isKeyPressed(Key::NUM_3))
    {
        if (m_window->isEnabled(ERenderType::eRenderVertex))
            m_window->disableRenderType(ERenderType::eRenderVertex);
        else
            m_window->enableRenderType(ERenderType::eRenderVertex);
    }
    if (m_window->isKeyPressed(Key::NUM_4))
    {
        if (m_window->isEnabled(ERenderType::eCullBackFace))
            m_window->disableRenderType(ERenderType::eCullBackFace);
        else
            m_window->enableRenderType(ERenderType::eCullBackFace);
    }
    if (m_window->isKeyPressed(Key::NUM_5))
    {
        if (m_window->isEnabled(ERenderType::eCullFrontFace))
            m_window->disableRenderType(ERenderType::eCullFrontFace);
        else
            m_window->enableRenderType(ERenderType::eCullFrontFace);
    }
    if (m_window->isKeyPressed(Key::NUM_6))
    {
        if (m_window->isEnabled(ERenderType::ePrespectiveProj))
            m_window->disableRenderType(ERenderType::ePrespectiveProj);
        else
            m_window->enableRenderType(ERenderType::ePrespectiveProj);
    }

    dottedLines(0xFF555555);

    m_cubeRotation.x += 0.005;
    m_cubeRotation.y += 0.005;
    m_cubeRotation.z += 0.005;

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
            faceVertices.points[j] += m_cameraPos;
        }

        bool isFacing = isfacingCamera(faceVertices);

        if ((!isFacing && m_window->isEnabled(ERenderType::eCullFrontFace)) || 
            (isFacing && m_window->isEnabled(ERenderType::eCullBackFace)) || 
            (!m_window->isEnabled(ERenderType::eCullFrontFace) && !m_window->isEnabled(ERenderType::eCullBackFace) ))
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
    if (m_window->isEnabled(ERenderType::eRenderFill))
    {
        for (auto& triangle : m_trisToDraw)
        {
            m_window->drawTriangle(
                triangle.points[0].x, triangle.points[0].y,
                triangle.points[1].x, triangle.points[1].y,
                triangle.points[2].x, triangle.points[2].y,
                0xFFFFFFFF
            );
        }
    }

    if (m_window->isEnabled(ERenderType::eRenderWireframe))
    {
        for (auto& triangle : m_trisToDraw)
        {
            m_window->drawLine(
                triangle.points[0].x, triangle.points[0].y,
                triangle.points[1].x, triangle.points[1].y,
                m_window->m_wireFrameClr);
            m_window->drawLine(
                triangle.points[2].x, triangle.points[2].y,
                triangle.points[1].x, triangle.points[1].y,
                m_window->m_wireFrameClr);
            m_window->drawLine(
                triangle.points[0].x, triangle.points[0].y,
                triangle.points[2].x, triangle.points[2].y,
                m_window->m_wireFrameClr);
        }
    }

    if (m_window->isEnabled(ERenderType::eRenderVertex))
    {
        for (auto& triangle : m_trisToDraw)
        {
            m_window->drawRect(triangle.points[0].x, triangle.points[0].y, 8, 8, m_window->m_vertexClr);
            m_window->drawRect(triangle.points[1].x, triangle.points[1].y, 8, 8, m_window->m_vertexClr);
            m_window->drawRect(triangle.points[2].x, triangle.points[2].y, 8, 8, m_window->m_vertexClr);
        }
    }
}

bool Application::isfacingCamera(const Triangle<vec3_f>& face)
{
    vec3_f cameraRay = vec3_f(0) - face.points[0];
    vec3_f ab = face.points[1] - face.points[0];
    vec3_f ac = face.points[2] - face.points[0];
    vec3_f normal = cross(ab, ac);

    return (dot(normal, cameraRay) < 0) ? false : true;
}

// recives a 3d vector and returns a projected 2d point
vec2_f Application::project(const vec3_f& point)
{
    if (m_window->isEnabled(ERenderType::ePrespectiveProj))
        // Prespective Projection
        return vec2_f(point.x, point.y) * m_fovFactor / point.z;
    else
        // Ortho Projection
        return vec2_f(point.x, point.y) * (m_fovFactor/5);
}

void Application::dottedLines(uint32_t clr)
{
    for (int y = 0; y < m_window->getWinHeight(); y++)
        for (int x = 0; x < m_window->getWinWidth(); x++)
            if (x % 10 == 0 && y % 10 == 0) 
                m_window->drawPixel(x, y, clr);
}

