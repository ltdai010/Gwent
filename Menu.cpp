#include "pch.h"
#include "Menu.h"


Menu::Menu()
{
	window = SDL_CreateWindow("Gwent", 100, 50, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_ALLOW_HIGHDPI);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	mainEvent = new SDL_Event();
	menu = IMG_LoadTexture(renderer, "img/Menu.png");
	choosed = false;
	if (menu == NULL)
	{
		std::cout << "error load menu" << std::endl;
	}
	else
	{
		std::cout << "success load menu" << std::endl;
	}
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		std::cout << "sound error" << std::endl;
	}
	music = Mix_LoadMUS("audio/CalmBeforeStorm.mp3");
	Mix_PlayMusic(music, -1);
	rect.x = 0;
	rect.y = 0;
	rect.w = SCREEN_WIDTH;
	rect.h = SCREEN_HEIGHT;
}


Menu::~Menu()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
}

void Menu::checkMouse()
{
	if (mainEvent->type == SDL_MOUSEBUTTONDOWN)
	{
		if (mainEvent->button.button == SDL_BUTTON_LEFT)
		{
			SDL_GetMouseState(&mouseX, &mouseY);
			if (hoverLeft())
			{
				GameField* gameField = new GameField(window, renderer, mainEvent, NILFGAARDIAN, NORTHERN);
				gameField->gameLoop();
				choosed = true;
			}
			if (hoverRight())
			{
				GameField* gameField = new GameField(window, renderer, mainEvent, NORTHERN, NILFGAARDIAN);
				gameField->gameLoop();
				choosed = true;
			}
		}
	}
}

bool Menu::hoverLeft()
{
	if (mouseX > 200 && mouseX < 600 && mouseY > 0 && mouseY < 1000)
	{
		return true;
	}
	return false;
}

bool Menu::hoverRight()
{
	if (mouseX > 1000 && mouseY < 1400 && mouseY > 0 && mouseY < 1000)
	{
		return true;
	}
	return false;
}

void Menu::draw()
{
	Uint32 time = SDL_GetTicks();
	while (mainEvent->type != SDL_QUIT && !choosed)
	{
		if (time + WAIT_TIME < SDL_GetTicks())
		{
			SDL_PollEvent(mainEvent);
			SDL_RenderClear(renderer);
			checkMouse();
			SDL_RenderCopy(renderer, menu, NULL, &rect);
			SDL_RenderPresent(renderer);
		}
	}
}


