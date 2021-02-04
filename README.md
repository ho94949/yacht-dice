# Yacht Dice AI

AI of [Yacht Dice](https://en.wikipedia.org/wiki/Yacht_(dice_game)).

This AI maximizes expected value of yacht. This AI Do not consider opponent, thus not maximizing winning probability.

Expected score value of Yacht dice game with optimal play is 185.317430, way more than average person playing.

## Requirement

- You should have C++-17 compatible compiler.
  - Tested with g++ 9.3.0 on ubuntu 20.04 WSL.
- This program requires 2GB of memory to save all possible state of yacht dice.

## Rules

Yacht dice game has many variations, and this game uses following rule.

- One, Two, Three, Four, Five, Six
  - For any combination, score is the sum of dice with chosen number.
  - If you score 63 or higher in these categories total, you can get additional 35 scores.
- Four Card
  - If combination includes four dice showing the same face, score is the sum of all dice.
- Full House
  - If combination is given ans two of one number and three of another, score is the sum of all dice.
- L. Straight
  - If combination is 5 consecutive numbers, score is 30.
- S. Straight
  - If combination has 4 consecutive numbers, score is 15.
- Yacht
  - If all five dices are showing same face, score is 50.

You can modify these rules in [rule.hh](https://github.com/ho94949/yacht-dice/blob/main/src/rule.hh) and [rule.cc](https://github.com/ho94949/yacht-dice/blob/main/src/rule.cc)

## Build & Execution

1. Build all `*.cc` files in `src` or use `./compile.sh`. `./main` will be produced in root directory.
2. `./main calc` produces pre-calculation files, `eval.bin` and `op.bin`. (Total 1.66GB)
   1. Calculation takes  20 minutes, 1.7GB of memory on Intel(R) Core(TM) i5-10400 CPU @ 2.90GHz.
3. `./main` loads `eval.bin` and `op.bin` if they exists.

## Usage

This program shows tabular interface of yacht dice game.
- `Input your dice (? more re-rolls)`
  - You should enter 5 space-separated integer, when dice rolled.
  - This program shows recommended dice to keep. (In most program, Click can be used to keep dices.)
  - You will see another `Input your dice` screen. You should input **all of your dices**, not only re-rolled dice.
    - This program only shows "recommendation"s and these are not forced.
- `Your choice: `
  - You can enter any integer between 1 and 12, where score can be recorded.
  - Recommended choice are shown, and you can follow them.


## Implementation

This Yacht Dice AI use bitmask dynamic programming, thus investigating all possible state of yacht dice. [calc.cc](https://github.com/ho94949/yacht-dice/blob/main/src/calc.cc) includes implementation.

## TODOs

If you want, you can create PR to this repository.

- Multi-core, GPU, or AVX support could be added.
- `dp` and `op` variable need not to be exported with careful implementation (will need little more calculation on run-time)
- Winning probability support. Supporting this naively will cost 660 times more calculation and memory. So multicore and file size reducing would be needed.

## License

Shield: [![CC BY-SA 4.0][cc-by-sa-shield]][cc-by-sa]

This work is licensed under a
[Creative Commons Attribution-ShareAlike 4.0 International License][cc-by-sa].

[![CC BY-SA 4.0][cc-by-sa-image]][cc-by-sa]


[cc-by-sa]: http://creativecommons.org/licenses/by-sa/4.0/
[cc-by-sa-image]: https://licensebuttons.net/l/by-sa/4.0/88x31.png
[cc-by-sa-shield]: https://img.shields.io/badge/License-CC%20BY--SA%204.0-lightgrey.svg