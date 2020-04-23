#pragma once
class GameField
{
public:
	GameField();
	~GameField();
	void gameLoop();
	void mouseCheck();
	bool hoverCard(Card* card, int mouseX, int mouseY);
	bool hoverDeck(int mouseX, int mouseY);
	Lane hoverLane(int mouseX, int mouseY);
private:
	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Event* mainEvent;
	Board* board;
	Mix_Music* music;
	int mouseX;
	int mouseY;
};

