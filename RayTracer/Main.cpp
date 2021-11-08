#include "Renderer.h"
#include "Framebuffer.h"
#include "Image.h"
#include "PostProcess.h"
#include "Tracer.h"
#include "Scene.h"
#include "Camera.h"

#include <iostream>
#include <SDL.h>

int main(int, char**)
{
	const int WIDTH = 800;
	const int HEIGHT = 600;

	std::unique_ptr<Renderer> renderer = std::make_unique<Renderer>();
	renderer->Initialize(WIDTH, HEIGHT);
	
	std::unique_ptr<Framebuffer> framebuffer = std::make_unique<Framebuffer>(renderer.get(), renderer->width, renderer->height);

	std::unique_ptr<Tracer> tracer = std::make_unique<Tracer>();

	// samplers
	std::shared_ptr<TextureSampler> texture1 = std::make_unique<TextureSampler>(std::make_unique<Image>("../resources/earth.bmp"));
	std::shared_ptr<TextureSampler> texture2 = std::make_unique<TextureSampler>(std::make_unique<Image>("../resources/metal.bmp"));
	std::shared_ptr<CheckerSampler> black_checker = std::make_unique<CheckerSampler>(glm::vec3{ 0, 0, 0 }, glm::vec3{ 1, 1, 1 });
	std::shared_ptr<CheckerSampler> red_checker = std::make_unique<CheckerSampler>(glm::vec3{ 0, 0, 0 }, glm::vec3{ 1, 0, 0 });

	// scene
	std::unique_ptr<Scene> scene = std::make_unique<Scene>();
	scene->Add(std::move(std::make_unique<Sphere>(glm::vec3{ 0, 4, -7 }, 2.5f, std::make_shared<Lambertian>(texture2))));
	scene->Add(std::move(std::make_unique<Sphere>(glm::vec3{ 4, 1, -8 }, 3.2f, std::make_shared<Lambertian>(glm::vec3{ 0.4f, 0.25f, 0.6f }))));
	scene->Add(std::move(std::make_unique<Sphere>(glm::vec3{ -3, 2, -8 }, 1.0f, std::make_shared<Metal>(texture1, 0.15f))));
	scene->Add(std::move(std::make_unique<Sphere>(glm::vec3{ 2, -1, -4 }, 1.5f, std::make_shared<Dielectric>(glm::vec3{ 0.6f, 0.8f, 0.25f }, 2.0f))));
	scene->Add(std::move(std::make_unique<Plane>(glm::vec3{ 0, -2, 0 }, glm::vec3{ 0, 1, 0 }, std::make_shared<Lambertian>(black_checker))));

	//light
	scene->Add(std::move(std::make_unique<Sphere>(glm::vec3{ 0, 25, 0 }, 10.0f, std::make_shared<Emissive>(glm::vec3{ 10, 10, 10 }))));

	// camera
	glm::vec3 eye = glm::vec3{ 5, 1, 2 };
	glm::vec3 lookAt = glm::vec3{ 0, 2, -10 };
	float focalLength = glm::length(eye - lookAt);
	std::unique_ptr<Camera> camera = std::make_unique<Camera>(eye, lookAt, glm::vec3{ 0, 1, 0 }, 90.0f, glm::ivec2{ framebuffer->colorBuffer.width, framebuffer->colorBuffer.height }, 0.2f, focalLength);

	framebuffer->Clear({ 0, 0, 0, 0 });
	tracer->Trace(framebuffer->colorBuffer, scene.get(), camera.get());
	framebuffer->Update();

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

		renderer->CopyBuffer(framebuffer.get());
		renderer->Present();
	}

	SDL_Quit();

	return 0;
}
