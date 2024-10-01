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
        break;
    case SDL_KEYDOWN:
        if (event.key.keysym.sym == SDLK_ESCAPE) {
            isRunning = false;
        }
        break;
    }
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
    drawRectPoints(x1, y1, x1 + width, y1 + height, clr);
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
