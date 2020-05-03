#include "pch.h"
#include "Player.h"


Player::Player(std::string name)
{
	this->name = name;
	this->score = 0;
	holded = false;
	turn = false;
}


Player::~Player()
{
	delete deck;
}

Deck* Player::getDeck()
{
	return deck;
}

bool Player::getHolded()
{
	return holded;
}

void Player::setHolded(bool holded)
{
	this->holded = holded;
}

void Player::setDeck(Deck* deck)
{
	this->deck = deck;
}

void Player::drawCard(SDL_Renderer* renderer)
{
	deck->show(renderer);
}

void Player::arrangeCard()
{
	int start_point = 60;
	for (int i = 1; i < MAX_CARD_IN_DECK; ++i)
	{
		start_point = start_point + IN_DECK_CARD_WIDTH + 25;
		deck->getBunch().at(i)->setLocation(start_point, SCREEN_HEIGHT - IN_DECK_CARD_HEIGHT - 5);
		deck->getBunch().at(i)->setSize(IN_DECK_CARD_WIDTH, IN_DECK_CARD_HEIGHT);
	}
}

void Player::setTurn(bool turn)
{
	this->turn = turn;
}

bool Player::inTurn()
{
	return this->turn;
}
