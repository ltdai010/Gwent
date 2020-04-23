#pragma once
class Role
{
public:
	Role(Lane lane);
	~Role();
	void drawCard(SDL_Renderer* renderer);
	void addCard(Card* card);
	Lane getLane();
private:
	std::vector<Card*> cards;
	Lane lane;
};

