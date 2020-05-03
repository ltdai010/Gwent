#pragma once
class Player
{
public:
	Player(std::string name);
	~Player();
	void drawCard(SDL_Renderer* renderer);
	Deck* getDeck();
	void setDeck(Deck* deck);
	void arrangeCard();
	void setHolded(bool holded);
	bool getHolded();
	bool inTurn();
	void setTurn(bool turn);
private:
	Deck* deck;
	int score;
	std::string name;
	bool holded;
	bool turn;
};

