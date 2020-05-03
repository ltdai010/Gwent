#include "pch.h"
#include "Card.h"


Card::Card(SDL_Renderer* renderer, int index, Empire empire)
{
	holded = false;
	onBoard = false;
	this->empire = empire;
	pickCard(index, renderer);
	file.close();
	if (texture == NULL)
	{
		std::cout << "error load card" << std::endl;
	}
	else
	{
		std::cout << "success load card" << std::endl;
	}
}


Card::~Card()
{
	delete texture;
}

void Card::draw(SDL_Renderer* renderer)
{
	SDL_RenderCopy(renderer, texture, NULL, &rect);
}

void Card::setLocation(int x, int y)
{
	rect.x = x;
	rect.y = y;
}

void Card::setSize(int w, int h)
{
	rect.w = w;
	rect.h = h;
}

int Card::getLocationX()
{
	return rect.x;
}

Lane Card::getLane()
{
	return lane;
}

void Card::setLane(Lane lane)
{
	this->lane = lane;
}

int Card::getLocationY()
{
	return rect.y;
}

Type Card::getType()
{
	return type;
}

void Card::setHolded(bool holded)
{
	if (holded && !onBoard)
	{
		rect.x = rect.x - 15;
		rect.y = rect.y - 55;
		rect.w = HOLDED_CARD_WIDTH;
		rect.h = HOLDED_CARD_HEIGHT;
	}
	else if(this->holded == true && !onBoard)
	{
		rect.x = rect.x + 15;
		rect.y = rect.y + 55;
		rect.w = IN_DECK_CARD_WIDTH;
		rect.h = IN_DECK_CARD_HEIGHT;
	}
	this->holded = holded;
}

void Card::setDamage(int dam)
{
	this->damage = dam;
}

int Card::getDamage()
{
	return damage;
}

bool Card::isHolded()
{
	return holded;
}

void Card::setOnBoard(bool onBoard)
{
	this->onBoard = onBoard;
	this->holded = false;
}

bool Card::isOnBoard()
{
	return onBoard;
}

int Card::getMaxDamage()
{
	return maxDamage;
}

void Card::setMaxDamage(int max)
{
	this->maxDamage = max;
}

void Card::pickCard(int index, SDL_Renderer* renderer)
{
	if (index < COMBAT_UNIT_NUMBER)
	{
		if (empire == NORTHERN)
			file.open("txt/NT_combat_card.txt");
		else
			file.open("txt/NG_combat_card.txt");
	}
	else if (index < COMBAT_UNIT_NUMBER + EFFECT_UNIT_NUMBER)
	{
		file.open("txt/effect_card.txt");
	}
	else
	{
		file.open("txt/lord_card.txt");
	}
	std::string path;
	while (!file.eof())
	{
		file >> path;
		if (path == "index")
		{
			int i;
			file >> i;
			if (i == index && index < COMBAT_UNIT_NUMBER)
			{
				std::string s;
				if(empire == NORTHERN)
					s = "img/card/Northern/";
				else
					s = "img/card/Nilfgaardian/";
				file >> path;
				file >> path;
				s += path + ".png";
				texture = IMG_LoadTexture(renderer, s.c_str());
				file >> path;
				int dam = 0;
				file >> dam;
				this->damage = dam;
				this->maxDamage = dam;
				file >> path;
				file >> path;
				std::cout << path;
				if (path == "melee")
				{
					this->lane = MELEE;
				}
				else if(path == "range")
				{
					this->lane = RANGE;
				}
				else
				{
					this->lane = SIEGE;
				}
				file >> path;
				file >> path;
				if (path == "normal")
				{
					this->type = NORMAL;
				}
				else
				{
					this->type = HERO;
				}
				break;
			}
			else if(i == index && index < COMBAT_UNIT_NUMBER + EFFECT_UNIT_NUMBER)
			{
				std::string s;
				if (empire == NORTHERN)
					s = "img/card/Northern/";
				else
					s = "img/card/Nilfgaardian/";
				file >> path;
				file >> path;
				s += path + ".png";
				texture = IMG_LoadTexture(renderer, s.c_str());
			}
			else if(i == index)
			{
				std::string s;
				if (empire == NORTHERN)
					s = "img/card/Northern/";
				else
					s = "img/card/Nilfgaardian/";
				file >> path;
				file >> path;
				s += path + ".png";
				texture = IMG_LoadTexture(renderer, s.c_str());
			}
		}
	}
}
	


