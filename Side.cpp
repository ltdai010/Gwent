#include "pch.h"
#include "Side.h"


Side::Side(SDL_Renderer* renderer, Faction faction)
{
	this->faction = faction;
	initRole();
	initScoreText(renderer, faction);
}


Side::~Side()
{
	delete melee;
	delete range;
	delete siege;
	delete melee_score;
	delete range_score;
	delete siege_score;
}

void Side::initScoreText(SDL_Renderer* renderer, Faction faction)
{
	melee_score = new Score(renderer, faction);
	range_score = new Score(renderer, faction);
	siege_score = new Score(renderer, faction);
	switch (faction)
	{
	case PLAYER:
		melee_score->setLocation(SCORE_POSITION_X, SCORE_MELEE_POSITION_Y);
		range_score->setLocation(SCORE_POSITION_X, SCORE_RANGE_POSITION_Y);
		siege_score->setLocation(SCORE_POSITION_X, SCORE_SIEGE_POSITION_Y);
		break;
	case ENEMY:
		melee_score->setLocation(SCORE_POSITION_X, SCORE_SIEGE_POSITION_Y - PLAYER_ENEMY_POSITION_Y_DIFF);
		range_score->setLocation(SCORE_POSITION_X, SCORE_RANGE_POSITION_Y - PLAYER_ENEMY_POSITION_Y_DIFF);
		siege_score->setLocation(SCORE_POSITION_X, SCORE_MELEE_POSITION_Y - PLAYER_ENEMY_POSITION_Y_DIFF);
		break;
	default:
		break;
	}
}

void Side::draw(SDL_Renderer* renderer)
{
	melee_score->draw(renderer);
	range_score->draw(renderer);
	siege_score->draw(renderer);
}


Role* Side::getRole(Lane lane)
{
	switch (lane)
	{
	case MELEE:
		return melee;
		break;
	case RANGE:
		return range;
		break;
	case SIEGE:
		return siege;
		break;
	default:
		break;
	}
}

int Side::totalDamage(Role* role)
{
	int s = 0;
	for (int i = 0; i < role->getCards().size(); ++i)
	{
		s += role->getCards().at(i)->getDamage();
	}
	return s;
}

void Side::updateScore(SDL_Renderer* renderer)
{
	melee_score->setText(renderer, totalDamage(melee));
	range_score->setText(renderer, totalDamage(range));
	siege_score->setText(renderer, totalDamage(siege));
}

void Side::clearBuff()
{
	if (totalDamage(melee) > totalMaxDamage(melee))
	{
		for (int i = 0; i < melee->getCards().size(); ++i)
		{
			melee->getCards().at(i)->setDamage(melee->getCards().at(i)->getMaxDamage());
		}
	}
	else if (totalDamage(range) > totalMaxDamage(range))
	{
		for (int i = 0; i < range->getCards().size(); ++i)
		{
			range->getCards().at(i)->setDamage(range->getCards().at(i)->getMaxDamage());
		}
	}
	else if (totalDamage(siege) > totalMaxDamage(siege))
	{
		for (int i = 0; i < siege->getCards().size(); ++i)
		{
			siege->getCards().at(i)->setDamage(siege->getCards().at(i)->getMaxDamage());
		}
	}
}

int Side::totalMaxDamage(Role* role)
{
	int s = 0;
	for (int i = 0; i < role->getCards().size(); ++i)
	{
		s += role->getCards().at(i)->getMaxDamage();
	}
	return s;
}


void Side::clearEffect()
{
	for (int i = 0; i < melee->getCards().size(); ++i)
	{
		melee->getCards().at(i)->setDamage(melee->getCards().at(i)->getMaxDamage());
	}
	for (int i = 0; i < range->getCards().size(); ++i)
	{
		range->getCards().at(i)->setDamage(range->getCards().at(i)->getMaxDamage());
	}
	for (int i = 0; i < siege->getCards().size(); ++i)
	{
		siege->getCards().at(i)->setDamage(siege->getCards().at(i)->getMaxDamage());
	}
}

void Side::doubleDamage(Role* role)
{
	for (int i = 0; i < role->getCards().size(); ++i)
	{
		role->getCards().at(i)->setDamage(role->getCards().at(i)->getMaxDamage() * 2);
	}
}

void Side::initRole()
{
	melee = new Role(MELEE);
	melee->setFaction(faction);
	range = new Role(RANGE);
	range->setFaction(faction);
	siege = new Role(SIEGE);
	siege->setFaction(faction);
}