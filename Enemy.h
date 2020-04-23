#pragma once
class Enemy
{
public:
	Enemy();
	~Enemy();
	void setDeck(Deck* deck);
	Deck* getDeck();
private:
	Deck* deck;
	int score;
};

