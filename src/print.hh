/*
 * PRINT.HH
 * This file contains print function of yatch dice game.
 */

#ifndef _PRINT_HH_
#define _PRINT_HH_

#include <string>
#include <vector>

// Name of combinations.
extern std::string names[];

// Current scores, where selection is represented as bitmask.
void print(int selection, const std::vector<int>& score);

#endif
