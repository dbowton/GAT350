#pragma once
#include "SDL.h"
#include <memory>
#include "Types.h"

class Renderer
{
public:
	~Renderer();

	bool Initialize(int width, int height, bool fullscreen = false);
	void CopyBuffer(class Framebuffer* buffer);
    void Present();

public:
	SDL_Window* window;
	SDL_Renderer* renderer;
    int width = 0;
    int height = 0;
};
