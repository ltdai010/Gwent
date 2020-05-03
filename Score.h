#pragma once
class Score
{
public:
	Score(SDL_Renderer* renderer, Faction faction);
	void setLocation(int x, int y);
	void draw(SDL_Renderer* renderer);
	void setText(SDL_Renderer* renderer, int score);
	void initPlayer();
	void initEnemy();
	~Score();
private:
	SDL_Surface* text_surface;
	SDL_Texture* text_texture;
	SDL_Color color;
	TTF_Font *font;
	SDL_Rect text_rect;
};

