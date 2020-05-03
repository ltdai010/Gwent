#include "pch.h"
#include "Board.h"


Board::Board(SDL_Renderer* renderer, Empire player, Empire enemy)
{
	texture = IMG_LoadTexture(renderer, "img/gwentBoard.png");
	if (texture == NULL)
	{
		std::cout << "error load board" << std::endl;
	}
	else
	{
		std::cout << "success load board" << std::endl;
	}
	rect.x = 0;
	rect.y = 0;
	rect.w = SCREEN_WIDTH;
	rect.h = SCREEN_HEIGHT;
	effect = new Role(EFFECT);
	effect->setFaction(PLAYER);
	initPlayer(renderer, player, enemy);
	playerSide = new Side(renderer, PLAYER);
	enemySide = new Side(renderer, ENEMY);
}



Board::~Board()
{
	delete texture;
}


void Board::initPlayer(SDL_Renderer* renderer, Empire player, Empire enemy)
{
	this->player = new Player("diaz");
	this->enemy = new Enemy();
	this->player->setDeck(new Deck(renderer, player));
	this->player->getDeck()->getBunch().at(0)->setLocation(PLAYER_LEADER_CARD_X, PLAYER_LEADER_CARD_Y);
	this->player->getDeck()->getBunch().at(0)->setSize(LEADER_CARD_WIDTH, LEADER_CARD_HEIGHT);
	this->player->arrangeCard();
	this->enemy->setDeck(new Deck(renderer, enemy));
	this->enemy->getDeck()->getBunch().at(0)->setLocation(ENEMY_LEADER_CARD_X, ENEMY_LEADER_CARD_Y);
	this->enemy->getDeck()->getBunch().at(0)->setSize(LEADER_CARD_WIDTH, LEADER_CARD_HEIGHT);
}


void Board::draw(SDL_Renderer* renderer)
{
	SDL_RenderCopy(renderer, texture, NULL, &rect);
	player->getDeck()->show(renderer);
	enemy->getDeck()->show(renderer);
	playerSide->draw(renderer);
	enemySide->draw(renderer);
}

Role* Board::getEffectRole()
{
	return effect;
}

void Board::updateEffect(SDL_Renderer* renderer)
{
	for (int i = 0; i < effect->getCards().size(); ++i)
	{
		EffectCard* e_card = static_cast<EffectCard*>(effect->getCards().at(i));
		if (e_card->getEffect() == MELEE_EF && !e_card->isUnEffect())
		{
			for (int j = 0; j < playerSide->getRole(MELEE)->getCards().size(); ++j)
			{
				if (playerSide->getRole(MELEE)->getCards().at(j)->getType() == NORMAL)
					playerSide->getRole(MELEE)->getCards().at(j)->setDamage(1);
			}
			for (int j = 0; j < enemySide->getRole(MELEE)->getCards().size(); ++j)
			{
				if (enemySide->getRole(MELEE)->getCards().at(j)->getType() == NORMAL)
					enemySide->getRole(MELEE)->getCards().at(j)->setDamage(1);
			}
		}
		else if (e_card->getEffect() == RANGE_EF && !e_card->isUnEffect())
		{
			for (int j = 0; j < playerSide->getRole(RANGE)->getCards().size(); ++j)
			{
				if (playerSide->getRole(RANGE)->getCards().at(j)->getType() == NORMAL)
					playerSide->getRole(RANGE)->getCards().at(j)->setDamage(1);
			}
			for (int j = 0; j < enemySide->getRole(RANGE)->getCards().size(); ++j)
			{
				if (enemySide->getRole(RANGE)->getCards().at(j)->getType() == NORMAL)
					enemySide->getRole(RANGE)->getCards().at(j)->setDamage(1);
			}
		}
		else if (e_card->getEffect() == SIEGE_EF && !e_card->isUnEffect())
		{
			for (int j = 0; j < playerSide->getRole(SIEGE)->getCards().size(); ++j)
			{
				if (playerSide->getRole(SIEGE)->getCards().at(j)->getType() == NORMAL)
					playerSide->getRole(SIEGE)->getCards().at(j)->setDamage(1);
			}
			for (int j = 0; j < enemySide->getRole(SIEGE)->getCards().size(); ++j)
			{
				if (enemySide->getRole(SIEGE)->getCards().at(j)->getType() == NORMAL)
					enemySide->getRole(SIEGE)->getCards().at(j)->setDamage(1);
			}
		}
		else if (e_card->getEffect() == CLEAR)
		{
			e_card->setUnEffect(true);
			for (int j = 0; j < i; ++j)
			{
				EffectCard* e = static_cast<EffectCard*>(effect->getCards().at(j));
				e->setUnEffect(true);
				playerSide->clearEffect();
				enemySide->clearEffect();
			}
		}
		else
		{
			if (playerSide->totalMaxDamage(playerSide->getRole(MELEE)) >= playerSide->totalMaxDamage(playerSide->getRole(RANGE)) &&
				playerSide->totalMaxDamage(playerSide->getRole(MELEE)) >= playerSide->totalMaxDamage(playerSide->getRole(SIEGE)))
			{
				playerSide->clearBuff();
				playerSide->doubleDamage(playerSide->getRole(MELEE));
			}
			else if (playerSide->totalMaxDamage(playerSide->getRole(RANGE)) >= playerSide->totalMaxDamage(playerSide->getRole(MELEE)) &&
				playerSide->totalMaxDamage(playerSide->getRole(RANGE)) >= playerSide->totalMaxDamage(playerSide->getRole(SIEGE)))
			{
				playerSide->clearBuff();
				playerSide->doubleDamage(playerSide->getRole(RANGE));
			}
			else
			{
				playerSide->clearBuff();
				playerSide->doubleDamage(playerSide->getRole(SIEGE));
			}
			if (enemySide->totalMaxDamage(enemySide->getRole(MELEE)) >= enemySide->totalMaxDamage(enemySide->getRole(RANGE)) &&
				enemySide->totalMaxDamage(enemySide->getRole(MELEE)) >= enemySide->totalMaxDamage(enemySide->getRole(SIEGE)))
			{
				enemySide->clearBuff();
				enemySide->doubleDamage(enemySide->getRole(MELEE));
			}
			else if (enemySide->totalMaxDamage(enemySide->getRole(RANGE)) >= enemySide->totalMaxDamage(enemySide->getRole(MELEE)) &&
				enemySide->totalMaxDamage(enemySide->getRole(RANGE)) >= enemySide->totalMaxDamage(enemySide->getRole(SIEGE)))
			{
				enemySide->clearBuff();
				enemySide->doubleDamage(enemySide->getRole(RANGE));
			}
			else
			{
				enemySide->clearBuff();
				enemySide->doubleDamage(enemySide->getRole(SIEGE));
			}
		}
	}
	playerSide->updateScore(renderer);
	enemySide->updateScore(renderer);
}

Side* Board::getPlayerSide()
{
	return playerSide;
}

Side* Board::getEnemySide()
{
	return enemySide;
}


Player* Board::getPlayer()
{
	return player;
}


Enemy* Board::getEnemy()
{
	return enemy;
}
