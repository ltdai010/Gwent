#include "pch.h"
#include "Board.h"


Board::Board(SDL_Renderer* renderer)
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
	initPlayer(renderer);
	initRole();
}



Board::~Board()
{
	delete texture;
}

void Board::initPlayer(SDL_Renderer* renderer)
{
	player = new Player("diaz");
	enemy = new Enemy();
	player->setDeck(new Deck(renderer, NORTHERN));
	player->getDeck()->getBunch().at(0)->setLocation(PLAYER_LEADER_CARD_X, PLAYER_LEADER_CARD_Y);
	player->getDeck()->getBunch().at(0)->setSize(LEADER_CARD_WIDTH, LEADER_CARD_HEIGHT);
	player->arrangeCard();
	enemy->setDeck(new Deck(renderer, NILFGAARDIAN));
	enemy->getDeck()->getBunch().at(0)->setLocation(ENEMY_LEADER_CARD_X, ENEMY_LEADER_CARD_Y);
	enemy->getDeck()->getBunch().at(0)->setSize(LEADER_CARD_WIDTH, LEADER_CARD_HEIGHT);
}

void Board::initRole()
{
	melee = new Role(MELEE);
	range = new Role(RANGE);
	siege = new Role(SIEGE);
}

void Board::draw(SDL_Renderer* renderer)
{
	SDL_RenderCopy(renderer, texture, NULL, &rect);
	player->getDeck()->show(renderer);
	enemy->getDeck()->show(renderer);
	melee->drawCard(renderer);
}

Role* Board::getRole(Lane lane)
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

Player* Board::getPlayer()
{
	return player;
}

Enemy* Board::getEnemy()
{
	return enemy;
}
