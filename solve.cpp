#include <iostream>
#include "sudoku.h"
using namespace std;

int main() {
    Sudoku sudoku;
    int ans;

    sudoku.setSudoku();
    sudoku.check();
    sudoku.solve(0, 0);
    ans = sudoku.getans();

    if(ans != 1)
        cout << ans << endl;
    else {
        cout << "1" << endl;
        sudoku.print_ansSudoku();
    }

    return 0;
}
