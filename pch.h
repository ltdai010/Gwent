#ifndef PCH_H
#define PCH_H
enum Empire { NORTHERN, NILFGAARDIAN };
enum Lane {MELEE, RANGE, SIEGE};
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include <vector>
#include "Card.h"
#include "Role.h"
#include "LeaderCard.h"
#include "Deck.h"
#include "Player.h"
#include "Enemy.h"
#include "Board.h"
#include "GameField.h"
#define SCREEN_WIDTH 1600
#define SCREEN_HEIGHT 1000
#define WAIT_TIME 50
#define PLAYER_LEADER_CARD_X 75
#define PLAYER_LEADER_CARD_Y 480
#define ENEMY_LEADER_CARD_X 75
#define ENEMY_LEADER_CARD_Y 5
#define LEADER_CARD_WIDTH 175
#define LEADER_CARD_HEIGHT 325
#define MAX_CARD_IN_DECK 11
#define IN_DECK_CARD_WIDTH 100
#define IN_DECK_CARD_HEIGHT 180
#define HOLDED_CARD_WIDTH 130
#define HOLDED_CARD_HEIGHT 235
#define ON_BOARD_CARD_WIDTH 77
#define ON_BOARD_CARD_HEIGHT 135
#define UNIT_POSITION_X 580
#define MELEE_POSITION_Y 400
#define RANGE_POSITION_Y 550
#define SIEGE_POSITION_Y 650
#define COMBAT_UNIT_NUMBER 12
#define EFFECT_UNIT_NUMBER 5
#define LORD_UNIT_NUMBER 2
#endif //PCH_H
