/*
 * HELPER.CC
 * This file contains basic bit-DP helper of yacht dice game.
 */

#include <algorithm>
#include <map>
#include <vector>
#include <cassert>

#include "helper.hh"

std::map<Dices, int> encode_map;
Dices decode_map[TOTAL_DICE_COMB];

int encode(Dices d)
{
    std::sort(d.begin(), d.end());
    return encode_map[d];
}

Dices decode(int v)
{
    return decode_map[v];
}

double trans[1<<TOTAL_DICE_COUNT][TOTAL_DICE_COMB][TOTAL_DICE_COMB];
int score[TOTAL_SUIT][TOTAL_DICE_COMB];

void InitEncoder()
{
    int iter = 1; for(int i=0; i<TOTAL_DICE_COUNT; ++i) iter *= DICE_NO;

    int tp = 0;
    for(int i=0; i<iter; ++i)
    {
        int dice = i; Dices d;
        for(int i=0; i<TOTAL_DICE_COUNT; ++i)
        {
            d[i] = 1 + dice % DICE_NO;
            dice /= DICE_NO;
        }
        if(!std::is_sorted(d.begin(), d.end())) continue;
        encode_map[d] = tp;
        decode_map[tp] = d;
        ++tp;
    }
    assert(tp == TOTAL_DICE_COMB);
}


void InitTransition()
{
    for(int roll = 0; roll<(1<<TOTAL_DICE_COUNT); ++roll)
    {
        std::vector<int> idx; int p6 = 1;
        for(int i=0; i<TOTAL_DICE_COUNT; ++i) if(roll&(1<<i))
        {
            idx.push_back(i);
            p6 *= 6;
        }
        for(int from = 0; from < TOTAL_DICE_COMB; ++from)
        {
            for(int i=0; i<p6; ++i)
            {
                int ci = i;
                Dices d = decode(from);
                for(int k: idx)
                {
                    d[k] = 1+ci%6;
                    ci /= 6;
                }
                std::sort(d.begin(), d.end());
                trans[roll][from][encode(d)] += 1/(double)p6;
            }
        }
    }
}

void InitScore()
{
    for(int i=0; i<TOTAL_SUIT; ++i)
        for(int j=0; j<TOTAL_DICE_COMB; ++j)
            score[i][j] = scoring[i](decode(j));
}

void init()
{
    InitEncoder();
    InitTransition();
    InitScore();
}