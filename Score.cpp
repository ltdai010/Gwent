#include "pch.h"
#include "Score.h"


Score::Score(SDL_Renderer* renderer, Faction faction)
{
	font = TTF_OpenFont("font/Pacifico.ttf", FONT_SIZE);
	if (font == NULL)
	{
		std::cout << TTF_GetError() << std::endl;
	}
	switch (faction)
	{
	case PLAYER:
		initPlayer();
		break;
	case ENEMY:
		initEnemy();
		break;
	default:
		break;
	}
	
	text_surface = TTF_RenderText_Solid(font, "0", color);
	text_texture = SDL_CreateTextureFromSurface(renderer, text_surface);
	SDL_QueryTexture(text_texture, NULL, NULL, &text_rect.w, &text_rect.h);
}


Score::~Score()
{
	delete text_surface;
	delete text_texture;
	delete font;
}

void Score::initEnemy()
{
	color.r = 194;
	color.g = 41;
	color.b = 41;
}

void Score::initPlayer()
{
	color.r = 225;
	color.g = 225;
	color.b = 225;
}

void Score::setText(SDL_Renderer* renderer, int score)
{
	char buffer[10];
	_itoa_s(score, buffer, 4, 10);
	text_surface = TTF_RenderText_Solid(font, buffer, color);
	text_texture = SDL_CreateTextureFromSurface(renderer, text_surface);
	SDL_QueryTexture(text_texture, NULL, NULL, &text_rect.w, &text_rect.h);
}

void Score::setLocation(int x, int y)
{
	text_rect.x = x;
	text_rect.y = y;
}

void Score::draw(SDL_Renderer* renderer)
{
	SDL_RenderCopy(renderer, text_texture, NULL, &text_rect);
}
