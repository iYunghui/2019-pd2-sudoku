#include <iostream>
#include "sudoku.h"
using namespace std;

int main() {
    Sudoku sudoku;
    int num=1, x=0, y=0;

    sudoku.setSudoku();
    while(num) {
        cin >> num;

        switch(num) {
        case 1:
            cin >> x >> y;
            sudoku.swapNum(x,y);
            break;
        case 2:
            cin >> x >> y;
            sudoku.swapRow(x,y);
            break;
        case 3:
            cin >> x >> y;
            sudoku.swapCol(x,y);
            break;
        case 4:
            cin >> x;
            sudoku.rotate(x);
            break;
        case 5:
            cin >> x;
            sudoku.flip(x);
            break;
        default:
            break;
        }
    }

    sudoku.printSudoku();

    return 0;
}
