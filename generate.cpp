#include <iostream>
#include "sudoku.h"
using namespace std;

int main() {
    Sudoku sudoku;

    sudoku.initial();
    sudoku.check();
    sudoku.generate(1, 0);
    sudoku.digSudoku();
    sudoku.printSudoku();

    return 0;
}
