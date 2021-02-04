/*
 * CALC.CC
 * This file contains calculations of yacht dice game.
 */

#include "calc.hh"

#include <algorithm>
#include <iostream>
#include <cstdlib>

double dpave[1<<TOTAL_SUIT][BONUS_LIMIT+1];
double dp[TOTAL_DICE_ROUND+1][1<<TOTAL_SUIT][BONUS_LIMIT+1][TOTAL_DICE_COMB];
int8_t op[TOTAL_DICE_ROUND+1][1<<TOTAL_SUIT][BONUS_LIMIT+1][TOTAL_DICE_COMB];

void save()
{
    FILE *fp = fopen("eval.bin", "wb");
    if(!fp) std::cerr << "Cannot open eval.bin to write." << std::endl, exit(EXIT_FAILURE);

    if(sizeof(dp)/sizeof(double) !=
        fwrite(dp, sizeof(double), sizeof(dp)/sizeof(double), fp))
            std::cerr << "Cannot write to eval.bin" << std::endl, exit(EXIT_FAILURE);
    if(sizeof(dpave)/sizeof(double) !=
        fwrite(dpave, sizeof(double), sizeof(dpave)/sizeof(double), fp))
            std::cerr << "Cannot write to eval.bin" << std::endl, exit(EXIT_FAILURE);
    fclose(fp);

    fp = fopen("op.bin", "wb");
    if(!fp) std::cerr << "Cannot open op.bin to write." << std::endl, exit(EXIT_FAILURE);

    if(sizeof(op)/sizeof(int8_t) !=
        fwrite(op, sizeof(int8_t), sizeof(op)/sizeof(int8_t), fp))
            std::cerr << "Cannot write to op.bin" << std::endl, exit(EXIT_FAILURE);
    fclose(fp);
}

void load(char* prog)
{
    FILE *fp = fopen("eval.bin", "rb");
    if(!fp) std::cerr << "eval.bin not found. use '" << prog << " calc' to calculate." << std::endl, exit(EXIT_FAILURE);

    if(sizeof(dp)/sizeof(double) !=
        fread(dp, sizeof(double), sizeof(dp)/sizeof(double), fp))
            std::cerr << "Corrupted eval.bin" << std::endl, exit(EXIT_FAILURE);
    if(sizeof(dpave)/sizeof(double) !=
        fread(dpave, sizeof(double), sizeof(dpave)/sizeof(double), fp))
            std::cerr << "Corrupted eval.bin" << std::endl, exit(EXIT_FAILURE);
    fclose(fp);

    fp = fopen("op.bin", "rb");
    if(!fp) std::cerr << "op.bin not found. use '" << prog << " calc' to calculate." << std::endl, exit(EXIT_FAILURE);

    if(sizeof(op)/sizeof(int8_t) !=
        fread(op, sizeof(int8_t), sizeof(op)/sizeof(int8_t), fp))
            std::cerr << "Corrupted op.bin" << std::endl, exit(EXIT_FAILURE);
    fclose(fp);
}

void calc()
{
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