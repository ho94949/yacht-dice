/*
 * CALC.HH
 * This file contains calculations of yacht dice game.
 */

#ifndef _CALC_HH_
#define _CALC_HH_

#include "helper.hh"

/*
 * dpave[i][j], expected future gain (bonus excluded)
 * when current selected combinations are i, sum of bonus score is j.
 */
extern double dpave[1<<TOTAL_SUIT][BONUS_LIMIT+1];

/*
 * op[k][i][j][s], optimal operation
 * when current selected combinations are i, sum of bonus score is j,
 * remaining re-roll is k, and current combination is s.
 * when k is 0, op is combination to choose. otherwise, op is bitmasked re-roll.
 */
extern int8_t op[TOTAL_DICE_ROUND+1][1<<TOTAL_SUIT][BONUS_LIMIT+1][TOTAL_DICE_COMB];

// Main calculation, fills dpave and op array.
void calc();

// Load calculated data from file_name to dpave and op array.
// Returns true on success.
bool load(const char* file_name);

// Save calculated data from dpave and op array to file_name
// Returns true on success.
bool save(const char* file_name);



#endif