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
private:
	SDL_Texture* texture;
	Empire empire;
	int index;
	std::ifstream file;
	bool holded;
protected:
	SDL_Rect rect;
};

