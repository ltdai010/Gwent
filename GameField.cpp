#include "pch.h"
#include "GameField.h"


GameField::GameField()
{
	window = SDL_CreateWindow("Gwent", 100, 50, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_ALLOW_HIGHDPI);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	mainEvent = new SDL_Event();
	board = new Board(renderer);
	mouseX = 0;
	mouseY = 0;
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		std::cout << "sound error" << std::endl;
	}
	music = Mix_LoadMUS("audio/Whispers.mp3");
	//Mix_PlayMusic(music, -1);
}


GameField::~GameField()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	Mix_Quit();
	IMG_Quit();
	SDL_Quit();
	delete mainEvent;
}

void GameField::mouseCheck()
{
	SDL_GetMouseState(&mouseX, &mouseY);
	if (mainEvent->type == SDL_MOUSEBUTTONDOWN)
	{
		if (mainEvent->button.button == SDL_BUTTON_LEFT)
		{
			for (int i = 1; i < board->getPlayer()->getDeck()->getBunch().size(); ++i)
			{
				if (board->getPlayer()->getDeck()->getBunch().at(i) != NULL && hoverCard(board->getPlayer()->getDeck()->getBunch().at(i), mouseX, mouseY))
				{
					std::cout << "Mouse left clicked" << std::endl;
					board->getPlayer()->getDeck()->unHoldAll();
					board->getPlayer()->getDeck()->getBunch().at(i)->setHolded(true);
					board->getPlayer()->setHolded(true);
					board->getRole(MELEE)->addCard(
					board->getPlayer()->getDeck()->getBunch().at(i));
				}
				else if(!hoverDeck(mouseX, mouseY))
				{
					board->getPlayer()->getDeck()->unHoldAll();
				}
			}	
		}
	}
}


void GameField::gameLoop()
{
	Uint32 time = SDL_GetTicks();
	while (mainEvent->type != SDL_QUIT )
	{
		if (time + WAIT_TIME < SDL_GetTicks())
		{
			SDL_PollEvent(mainEvent);
			SDL_RenderClear(renderer);

			mouseCheck();
			board->draw(renderer);

			SDL_RenderPresent(renderer);	
		}
	}
}

bool GameField::hoverCard(Card* card, int mouseX, int mouseY)
{
	if (mouseX > card->getLocationX() &&
		mouseX < card->getLocationX() +
		IN_DECK_CARD_WIDTH &&
		mouseY > card->getLocationY() &&
		mouseY < card->getLocationY() +
		IN_DECK_CARD_HEIGHT)
	{
		return true;
	}
	return false;
}

bool GameField::hoverDeck(int mouseX, int mouseY)
{
	if (mouseX > 175 && mouseX < SCREEN_WIDTH - 175
		&& mouseY > SCREEN_HEIGHT - 190 && mouseY < SCREEN_HEIGHT)
	{
		return true;
	}
	return false;
}


