#pragma once
class Menu
{
public:
	Menu();
	~Menu();
	void draw();
	bool hoverLeft();
	bool hoverRight();
private:
	void checkMouse();
	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Event* mainEvent;
	SDL_Texture* menu;
	Mix_Music* music;
	SDL_Rect rect;
	Board* board;
	bool on;
	int mouseX;
	int mouseY;
	bool choosed;
};

