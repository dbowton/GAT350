#include <iostream>
#include <SDL.h>

int main(int, char**)
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		std::cout << "SDL_INIT Error: " << SDL_GetError() << std::endl;
		return 1;
	}


	SDL_Window* window = SDL_CreateWindow("Gat350", 100, 100, 800, 600, SDL_WINDOW_SHOWN);
	if (window == nullptr)
	{
		std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
		return 1;
	}

	std::getchar();

	SDL_Quit();

	return 0;
}
