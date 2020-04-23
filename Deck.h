#pragma once
class Deck
{
public:
	Deck(SDL_Renderer* renderer, Empire empire);
	~Deck();
	void show(SDL_Renderer* renderer);
	void generateCard(Empire empire, SDL_Renderer* renderer);
	std::vector<Card*> getBunch();
	void unHoldAll();
private:
	std::vector<Card*> bunchOfCard;
};

