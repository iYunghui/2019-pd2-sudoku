#include "sudoku.h"
#include <iostream>
#include <ctime>
#include <algorithm>
using namespace std;

Sudoku::Sudoku() {
    ans = 0;
    for(i=0; i<9; i++)
        for(j=0; j<9; j++) {
            ansSudoku[i][j] = 0;
            sudoku[i][j] = 0;
            rownum[i][j] = 0;
            colnum[i][j] = 0;
            block[i][j] = 0;
        }
}

void Sudoku::setSudoku() {
    for(i=0; i<9; i++)
        for(j=0; j<9; j++)
            cin >> sudoku[i][j];
}
void Sudoku::printSudoku() {
    for(i=0; i<9; i++) {
        for(j=0; j<8; j++)
            cout << sudoku[i][j] << " ";
        cout << sudoku[i][8] << endl;
    }
}
void Sudoku::print_ansSudoku() {
    for(i=0; i<9; i++) {
        for(j=0; j<8; j++)
            cout << ansSudoku[i][j] << " ";
        cout << ansSudoku[i][8] << endl;
    }
}
int Sudoku::getans() {
    return ans;
}
void Sudoku::check() {
    for(i=0; i<9; i++)
        for(j=0; j<9; j++) {
            if(sudoku[i][j]) {
                rownum[i][sudoku[i][j]-1] = 1;
                colnum[sudoku[i][j]-1][j] = 1;
                block[(i/3)*3+(j/3)][sudoku[i][j]-1] = 1;
            }
        }
}

// generate
void Sudoku::initial() {
    srand( time(NULL) );
    for(i=0; i<9; i++)
        sudoku[0][i] = i+1;
    random_shuffle(&sudoku[0][0], &sudoku[0][8]);
}
int Sudoku::generate(int row, int col) {
    int num;

    for(num=0; num<9; num++) {
        if(!rownum[row][num] && !colnum[num][col] && !block[(row/3)*3+(col/3)][num]) {
            sudoku[row][col] = num+1;
            rownum[row][num] = 1;
            colnum[num][col] = 1;
            block[(row/3)*3+(col/3)][num] = 1;

            if(col < 8) {
                if(generate(row, col+1))
                    return 1;
            } else if(row < 8) {
                if(generate(row+1, 0))
                    return 1;
            } else
                return 1;

            sudoku[row][col] = 0;
            rownum[row][num] = 0;
            colnum[num][col] = 0;
            block[(row/3)*3+(col/3)][num] = 0;
        }
    }
    return 0;
}
void Sudoku::digSudoku() {
    int num;
    srand( time(NULL) );
    num = rand()%14+51;
    while(num) {
        i = rand()%9;
        j = rand()%9;

        if(sudoku[i][j] == 0)
            continue;
        else
            sudoku[i][j] = 0;

        num--;
    }
}

// transform
void Sudoku::swapNum(int x, int y) {
    for(i=0; i<9; i++)
        for(j=0; j<9; j++) {
            if(sudoku[i][j] == x) sudoku[i][j] = y;
            else if(sudoku[i][j] == y) sudoku[i][j] = x;
        }
}
void Sudoku::swapRow(int x, int y) {
    int temp = 0;

    for(i=0; i<3; i++)
        for(j=0; j<9; j++) {
            temp = sudoku[x*3+i][j];
            sudoku[x*3+i][j] = sudoku[y*3+i][j];
            sudoku[y*3+i][j] = temp;
        }
}
void Sudoku::swapCol(int x, int y) {
    int temp = 0;

    for(i=0; i<3; i++)
        for(j=0; j<9; j++) {
            temp = sudoku[j][x*3+i];
            sudoku[j][x*3+i] = sudoku[j][y*3+i];
            sudoku[j][y*3+i] = temp;
        }
}
void Sudoku::rotate(int x) {
    int num = 8;
    int temp[9][9];
    x %= 4;

    for(i=0; i<9; i++)
        for(j=0; j<9; j++)
            temp[i][j] = 0;

    while(x!=0) {
        num = 8;
        for(i=0; i<9; i++) {
            for(j=0; j<9; j++)
                temp[j][num] = sudoku[i][j];
            num--;
        }

        for(i=0; i<9; i++)
            for(j=0; j<9; j++)
                sudoku[i][j] = temp[i][j];

        x--;
    }
}
void Sudoku::flip(int x) {
    int temp = 0;

    if(x == 1) {
        for(i=0; i<4; i++)
            for(j=0; j<9; j++) {
                temp = sudoku[j][i];
                sudoku[j][i] = sudoku[j][8-i];
                sudoku[j][8-i] = temp;
            }
    } else {
        for(i=0; i<4; i++)
            for(j=0; j<9; j++) {
                temp = sudoku[i][j];
                sudoku[i][j] = sudoku[8-i][j];
                sudoku[8-i][j] = temp;
            }
    }
}

// solve
void Sudoku::solve(int row, int col) {
    int num;

    if(ans>1)
        return;

    if(row > 8) {
        ans++;
        for(i=0; i<9; i++)
            for(j=0; j<9; j++)
                ansSudoku[i][j] = sudoku[i][j];
        return;
    }

    if(sudoku[row][col] != 0) {
        if(col < 8)
            solve(row, col+1);
        else
            solve(row+1, 0);
    } else {
        for(num=0; num<9; num++) {
            if(!rownum[row][num] && !colnum[num][col] && !block[(row/3)*3+(col/3)][num]) {
                sudoku[row][col] = num+1;
                rownum[row][num] = 1;
                colnum[num][col] = 1;
                block[(row/3)*3+(col/3)][num] = 1;

                if(col < 8)
                    solve(row, col+1);
                else
                    solve(row+1, 0);

                sudoku[row][col] = 0;
                rownum[row][num] = 0;
                colnum[num][col] = 0;
                block[(row/3)*3+(col/3)][num] = 0;
            }
        }
    }
}
