#ifndef WINDOW_H
#define WINDOW_H

#include <SDL.h>
#include <cstdint>
#include <vector>
#include <memory>
#include <chrono>
#include <thread>

class Window {
public:
    Window() = default;
    ~Window() = default;

    void init();

    void setup();
    void processInput();
    void render();

    int getWinWidth();
    int getWinHeight();

    void targetFrameTime(int target);

    void setClearClr(uint32_t clr);
    void drawPixel(int x, int y, uint32_t clr);

    void drawLine(int x0, int y0, int x1, int y1, uint32_t clr);
    void drawRect(int x1, int y1, int width, int height, uint32_t clr);
    void drawRectPoints(int x1, int y1, int x2, int y2, uint32_t clr);

    bool isRunning = true;

private:
    std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)> m_window{ nullptr, SDL_DestroyWindow };
    std::unique_ptr<SDL_Renderer, decltype(&SDL_DestroyRenderer)> m_renderer{ nullptr, SDL_DestroyRenderer };
    std::unique_ptr<SDL_Texture, decltype(&SDL_DestroyTexture)> m_colorBufferTexture{ nullptr, SDL_DestroyTexture };
    std::vector<uint32_t> m_colorBuffer;

    int m_windowWidth = 0;
    int m_windowHeight = 0;
    uint32_t m_clearClr = 0;

    void renderColorBuffer();
    void clearColorBuffer();
};

#endif // !WINDOW_H
