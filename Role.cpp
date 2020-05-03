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

std::vector<Card*> Role::getCards()
{
	return cards;
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
	switch (lane)
	{
	case MELEE:
		if(faction == PLAYER)
			card->setLocation(UNIT_POSITION_X + cards.size()*(ON_BOARD_CARD_WIDTH + 20), MELEE_POSITION_Y);
		else
			card->setLocation(UNIT_POSITION_X + cards.size()*(ON_BOARD_CARD_WIDTH + 20), SIEGE_POSITION_Y - PLAYER_ENEMY_POSITION_Y_DIFF);
		break;
	case RANGE:
		if(faction == PLAYER)
			card->setLocation(UNIT_POSITION_X + cards.size()*(ON_BOARD_CARD_WIDTH + 20), RANGE_POSITION_Y);
		else
			card->setLocation(UNIT_POSITION_X + cards.size()*(ON_BOARD_CARD_WIDTH + 20), RANGE_POSITION_Y - PLAYER_ENEMY_POSITION_Y_DIFF);
		break;
	case SIEGE:
		if(faction == PLAYER)
			card->setLocation(UNIT_POSITION_X + cards.size()*(ON_BOARD_CARD_WIDTH + 20), SIEGE_POSITION_Y );
		else
			card->setLocation(UNIT_POSITION_X + cards.size()*(ON_BOARD_CARD_WIDTH + 20), MELEE_POSITION_Y - PLAYER_ENEMY_POSITION_Y_DIFF);
		break;
	case EFFECT:
		EffectCard* e_card = static_cast<EffectCard*>(card);
		switch (e_card->getEffect())
		{
		case MELEE_EF:
			e_card->setLocation(EFFECT_POSITION_X, EFFECT_POSITION_Y);
			break;
		case RANGE_EF:
			e_card->setLocation(EFFECT_POSITION_X + ON_BOARD_CARD_WIDTH, EFFECT_POSITION_Y);
			break;
		case SIEGE_EF:
			e_card->setLocation(EFFECT_POSITION_X + 2 * ON_BOARD_CARD_WIDTH, EFFECT_POSITION_Y);
			break;
		case CLEAR:
			e_card->setLocation(EFFECT_POSITION_X + 3 * ON_BOARD_CARD_WIDTH, EFFECT_POSITION_Y);
			break;
		case HORN:
			e_card->setLocation(EFFECT_POSITION_X + 4 * ON_BOARD_CARD_WIDTH, EFFECT_POSITION_Y);
			break;
		default:
			break;
		}
		break;
	}
	card->setSize(ON_BOARD_CARD_WIDTH, ON_BOARD_CARD_HEIGHT);
	cards.push_back(card);
}

void Role::setFaction(Faction faction)
{
	this->faction = faction;
}

Faction Role::getFaction()
{
	return this->faction;
}

Lane Role::getLane()
{
	return this->lane;
}

