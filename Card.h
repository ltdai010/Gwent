#pragma once
class Card
{
public:
	Card(SDL_Renderer* renderer, int index, Empire empire);
	~Card();
	void draw(SDL_Renderer* renderer);
	void pickCard(int index, SDL_Renderer* renderer);
	void setLocation(int x, int y);
	void setSize(int w, int h);
	int getLocationX();
	int getLocationY();
	void setHolded(bool holded);
	bool isHolded();
	void setOnBoard(bool onBoard);
	bool isOnBoard();
	void setLane(Lane lane);
	void setDamage(int dam);
	int getDamage();
	int getMaxDamage();
	void setMaxDamage(int max);
	Lane getLane();
	Type getType();
protected:
	SDL_Texture* texture;
	Empire empire;
	int index;
	int damage;
	int maxDamage;
	Type type;
	bool holded;
	bool onBoard;
	std::ifstream file;
	SDL_Rect rect;
	Lane lane;
};

