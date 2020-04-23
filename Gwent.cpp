#include "pch.h"


int main(int argc, char *argv[])
{
	SDL_Init(SDL_INIT_EVERYTHING);
	GameField* gameField = new GameField();
	gameField->gameLoop();
	return 0;
}
