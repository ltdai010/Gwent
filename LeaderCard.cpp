#include "pch.h"
#include "LeaderCard.h"


LeaderCard::LeaderCard(SDL_Renderer* renderer, int index, Empire empire) :Card(renderer, index, empire)
{
	rect.x = 75;
	rect.y = 10;
	rect.w = 175;
	rect.h = 325;
}


LeaderCard::~LeaderCard()
{

}
