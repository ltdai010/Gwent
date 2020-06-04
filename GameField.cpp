#include "pch.h"
#include "GameField.h"


GameField::GameField(SDL_Window* window, SDL_Renderer* renderer, SDL_Event* event, Empire player, Empire enemy)
{
	this->window = window;
	this->renderer = renderer;
	mainEvent = event;
	gameOver = false;
	endScene = IMG_LoadTexture(renderer, "img/black.png");
	font = TTF_OpenFont("font/Pacifico.ttf", 90);
	if (font == NULL)
	{
		std::cout << TTF_GetError() << std::endl;
	}
	color.r = 194;
	color.g = 41;
	color.b = 41;
	endText_s = TTF_RenderText_Solid(font, "YOU WIN", color);
	endText = SDL_CreateTextureFromSurface(renderer, endText_s);
	SDL_QueryTexture(endText, NULL, NULL, &text_rect.w, &text_rect.h);
	text_rect.x = 600;
	text_rect.y = 450;
	if (endScene == NULL)
	{
		std::cout << "Error load endscene" << std::endl;
	}
	else
	{
		SDL_SetTextureBlendMode(endScene, SDL_BLENDMODE_BLEND);
		SDL_SetTextureAlphaMod(endScene, 125);
	}
	rect.x = 0;
	rect.y = 0;
	rect.w = SCREEN_WIDTH;
	rect.h = SCREEN_HEIGHT;
	board = new Board(renderer, player, enemy);
	mouseX = 0;
	mouseY = 0;
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		std::cout << "sound error" << std::endl;
	}
	music = Mix_LoadMUS("audio/Whispers.mp3");
	Mix_PlayMusic(music, -1);
}


GameField::~GameField()
{
	delete music;
	delete endScene;
}

void GameField::mouseCheck()
{
	if (mainEvent->type == SDL_MOUSEBUTTONDOWN)
	{
		if (mainEvent->button.button == SDL_BUTTON_LEFT)
		{
			SDL_GetMouseState(&mouseX, &mouseY);
			clicked = true;
		}
	}
	if (mainEvent->type == SDL_MOUSEBUTTONUP && clicked)
	{
		if (mainEvent->button.button == SDL_BUTTON_LEFT)
		{
			for (int i = 1; i < board->getPlayer()->getDeck()->getBunch().size(); ++i)
			{
				if (board->getPlayer()->getDeck()->getBunch().at(i) != NULL && 
					hoverCard(board->getPlayer()->getDeck()->getBunch().at(i), mouseX, mouseY))
				{
					std::cout << "Mouse left clicked" << std::endl;
					//check if the card is already hold
					if (board->getPlayer()->getDeck()->getBunch().at(i)->isHolded() && board->getPlayer()->inTurn())
					{
						board->getPlayer()->getDeck()->getBunch().at(i)->setOnBoard(true);
						if (board->getPlayer()->getDeck()->getBunch().at(i)->getLane() == EFFECT)
						{
							board->getEffectRole()->addCard(board->getPlayer()->getDeck()->getBunch().at(i));
						}
						else
						{
							board->getPlayerSide()->getRole(board->getPlayer()->getDeck()->getBunch().at(i)->getLane()
							)->addCard(board->getPlayer()->getDeck()->getBunch().at(i));
						}
						board->getPlayer()->setTurn(false);
						board->getEnemy()->setTurn(true);
						board->updateEffect(renderer);
						std::cout << board->getPlayerSide()->totalDamage(board->getPlayerSide()->getRole(MELEE)) << std::endl;
						std::cout << board->getPlayerSide()->totalDamage(board->getPlayerSide()->getRole(RANGE)) << std::endl;
						std::cout << board->getPlayerSide()->totalDamage(board->getPlayerSide()->getRole(SIEGE)) << std::endl;
					}
					//if not, hold the card
					board->getPlayer()->getDeck()->unHoldAll();
					board->getPlayer()->getDeck()->getBunch().at(i)->setHolded(true);
					board->getPlayer()->setHolded(true);
				}
				else if (!hoverDeck(mouseX, mouseY))
				{
					board->getPlayer()->getDeck()->unHoldAll();
				}
			}
			clicked = false;
		}
	}
}

void GameField::enemyTurn()
{
	if (board->getEnemy()->inTurn())
	{
		int playerMelee = board->getPlayerSide()->totalDamage(board->getPlayerSide()->getRole(MELEE));
		int playerRange = board->getPlayerSide()->totalDamage(board->getPlayerSide()->getRole(RANGE));
		int playerSiege = board->getPlayerSide()->totalDamage(board->getPlayerSide()->getRole(SIEGE));
		int playerTotalDamage = playerMelee + playerRange + playerSiege;
		int enemyMelee = board->getEnemySide()->totalDamage(board->getEnemySide()->getRole(MELEE));
		int enemyRange = board->getEnemySide()->totalDamage(board->getEnemySide()->getRole(RANGE));
		int enemySiege = board->getEnemySide()->totalDamage(board->getEnemySide()->getRole(SIEGE));
		int enemyTotalDamage = enemyMelee + enemyRange + enemySiege;
		if (playerTotalDamage >= enemyTotalDamage)
		{
			//if player's melee score is high
			if (playerMelee > enemyMelee)
			{
				for (int i = 0; i < board->getEnemy()->getDeck()->getBunch().size(); ++i)
				{
					if (board->getEnemy()->getDeck()->getBunch().at(i)->getLane() == EFFECT )
					{
						EffectCard* buffer = static_cast<EffectCard*>(board->getEnemy()->getDeck()->getBunch().at(i));
						if (buffer->getEffect() == MELEE_EF && !buffer->isOnBoard())
						{
							buffer->setOnBoard(true);
							board->getEffectRole()->addCard(buffer);
							board->getPlayer()->setTurn(true);
							board->getEnemy()->setTurn(false);
							board->updateEffect(renderer);
							return;
						}
					}
				}
			}
			//if player's range score is high
			if (playerRange > enemyRange)
			{
				for (int i = 0; i < board->getEnemy()->getDeck()->getBunch().size(); ++i)
				{
					if (board->getEnemy()->getDeck()->getBunch().at(i)->getLane() == EFFECT)
					{
						EffectCard* buffer = static_cast<EffectCard*>(board->getEnemy()->getDeck()->getBunch().at(i));
						if (buffer->getEffect() == RANGE_EF && !buffer->isOnBoard())
						{
							buffer->setOnBoard(true);
							board->getEffectRole()->addCard(buffer);
							board->getPlayer()->setTurn(true);
							board->getEnemy()->setTurn(false);
							board->updateEffect(renderer);
							return;
						}
					}
				}
			}
			//if player's siege score is high
			if (playerSiege > enemySiege)
			{
				for (int i = 0; i < board->getEnemy()->getDeck()->getBunch().size(); ++i)
				{
					if (board->getEnemy()->getDeck()->getBunch().at(i)->getLane() == EFFECT)
					{
						EffectCard* buffer = static_cast<EffectCard*>(board->getEnemy()->getDeck()->getBunch().at(i));
						if (buffer->getEffect() == SIEGE_EF && !buffer->isOnBoard())
						{
							buffer->setOnBoard(true);
							board->getEffectRole()->addCard(buffer);
							board->getPlayer()->setTurn(true);
							board->getEnemy()->setTurn(false);
							board->updateEffect(renderer);
							return;
						}
					}
				}
			}
		}
		for (int i = 1; i < board->getEnemy()->getDeck()->getBunch().size(); ++i)
		{
			if (!board->getEnemy()->getDeck()->getBunch().at(i)->isOnBoard())
			{
				board->getEnemy()->getDeck()->getBunch().at(i)->setOnBoard(true);
				if (board->getEnemy()->getDeck()->getBunch().at(i)->getLane() == EFFECT)
				{
					board->getEffectRole()->addCard(board->getEnemy()->getDeck()->getBunch().at(i));
				}
				else
				{
					board->getEnemySide()->getRole(board->getEnemy()->getDeck()->getBunch().at(i)->getLane())
						->addCard(board->getEnemy()->getDeck()->getBunch().at(i));
				}
				board->getPlayer()->setTurn(true);
				board->getEnemy()->setTurn(false);
				board->updateEffect(renderer);
				return;
			}
		}
	}
}

bool GameField::over()
{
	if (board->getPlayer()->getDeck()->allOnBoard() && board->getEnemy()->getDeck()->allOnBoard())
	{
		return true;
	}
	return false;
}

void GameField::checkResult()
{
	int playerScore = board->getPlayerSide()->totalDamage(board->getPlayerSide()->getRole(MELEE)) +
		board->getPlayerSide()->totalDamage(board->getPlayerSide()->getRole(RANGE)) +
		board->getPlayerSide()->totalDamage(board->getPlayerSide()->getRole(SIEGE));
	int enemyScore = board->getEnemySide()->totalDamage(board->getEnemySide()->getRole(MELEE)) +
		board->getEnemySide()->totalDamage(board->getEnemySide()->getRole(RANGE)) +
		board->getEnemySide()->totalDamage(board->getEnemySide()->getRole(SIEGE));
	if (playerScore > enemyScore)
	{
		color.r = 255;
		color.g = 0;
		color.b = 0;
		endText_s = TTF_RenderText_Solid(font, "YOU WIN", color);
	}
	else if (playerScore < enemyScore)
	{
		color.r = 255;
		color.g = 255;
		color.b = 255;
		endText_s = TTF_RenderText_Solid(font, "YOU LOSE", color);
	}
	else
	{
		color.r = 255;
		color.g = 255;
		color.b = 0;
		endText_s = TTF_RenderText_Solid(font, "DRAW", color);
	}
	SDL_QueryTexture(endText, NULL, NULL, &text_rect.w, &text_rect.h);
	endText = SDL_CreateTextureFromSurface(renderer, endText_s);
}

void GameField::gameLoop()
{
	Uint32 time = SDL_GetTicks();
	board->getPlayer()->setTurn(true);
	while (mainEvent->type != SDL_QUIT && !gameOver)
	{
		if (time + WAIT_TIME < SDL_GetTicks())
		{
			SDL_PollEvent(mainEvent);
			SDL_RenderClear(renderer);
			
			mouseCheck();
			enemyTurn();

			board->draw(renderer);
			if (over())
			{
				checkResult();
				SDL_RenderCopy(renderer, endScene, NULL, &rect);
				SDL_RenderCopy(renderer, endText, NULL, &text_rect);
				gameOver = true;
				SDL_RenderPresent(renderer);
				SDL_Delay(5000);
			}
			SDL_RenderPresent(renderer);	
		}
	}
}

bool GameField::hoverCard(Card* card, int mouseX, int mouseY)
{
	if (mouseX > card->getLocationX() &&
		mouseX < card->getLocationX() +
		IN_DECK_CARD_WIDTH &&
		mouseY > card->getLocationY() &&
		mouseY < card->getLocationY() +
		IN_DECK_CARD_HEIGHT)
	{
		return true;
	}
	return false;
}

bool GameField::hoverDeck(int mouseX, int mouseY)
{
	if (mouseX > 175 && mouseX < SCREEN_WIDTH - 175
		&& mouseY > SCREEN_HEIGHT - 190 && mouseY < SCREEN_HEIGHT)
	{
		return true;
	}
	return false;
}


