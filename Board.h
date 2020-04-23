#pragma once
class Board
{
public:
	Board(SDL_Renderer* renderer);
	~Board();
	void draw(SDL_Renderer* renderer);
	void initPlayer(SDL_Renderer* renderer);
	void initRole();
	Player* getPlayer();
	Enemy* getEnemy();
	Role* getRole(Lane lane);
private:
	Player* player;
	Enemy* enemy;
	SDL_Rect rect;
	SDL_Texture* texture;
	Role* melee;
	Role* range;
	Role* siege;
};

