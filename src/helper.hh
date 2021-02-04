/*
 * HELPER.HH
 * This file contains basic bit-DP helper of yacht dice game.
 */


#ifndef _HELPER_HH_
#define _HELPER_HH_

#include "rule.hh"

// Calculate Binom(n, r);
constexpr int Binom(int n, int r)
{
    int ans = 1;
    for(int i=1; i<=n-r; ++i)
        ans = ans * (r+i) / i;
    return ans;
}

const int TOTAL_DICE_COMB = Binom(DICE_NO + TOTAL_DICE_COUNT - 1, TOTAL_DICE_COUNT);

// Init function should be called initially to use helper functions.
void init();

// Encode dices to [0, TOTAL_DICE_COMB) integer.
int encode(Dices d);

// Decode [0, TOTAL_DICE_COMB) integer to dices.
Dices decode(int v);

/*
 * trans[roll][from][to]:
 * roll is represented as bitmask, from and to is encoded using `encode` function.
 * Probability of dices showing `to`, when `roll` is selected as re-roll and current dices are from.
 */
extern double trans[1<<TOTAL_DICE_COUNT][TOTAL_DICE_COMB][TOTAL_DICE_COMB];

// score[suit][d]: score of combination #suit, when dices are shown as d.
extern int score[TOTAL_SUIT][TOTAL_DICE_COMB];

#endif