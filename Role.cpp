#include "pch.h"
#include "Role.h"


Role::Role(Lane lane)
{
	this->lane = lane;
}


Role::~Role()
{
	for (size_t i = 0; i < cards.size(); i++)
	{
		delete cards.at(i);
	}
}

void Role::drawCard(SDL_Renderer* renderer)
{
	for (int i = 0; i < cards.size(); ++i)
	{
		cards.at(i)->draw(renderer);
	}
}

void Role::addCard(Card* card)
{
	card->setLocation(UNIT_POSITION_X, MELEE_POSITION_Y);
	card->setSize(ON_BOARD_CARD_WIDTH, ON_BOARD_CARD_HEIGHT);
	cards.push_back(card);
}

Lane Role::getLane()
{
	return this->lane;
}

