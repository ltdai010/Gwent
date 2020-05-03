#pragma once
class Enemy
{
public:
	Enemy();
	~Enemy();
	void setDeck(Deck* deck);
	Deck* getDeck();
	bool inTurn();
	void setTurn(bool turn);
	void drawCard(SDL_Renderer* renderer, Side* enemy);
private:
	Deck* deck;
	int score;
	bool turn;
};

