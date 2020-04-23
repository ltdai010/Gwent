#include "pch.h"
#include "Enemy.h"


Enemy::Enemy()
{
	score = 0;
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