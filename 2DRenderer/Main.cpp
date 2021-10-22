#include "Renderer.h"
#include "Framebuffer.h"
#include "Image.h"
#include "PostProcess.h"

#include <iostream>
#include <SDL.h>

int main(int, char**)
{
	const int WIDTH = 800;
	const int HEIGHT = 600;

	std::unique_ptr<Renderer> renderer = std::make_unique<Renderer>();
	renderer->Initialize(WIDTH, HEIGHT);
	
	std::unique_ptr<Framebuffer> framebuffer = std::make_unique<Framebuffer>(renderer.get(), renderer->width, renderer->height);

    std::unique_ptr<Image> image = std::make_unique<Image>();
    image->Load("../Resources/flower.bmp", 128);
    image->Flip();

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

        framebuffer->DrawImage(300, 50, image.get());

        std::unique_ptr<Image> image1 = std::make_unique<Image>(*image.get());
        PostProcess::BoxBlur(image1->colorBuffer);
        framebuffer->DrawImage(0, 300, image1.get());
       
        std::unique_ptr<Image> image2 = std::make_unique<Image>(*image.get());
        PostProcess::GausianBlur(image2->colorBuffer);
        framebuffer->DrawImage(200, 300, image2.get());
        
        std::unique_ptr<Image> image3 = std::make_unique<Image>(*image.get());
        PostProcess::Sharpen(image3->colorBuffer);
        framebuffer->DrawImage(400, 300, image3.get());

        std::unique_ptr<Image> image4 = std::make_unique<Image>(*image.get());
        PostProcess::Monochrome(image4->colorBuffer);
        PostProcess::Edge(image4->colorBuffer, 0);
        framebuffer->DrawImage(600, 300, image4.get());


        for (int i = 0; i < 20; i++)
        {
            framebuffer->DrawRect(rand() % renderer->width, rand() % renderer->height, 50, 50, { (uint8_t)((rand() % 2) * 255), (uint8_t)((rand() % 2) * 255), (uint8_t)((rand() % 2) * 255), (uint8_t)(rand() % 256) });
        }

        if(false)
        {
            for (int i = 0; i < 100; i++)
            {
                framebuffer->DrawPoint(rand() % renderer->width, rand() % renderer->height, { 0, 255, 0, 0 });
            }
            for (int i = 0; i < 20; i++)
            {
                framebuffer->DrawRect(rand() % renderer->width, rand() % renderer->height, 20, 20, { 0, 0, 255, 0 });
            }
            for (int i = 0; i < 20; i++)
            {
                framebuffer->DrawLine(renderer->width >> 1, renderer->height >> 1, rand() % renderer->width, rand() % renderer->height, { 255, 255, 255, 0 });
            }

            framebuffer->DrawCircle(renderer->width >> 1, renderer->height >> 1, 150, { 255, 255, 0, 0 });
            framebuffer->DrawTriangle(150, 150, 200, 200, 200, 400, { 0, 255, 0, 0 });

            for (int i = 0; i < 10; i++)
            {
                framebuffer->DrawQuadraticBezier(
                    rand() % renderer->width, rand() % renderer->height,
                    rand() % renderer->width, rand() % renderer->height,
                    rand() % renderer->width, rand() % renderer->height, 30, { 255, 255, 0, 255 });
            }
            for (int i = 0; i < 10; i++)
            {
                framebuffer->DrawCubicBezier(
                    rand() % renderer->width, rand() % renderer->height,
                    rand() % renderer->width, rand() % renderer->height,
                    rand() % renderer->width, rand() % renderer->height,
                    rand() % renderer->width, rand() % renderer->height,
                    30, { 0, 255, 255, 255 });
            }
        }

//       PostProcess::Invert(framebuffer->colorBuffer);
//        PostProcess::Monochrome(framebuffer->colorBuffer);
  //      PostProcess::ColorBalance(framebuffer->colorBuffer, 0, 0, 100);
  //      PostProcess::Brightness(framebuffer->colorBuffer, -100);
 //       PostProcess::Noise(framebuffer->colorBuffer, 100);
 //       PostProcess::Threshold(framebuffer->colorBuffer, 200);

		framebuffer->Update();
		renderer->CopyBuffer(framebuffer.get());
		renderer->Present();
	}

	SDL_Quit();

	return 0;
}
