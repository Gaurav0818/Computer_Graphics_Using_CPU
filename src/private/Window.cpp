#include "Window.h"
#include <iostream>

void Window::init() 
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) 
    {
        throw std::runtime_error("Error initializing SDL.");
    }

    SDL_DisplayMode display;
    SDL_GetCurrentDisplayMode(0, &display);

    m_windowWidth = display.w - (display.w >> 2);
    m_windowHeight = display.h - (display.h >> 2);

    m_window.reset(SDL_CreateWindow(
        "Computer Graphics",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        m_windowWidth, m_windowHeight,
        0
    ));

    if (!m_window) 
    {
        throw std::runtime_error("Error creating SDL window.");
    }

    m_renderer.reset(SDL_CreateRenderer(m_window.get(), -1, 0));

    if (!m_renderer) 
    {
        throw std::runtime_error("Error creating SDL renderer.");
    }
}

void Window::setup() 
{
    m_colorBuffer.resize(m_windowWidth * m_windowHeight);

    m_colorBufferTexture.reset( SDL_CreateTexture(
        m_renderer.get(),
        SDL_PIXELFORMAT_ARGB8888,
        SDL_TEXTUREACCESS_STREAMING,
        m_windowWidth,
        m_windowHeight
    ));
}

void Window::processInput() 
{
    SDL_Event event;
    SDL_PollEvent(&event);

    switch (event.type) {
    case SDL_QUIT:
            isRunning = false;
    }

    if (isKeyPressed(Key::ESCAPE))
        isRunning = false;
}

void Window::render() 
{
    SDL_RenderClear(m_renderer.get());

    renderColorBuffer();
    SDL_RenderPresent(m_renderer.get());
    
    clearColorBuffer();
}

int Window::getWinWidth()
{
    return m_windowWidth;
}

int Window::getWinHeight()
{
    return m_windowHeight;
}

void Window::targetFrameTime(int target)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(target));
}

void Window::setClearClr(uint32_t clr)
{
    m_clearClr = clr;
}

void Window::drawPixel(int x, int y, uint32_t clr)
{
    if(x>=0 && x < m_windowWidth && y >=0 && y < m_windowHeight)
        m_colorBuffer[m_windowWidth * y + x] = clr;
}

bool Window::isKeyDown(int keyCode)
{
    return m_keyInput->isButtonDown(keyCode);
}

bool Window::isKeyPressed(int keyCode)
{
    return m_keyInput->isButtonPressed(keyCode);
}

void Window::getMousePos(int& x, int& y)
{
    SDL_GetMouseState(&x, &y);
}

bool Window::isEnabled(ERenderType type)
{
    return ( ( (m_activeRenderTypes >> type) & 1) == 1 );
}

void Window::enableRenderType(ERenderType type)
{
    m_activeRenderTypes = m_activeRenderTypes | (1 << type);
}

void Window::disableRenderType(ERenderType type)
{
    m_activeRenderTypes = m_activeRenderTypes & (0xFFFFFFFF ^ (1 << type));
}

void Window::drawLine(int x0, int y0, int x1, int y1, uint32_t clr)
{
    int dx = x1 - x0;
    int dy = y1 - y0;

    float sideLength = abs(dx) >= abs(dy) ? abs(dx) : abs(dy);

    float xInc = dx / sideLength;
    float yInc = dy / sideLength;


    float currentX = x0;
    float currentY = y0;

    for (int i = 0; i <= sideLength; i++)
    {
        drawPixel(currentX, currentY, clr);
        currentX += xInc;
        currentY += yInc;
    }
}

void Window::drawTriangle(int x0, int y0, int x1, int y1, int x2, int y2, uint32_t clr)
{

    if (y0 > y1)
    {
        swap(y0, y1);
        swap(x0, x1);
    }
    
    if (y1 > y2)
    {
        swap(y2, y1);
        swap(x2, x1);
    }
    
    if (y0 > y1)
    {
        swap(y0, y1);
        swap(x0, x1);
    }
    
    if (y1 == y2)
    {
        // pure Bottom flat triangle
        fillFlatBottomTriangle(x0, y0, x1, y1, x2, y2, clr);
    }
    else if (y0 == y1)
    {
        // pure Top flat triangle
        fillFlatTopTriangle(x0, y0, x1, y1, x2, y2, clr);
    }
    else
    {
        int my = y1;
        int mx = ((float)(x2 - x0) * (y1 - y0) / (float)(y2 - y0)) + x0;
    
        fillFlatBottomTriangle(x0, y0, x1, y1, mx, my, clr);
        fillFlatTopTriangle(x1, y1, mx, my, x2, y2, clr);
    }

}

void Window::drawRectPoints(int x1, int y1, int x2, int y2, uint32_t clr)
{
    if (x2 < x1) std::swap(x1, x2);
    if (y2 < y1) std::swap(y1, y2);

    for (int y = y1; y < y2; y++)
        for (int x = x1; x < x2; x++)
            drawPixel(x, y, clr);

}

void Window::drawRect(int x1, int y1, int width, int height, uint32_t clr)
{
    drawRectPoints(x1 - width / 2, y1 - width / 2, x1 + width / 2, y1 + height / 2, clr);
}

template <typename T>
void Window::swap(T& a, T& b)
{
    a ^= b;
    b ^= a;
    a ^= b;
}

void Window::fillFlatBottomTriangle(int x0, int y0, int x1, int y1, int x2, int y2, uint32_t clr)
{
    float invSlope1 = (float)(x1 - x0)/ (y1 - y0);
    float invSlope2 = (float)(x2 - x0)/ (y2 - y0);

    // Start xStart and xEnd from the top vertex(x0, y0);
    float xStart = x0;
    float xEnd = x0;

    // Loop all the scanlines from top to bottom
    for (int y = y0; y <= y2; y++)
    {
        drawLine(xStart, y, xEnd, y, clr);
        xStart += invSlope1;
        xEnd += invSlope2;
    }
}

void Window::fillFlatTopTriangle(int x0, int y0, int x1, int y1, int x2, int y2, uint32_t clr)
{
    float invSlope1 = (float)(x2 - x0) / (y2 - y0);
    float invSlope2 = (float)(x2 - x1) / (y2 - y1);

    // Start xStart and xEnd from the bottom vertex(x2, y2);
    float xStart = x2;
    float xEnd = x2;

    // Loop all the scanlines from bottom to top
    for(int y = y2; y >=y0; y--)
    {
        drawLine(xStart, y, xEnd, y, clr);
        xStart -= invSlope1;
        xEnd -= invSlope2;
    }
}

void Window::renderColorBuffer()
{
    SDL_UpdateTexture(m_colorBufferTexture.get(), NULL, m_colorBuffer.data(), sizeof(uint32_t) * m_windowWidth);
    SDL_RenderCopy(m_renderer.get(), m_colorBufferTexture.get(), NULL, NULL);
}

void Window::clearColorBuffer() 
{
    std::fill(m_colorBuffer.begin(), m_colorBuffer.end(), m_clearClr);
}
