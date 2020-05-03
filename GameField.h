#pragma once
class GameField
{
public:
	GameField(SDL_Window* window, SDL_Renderer* renderer, SDL_Event* event, Empire player, Empire enemy);
	~GameField();
	void gameLoop();
	void mouseCheck();
	bool hoverCard(Card* card, int mouseX, int mouseY);
	bool hoverDeck(int mouseX, int mouseY);
	void enemyTurn();
	bool over();
	void checkResult();
private:
	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Event* mainEvent;
	SDL_Texture* endScene;
	SDL_Texture* endText;
	TTF_Font* font;
	SDL_Color color;
	Board* board;
	Mix_Music* music;
	bool clicked;
	int mouseX;
	int mouseY;
	SDL_Rect rect;
	SDL_Rect text_rect;
	bool gameOver;
	SDL_Surface* endText_s;
};

