#include "pch.h"


int main(int argc, char *argv[])
{
	SDL_Init(SDL_INIT_EVERYTHING);
	TTF_Init();
	Menu* menu = new Menu();
	menu->draw();
	delete menu;
	return 0;
}


