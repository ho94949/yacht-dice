/*
 * PRINT.CC
 * This file contains print function of yatch dice game.
 */

#include "calc.hh"
#include "print.hh"

#include <algorithm>

std::string names[] = {"One", "Two", "Three", "Four", "Five", "Six", "Choice", "Four Card", "Full House", "S.Straight", "L.Straight",  "Yacht"};

void print(int selection, const std::vector<int>& score)
{
    int sumv = 0, bonus = 0;
    puts("+----+------------+--------------+");
    for(int i=0; i<6; ++i)
    {
        printf("| %2d |%*s ", i+1, 11, names[i].c_str());
        if(selection&(1<<i)) printf("|      %2d      |\n", score[i]);
        else puts("|              |");
        bonus += score[i];
        sumv += score[i];
    }
    puts("+----+-------+----+--------------+");
    printf("|%*s |", 11, "Bonus");
    printf(" %2d ", bonus);
    if(bonus >= BONUS_LIMIT || (selection & ((1<<BONUS_SUIT)-1)) == ((1<<BONUS_SUIT)-1))
        printf("|      %2d      |\n", bonus>=BONUS_LIMIT?BONUS_SCORE:0);
    else
        puts("|              |");
    puts("+----+-------+----+--------------+");
    for(int i=6; i<12; ++i)
    {
        printf("| %2d |%*s ", i+1, 11, names[i].c_str());
        if(selection&(1<<i)) printf("|      %2d      |\n", score[i]);
        else puts("|              |");
        sumv += score[i];
    }
    puts("+----+------------+--------------+");
    double est = dpave[selection][std::min(bonus, BONUS_LIMIT)];
    printf("Total: %d\n", sumv+(bonus>=BONUS_LIMIT?BONUS_SCORE:0));
    if(est == 0) est = (bonus>=BONUS_LIMIT?BONUS_SCORE:0);
    printf("Estimation: %f\n", sumv+est);
};