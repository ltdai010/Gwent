#include "pch.h"
#include "Enemy.h"


Enemy::Enemy()
{
	score = 0;
	turn = false;
}


Enemy::~Enemy()
{
	delete deck;
}

Deck* Enemy::getDeck()
{
	return this->deck;
}

void Enemy::setDeck(Deck* deck)
{
	this->deck = deck;
}

bool Enemy::inTurn()
{
	return this->turn;
}

void Enemy::setTurn(bool turn)
{
	this->turn = turn;
}

void Enemy::drawCard(SDL_Renderer* renderer, Side* enemy)
{
	for (int i = 0; i < enemy->getRole(MELEE)->getCards().size(); ++i)
	{
		enemy->getRole(MELEE)->getCards().at(i)->draw(renderer);
	}
	
}