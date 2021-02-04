#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

#include "rule.hh"
#include "helper.hh"
#include "calc.hh"
#include "print.hh"

int main(int argc, char **argv)
{
    init();
    std::cout << "Init OK!" << std::endl;

    if(argc == 2 && std::string(argv[1]) == "calc")
    {
        calc();
        save();
        return 0;
    }
    else load(argv[0]), std::cout << "Load OK!" << std::endl;

    std::vector<int> score(12);
    int curval = 0, bonus = 0;

    for(int i=0; i<12; ++i)
    {
        Dices d;
        print(curval, score);

        for(int j=TOTAL_DICE_ROUND; j>0; --j)
        {
            printf("Input your dice (%d more re-rolls): ", j);

            for(int k=0; k<TOTAL_DICE_COUNT; ++k) std::cin >> d[k];
            std::sort(d.begin(), d.end());
            int TODO = op[j][curval][std::min(bonus, BONUS_LIMIT)][encode(d)];

            printf("Recommended dice to keep (%d):", TOTAL_DICE_COUNT - __builtin_popcount(TODO));
            for(int k=0; k<TOTAL_DICE_COUNT; ++k)
                if(!(TODO&(1<<k))) printf("%d ", d[k]);
            puts("");
        }

        printf("Input your dice (final): ");

        for(int k=0; k<TOTAL_DICE_COUNT; ++k) std::cin >> d[k];
        int TODO = op[0][curval][std::min(bonus, BONUS_LIMIT)][encode(d)];

        printf("Recommended choice: %s\n", names[TODO].c_str());

        int choice = 0;
        printf("Your choice: "); std::cin >> choice; --choice;

        score[choice] = ::score[choice][encode(d)];
        curval |= 1<<choice;
        if(choice < BONUS_SUIT) bonus += score[choice];
    }

    print(curval, score);
    return 0;
}