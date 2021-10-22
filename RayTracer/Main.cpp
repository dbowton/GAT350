#include "Renderer.h"
#include "Framebuffer.h"
#include "Image.h"
#include "PostProcess.h"
#include "Tracer.h"

#include <iostream>
#include <SDL.h>

int main(int, char**)
{
	const int WIDTH = 800;
	const int HEIGHT = 600;

	std::unique_ptr<Renderer> renderer = std::make_unique<Renderer>();
	renderer->Initialize(WIDTH, HEIGHT);
	
	std::unique_ptr<Framebuffer> framebuffer = std::make_unique<Framebuffer>(renderer.get(), renderer->width, renderer->height);

	Tracer tracer;

	bool quit = false;
	SDL_Event event;
	while (!quit)
	{
		SDL_PollEvent(&event);
		switch (event.type)
		{
		case SDL_QUIT:
			quit = true;
			break;
		}

		framebuffer->Clear({ 0, 0, 0, 0 });

		tracer.Trace(framebuffer->colorBuffer);

		framebuffer->Update();
		renderer->CopyBuffer(framebuffer.get());
		renderer->Present();
	}

	SDL_Quit();

	return 0;
}
