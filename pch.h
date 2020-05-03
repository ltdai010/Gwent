#ifndef PCH_H
#define PCH_H
enum Empire { NORTHERN, NILFGAARDIAN };
enum Lane {MELEE, RANGE, SIEGE, EFFECT};
enum Type {HERO, NORMAL};
enum Effect {MELEE_EF, RANGE_EF, SIEGE_EF, CLEAR, HORN};
enum Faction{PLAYER, ENEMY};

template<typename Base, typename T>
inline bool instanceof(const T*) {
	return std::is_base_of<Base, T>::value;
}

#include <fstream>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include "SDL_ttf.h"
#include <vector>
#include "Score.h"
#include "Card.h"
#include "Role.h"
#include "Side.h"
#include "LeaderCard.h"
#include "EffectCard.h"
#include "Deck.h"
#include "Player.h"
#include "Enemy.h"
#include "Board.h"
#include "GameField.h"
#include "Menu.h"
#define SCREEN_WIDTH 1600
#define SCREEN_HEIGHT 1000
#define WAIT_TIME 50
//Leader card
#define PLAYER_LEADER_CARD_X 75
#define PLAYER_LEADER_CARD_Y 480
#define ENEMY_LEADER_CARD_X 75
#define ENEMY_LEADER_CARD_Y 5
#define LEADER_CARD_WIDTH 175
#define LEADER_CARD_HEIGHT 325
//card size
#define IN_DECK_CARD_WIDTH 100
#define IN_DECK_CARD_HEIGHT 180
#define HOLDED_CARD_WIDTH 130
#define HOLDED_CARD_HEIGHT 235
#define ON_BOARD_CARD_WIDTH 77
#define ON_BOARD_CARD_HEIGHT 135
//onboard location
#define UNIT_POSITION_X 580
#define MELEE_POSITION_Y 400
#define RANGE_POSITION_Y 540
#define SIEGE_POSITION_Y 670
#define EFFECT_POSITION_X 50
#define EFFECT_POSITION_Y 335
//unit number
#define MAX_CARD_IN_DECK 11
#define COMBAT_UNIT_NUMBER 12
#define EFFECT_UNIT_NUMBER 5
#define LORD_UNIT_NUMBER 2
//score text
#define SCORE_POSITION_X 470
#define SCORE_MELEE_POSITION_Y 430
#define SCORE_RANGE_POSITION_Y 555
#define SCORE_SIEGE_POSITION_Y 685
#define PLAYER_ENEMY_POSITION_Y_DIFF 400
#define FONT_SIZE 48
#endif //PCH_H
