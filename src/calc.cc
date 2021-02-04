/*
 * CALC.CC
 * This file contains calculations of yacht dice game.
 */

#include "calc.hh"

#include <algorithm>
#include <iostream>
#include <cstdlib>

double dpave[1<<TOTAL_SUIT][BONUS_LIMIT+1];
int8_t op[TOTAL_DICE_ROUND+1][1<<TOTAL_SUIT][BONUS_LIMIT+1][TOTAL_DICE_COMB];

bool save(const char* file_name)
{
    FILE *fp = fopen(file_name, "wb");
    if(!fp) return false;

    if(sizeof(dpave)/sizeof(double) !=
        fwrite(dpave, sizeof(double), sizeof(dpave)/sizeof(double), fp))
            return false;
    if(sizeof(op)/sizeof(int8_t) !=
        fwrite(op, sizeof(int8_t), sizeof(op)/sizeof(int8_t), fp))
            return false;

    fclose(fp);
    return true;
}

bool load(const char* file_name)
{
    FILE *fp = fopen(file_name, "rb");
    if(!fp)
    {
        std::cerr << "Cannot open " << file_name << std::endl;
        return false;
    }

    if(sizeof(dpave)/sizeof(double) !=
        fread(dpave, sizeof(double), sizeof(dpave)/sizeof(double), fp))
        {
            std::cerr << "Corrupted " << file_name << std::endl;
            return false;
        }
    if(sizeof(op)/sizeof(int8_t) !=
        fread(op, sizeof(int8_t), sizeof(op)/sizeof(int8_t), fp))
        {
            std::cerr << "Corrupted " << file_name << std::endl;
            return false;
        }

    fclose(fp);
    return true;
}

void calc()
{
    /*
    * dp[k][i][j][s], expected future gain (bonus excluded)
    * when current selected combinations are i, sum of bonus score is j,
    * remaining re-roll is k, and current combination is s.
    */
    auto dp = new double[TOTAL_DICE_ROUND+1][1<<TOTAL_SUIT][BONUS_LIMIT+1][TOTAL_DICE_COMB];


    dpave[(1<<TOTAL_SUIT)-1][BONUS_LIMIT] = BONUS_SCORE;
    for(int selected_suit=(1<<TOTAL_SUIT)-2; selected_suit>=0; --selected_suit)
    {
        std::cerr << "Calculating: " << ((1<<TOTAL_SUIT) - selected_suit) << "/" << (1<<TOTAL_SUIT) << std::endl;
        for(int bonus = 0; bonus <= BONUS_LIMIT; ++bonus)
        {
            // First, calculate maximum possible score when no bonus is given.
            for(int comb = 0; comb < TOTAL_DICE_COMB; ++comb)
            {
                double maxv = -1; int maxi = -1;
                for(int j=0; j<TOTAL_SUIT; ++j)
                {
                    if((1<<j)&selected_suit) continue;
                    int add_score = score[j][comb];
                    int new_suit = selected_suit | (1<<j);
                    int new_bonus = bonus;
                    if(j < BONUS_SUIT) new_bonus = std::min(BONUS_LIMIT, bonus + add_score);
                    double val = dpave[new_suit][new_bonus] + add_score;
                    if(maxv < val) maxv = val, maxi = j;
                }
                dp[0][selected_suit][bonus][comb] = maxv;
                op[0][selected_suit][bonus][comb] = maxi;
            }

            // Second, choice maximum dice roll.
            for(int round = 1; round <= TOTAL_DICE_ROUND; ++round)
            {
                for(int from = 0; from < TOTAL_DICE_COMB; ++from)
                {
                    double maxv = -1; int maxi = -1;
                    for(int j=0; j<(1<<TOTAL_DICE_COUNT); ++j)
                    {
                        double sumv = 0;
                        for(int to = 0; to < TOTAL_DICE_COMB; ++to)
                            sumv += trans[j][from][to] * dp[round-1][selected_suit][bonus][to];
                        if(maxv < sumv) maxv = sumv, maxi = j;
                    }
                    dp[round][selected_suit][bonus][from] = maxv;
                    op[round][selected_suit][bonus][from] = maxi;
                }
            }

			// choose according to correct yahtzee calculation
            for(int i=0; i<TOTAL_DICE_COMB; ++i)
                dpave[selected_suit][bonus] +=
				trans[(1<<TOTAL_DICE_COUNT)-1][0][i] *
				dp[TOTAL_DICE_ROUND][selected_suit][bonus][i];
        }
    }
    std::cerr << "Calculation Complete." << std::endl;
}