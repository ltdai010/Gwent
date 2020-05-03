#pragma once
class Role
{
public:
	Role(Lane lane);
	~Role();
	void drawCard(SDL_Renderer* renderer);
	void addCard(Card* card);
	std::vector<Card*> getCards();
	Lane getLane();
	Faction getFaction();
	void setFaction(Faction faction);
private:
	std::vector<Card*> cards;
	Lane lane;
	Faction faction;
};

