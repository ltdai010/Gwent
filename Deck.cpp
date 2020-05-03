#include "pch.h"
#include "Deck.h"


Deck::Deck(SDL_Renderer* renderer, Empire empire)
{
	switch (empire)
	{
	case NORTHERN:
		bunchOfCard.push_back(new LeaderCard(renderer, 17, NORTHERN));
		generateCard(NORTHERN, renderer); 
		break;
	case NILFGAARDIAN:
		bunchOfCard.push_back(new LeaderCard(renderer, 18, NILFGAARDIAN));
		generateCard(NILFGAARDIAN, renderer);
		break;
	default:
		break;
	}
	
}



Deck::~Deck()
{
	for (int i = 0; i < bunchOfCard.size(); ++i)
	{
		bunchOfCard.pop_back();
		--i;
	}
}

std::vector<Card*> Deck::getBunch()
{
	return bunchOfCard;
}

void Deck::show(SDL_Renderer* renderer)
{
	for (int i = 0; i < bunchOfCard.size(); ++i)
	{
		bunchOfCard.at(i)->draw(renderer);
	}
}

bool Deck::allOnBoard()
{
	for (int i = 1; i < bunchOfCard.size(); ++i)
	{
		if (!bunchOfCard.at(i)->isOnBoard())
		{
			return false;
		}
	}
	return true;
}

void Deck::generateCard(Empire empire, SDL_Renderer* renderer)
{
	for (int i = 0; i < MAX_CARD_IN_DECK - 1; ++i)
	{
		srand(time(0) + i);
		int random = rand()%17;
		if(random < COMBAT_UNIT_NUMBER)
			bunchOfCard.push_back(new Card(renderer, random, empire));
		else
			bunchOfCard.push_back(new EffectCard(renderer, random, empire));
	}
}

void Deck::unHoldAll()
{
	for (int i = 0; i < MAX_CARD_IN_DECK; ++i)
	{
		bunchOfCard.at(i)->setHolded(false);
	}
}