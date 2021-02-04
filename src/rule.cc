/*
 * RULE.CC
 * This file contains basic rules of yacht dice game.
 */

#include <algorithm>

#include "rule.hh"

int Sum(Dices d) {
    int s = 0;
    for(auto v: d) s += v;
    return s;
}

int Ones(Dices d) { return 1 * std::count(d.begin(), d.end(), 1); }
int Twos(Dices d) { return 2 * std::count(d.begin(), d.end(), 2); }
int Threes(Dices d) { return 3 * std::count(d.begin(), d.end(), 3); }
int Fours(Dices d) { return 4 * std::count(d.begin(), d.end(), 4); }
int Fives(Dices d) { return 5 * std::count(d.begin(), d.end(), 5); }
int Sixes(Dices d) { return 6 * std::count(d.begin(), d.end(), 6); }

int Choice(Dices d) { return Sum(d); }

int FourCards(Dices d) {
    std::sort(d.begin(), d.end());
    if(d[0] == d[3] || d[1] == d[4]) return Sum(d);
    else return 0;
}

int FullHouse(Dices d)
{
    std::sort(d.begin(), d.end());
    if( (d[0] == d[1] && d[2] == d[4]) ||
        (d[0] == d[2] && d[3] == d[4]) ) return Sum(d);
    else return 0;
}

int LStraight(Dices d)
{
    std::sort(d.begin(), d.end());
    if( d[0] + 1 == d[1] &&
        d[1] + 1 == d[2] &&
        d[2] + 1 == d[3] &&
        d[3] + 1 == d[4] ) return 30;
    else return 0;
}

int SStraight(Dices d)
{
    bool a[DICE_NO+1];
    for(int i=1; i<=DICE_NO; ++i) a[i] = std::find(d.begin(), d.end(), i) != d.end();
    if( (a[1] && a[2] && a[3] && a[4]) ||
        (a[2] && a[3] && a[4] && a[5]) ||
        (a[3] && a[4] && a[5] && a[6]) ) return 15;
    else return 0;
}

int Yacht(Dices d)
{
    for(int v: d) if(v == d[0]) return 0;
    return 50;
}

std::function<int(Dices)> scoring[TOTAL_SUIT] = {
	Ones, Twos, Threes, Fours, Fives, Sixes, Choice, FourCards, FullHouse, LStraight, SStraight, Yacht
};