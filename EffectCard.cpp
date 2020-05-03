#include "pch.h"
#include "EffectCard.h"


EffectCard::EffectCard(SDL_Renderer* renderer, int index, Empire empire):Card(renderer, index, empire)
{
	file.open("txt/effect_card.txt");
	std::string path;
	lane = EFFECT;
	while (!file.eof())
	{
		file >> path;
		if (path == "index")
		{ 
			int i = 0;
			file >> i;
			if (index == i)
			{
				file >> path;
				file >> path;
				if (path == "Clear_Weather")
				{
					effect = CLEAR;
				}
				else if (path == "Biting_Frost")
				{
					effect = MELEE_EF;
				}
				else if (path == "Impenetrable_Fog")
				{
					effect = RANGE_EF;
				}
				else if (path == "Torrential_Rain")
				{
					effect = SIEGE_EF;
				}
				else
				{
					effect = HORN;
				}
			}
		}
	}
}


EffectCard::~EffectCard()
{

}

Effect EffectCard::getEffect()
{
	return effect;
}

void EffectCard::setUnEffect(bool unEffect)
{
	this->unEffect = unEffect;
	rect.x = -200;
	rect.y = -200;
}


bool EffectCard::isUnEffect()
{
	return unEffect;
}


