#include "Framebuffer.h"

Framebuffer::Framebuffer(Renderer* renderer, int width, int height)
{
    this->width = width;
    this->height = height;

    texture = SDL_CreateTexture(renderer->renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, width, height);
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
        buffer[i * sizeof(color_t)] = color.r;
        buffer[i * sizeof(color_t) + 1] = color.g;
        buffer[i * sizeof(color_t) + 2] = color.b;
        buffer[i * sizeof(color_t) + 3] = color.a;

    }

}

void Framebuffer::DrawPoint(int x, int y, const color_t& color)
{
    int index = x * sizeof(color_t) + y * pitch;

    buffer[index] = color.r;
    buffer[index + 1] = color.g;
    buffer[index + 2] = color.b;
    buffer[index + 3] = color.a;

}

void Framebuffer::DrawRect(int x, int y, int rect_width, int rect_height, const color_t& color)
{
    //if (x < 0 || x >= width || y < 0 || y >= height) return;

    for (int sy = y; sy < y + rect_height; sy++)
    {
        for (int sx = x; sx < x + rect_width; sx++)
        {
            if (sx >= 0 && sx < width && sy >= 0 && sy < height) DrawPoint(sx, sy, color);
        }
    }

}

void Framebuffer::DrawLine(int x1, int y1, int x2, int y2, const color_t& color)
{

}

void Framebuffer::DrawCircle(int x, int y, int radius, const color_t& color)
{
}
