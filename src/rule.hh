/*
 * RULE.HH
 * This file contains basic rules of yacht dice game.
 */

#ifndef _RULE_HH_
#define _RULE_HH_

#include <array>
#include <functional>

// The number of combination used in game.
const int TOTAL_SUIT = 12;

// The number of combinations included in "upper section bonus."
const int BONUS_SUIT = 6;

// Score to acheive upper section bonus.
const int BONUS_LIMIT = 63;

// Bonus score granted, if upper section bonus limit is acheived.
const int BONUS_SCORE = 35;

// The number of dice used in game.
const int TOTAL_DICE_COUNT = 5;

// The number of sides in dice.
const int DICE_NO = 6;

// The number of re-rolls given in game.
const int TOTAL_DICE_ROUND = 2;

using Dices = std::array<int, TOTAL_DICE_COUNT>;

// Scoring function used in game
extern std::function<int(Dices)> scoring[TOTAL_SUIT];

#endif