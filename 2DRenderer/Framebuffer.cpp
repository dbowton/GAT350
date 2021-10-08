#include "Framebuffer.h"

Framebuffer::Framebuffer(Renderer* renderer, int width, int height)
{
    this->width = width;
    this->height = height;

    texture = SDL_CreateTexture(renderer->renderer, SDL_PIXELFORMAT_ABGR8888, SDL_TEXTUREACCESS_STREAMING, width, height);
    pitch = width * sizeof(color_t);
    buffer = new uint8_t[pitch * height];

}

Framebuffer::~Framebuffer()
{
    SDL_DestroyTexture(texture);
    delete[] buffer;
}

void Framebuffer::Update()
{
    SDL_UpdateTexture(texture, nullptr, buffer, pitch);

}

void Framebuffer::Clear(const color_t& color)
{


    for (int i = 0; i < width * height; i++)
    {
        ((color_t*)buffer)[i] = color;
    }

}

void Framebuffer::DrawPoint(int x, int y, const color_t& color)
{
    if(x < 0 || x >= width || y < 0 || y >= height) return;

    int i = x + y * width;

    ((color_t*)buffer)[i] = color;
}

void Framebuffer::DrawRect(int x, int y, int rect_width, int rect_height, const color_t& color)
{
    for (int sy = y; sy < y + rect_height; sy++)
    {
        for (int sx = x; sx < x + rect_width; sx++)
        {
            DrawPoint(sx, sy, color);
        }
    }
}

void Framebuffer::DrawLine(int x1, int y1, int x2, int y2, const color_t& color)
{
    int dx = x2 - x1;
    int dy = y2 - y1;

    if (dx == 0)
    {
        if (y1 > y2) std::swap(y1, y2);
        for (int y = y1; y <= y2; y++)
        {
            DrawPoint(x1, y, color);
        }
    }
    else
    {
        float m = dy / (float)dx;
        float b = y1 - (m * x1);


        if (std::abs(dx) > std::abs(dy))
        {
            if (x1 > x2) std::swap(x1, x2);
            for (int x = x1; x <= x2; x++)
            {
                int y = (int)round((m * x) + b);
                DrawPoint(x, y, color);
            }
        }
        else
        {
            if (y1 > y2) std::swap(y1, y2);
            for (int y = y1; y <= y2; y++)
            {
                int x = (int)round((y - b) / m);
                DrawPoint(x, y, color);
            }
        }
    }
}

void Framebuffer::DrawCircle(int x, int y, int radius, const color_t& color)
{
}
