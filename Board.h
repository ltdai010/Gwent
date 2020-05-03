#pragma once
class Board
{
public:
	Board(SDL_Renderer* renderer, Empire player, Empire enemy);
	~Board();
	void draw(SDL_Renderer* renderer);
	Player* getPlayer();
	Side* getPlayerSide();
	Side* getEnemySide();
	Enemy* getEnemy();
	Role* getEffectRole();
	void updateEffect(SDL_Renderer* renderer);
private:
	void initPlayer(SDL_Renderer* renderer, Empire player, Empire enemy);
	Player* player;
	Enemy* enemy;
	Side* playerSide;
	Side* enemySide;
	Role* effect;
	SDL_Rect rect;
	SDL_Texture* texture;
};

