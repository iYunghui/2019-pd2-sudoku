#ifndef SUDOKU_H
#define SUDOKU_H
using namespace std;

class Sudoku {
  public:
    Sudoku();

    void setSudoku();
    void printSudoku();
    void print_ansSudoku();
    int getans();
    void check();

    // generate
    void initial();
    int generate(int row, int col);
    void digSudoku();

    // transform
    void swapNum(int x, int y);
    void swapRow(int x, int y);
    void swapCol(int x, int y);
    void rotate(int x);
    void flip(int x);

    // solve
    void solve(int row, int col);

  private:
    int i, j, ans;
    int sudoku[9][9], ansSudoku[9][9];
    int rownum[9][9], colnum[9][9], block[9][9];
};

#endif // SUDOKU_H
