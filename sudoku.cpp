/**
 * @file sudoku.cpp
 * @author Ryan Sordillo
 * @brief Given a unfinished sudoku puzzle, this program recursively solves the puzzle
 * @date 4/22/2024
 */
#include <iostream>
#include <vector>

using namespace std;

const int ROWS = 9;
const int COLS = 9;

class Sudoku {
private:
    vector<vector<int>> board;
public:
    void write_board();
    void read_board();
    bool check_row(int row, int num);
    bool check_col(int col, int num);
    bool check_block(int row, int col, int num);
    bool is_valid(int row, int col, int num);
    bool solve();
    bool find_empty_cell(int & row, int & col);
};

/**
* Reads in the given board from standard input and stores it in 2d vector with 0 for empty spaces
*/
void Sudoku::read_board() {
    for (int r = 0; r < ROWS; r++) {
        vector<int> row;
        string line;
        getline(cin, line); // Read entire line
        for (int c = 0; c < COLS; c++) {
            if (line[c] == ' ') 
                row.push_back(0);
            else
                //adjusts the ASCII value
                row.push_back(line[c] - '0');
        }
        board.push_back(row);
    }
}

/**
* Prints out the board
*/
void Sudoku::write_board() {
    for (int r = 0; r < ROWS; r++) {
        for (int c = 0; c < COLS; c++) 
            cout << board[r][c];
        cout << endl;
    }
}

/**
* @param row row we are checking
* @param num number we are checking the row with 
* @return true if the row does not contain the number, false otherwise.
*/
bool Sudoku::check_row(int row, int num) {
    for (int col = 0; col < COLS; col++) {
        if (board[row][col] == num) 
            return false;
    }
    return true;
}

/**
* @param col column we are checking
* @param num number we are checking the row with 
* @return true if the column does not contain the number, false otherwise.
*/
bool Sudoku::check_col(int col, int num) {
    for (int row = 0; row < ROWS; row++) {
        if (board[row][col] == num) 
            return false;
    }
    return true;
}

/**
* @param start_row The starting row index of the 3x3 block.
* @param start_col The starting column index of the 3x3 block.
* @param num The number to check the block with. 
* @return true if the block does not contain the number, false otherwise
*/
bool Sudoku::check_block(int start_row, int start_col, int num) {
    for (int row = 0; row < 3; row++) {
        for (int col = 0; col < 3; col++) {
            if (board[start_row + row][start_col + col] == num) 
                return false;
        }
    }
    return true;
}

/**
* @param row The row index of the cell
* @param col The column index of the cell
* @param num The number to check the each the column, row and block with. 
* @return true if placing the number in the cell is valid, false otherwise
*/
bool Sudoku::is_valid(int row, int col, int num) {
    int block_start_row = row - row % 3;
    int block_start_col = col - col % 3;
    return check_row(row, num) && check_col(col, num) && \
                                check_block(block_start_row, block_start_col, num);
}

/**
* @param row Reference to store the row index of the empty cell
* @param col Reference to store the column index of the empty cell
* @return true if found an empty cell
*/
bool Sudoku::find_empty_cell(int & row, int & col) {
    for (row = 0; row < ROWS; row++) {
        for (col = 0; col < COLS; col++) {
            if (board[row][col] == 0) 
                return true;
        }
    }
    return false;
}

/**
* @return true if puzzle is solved, false otherwise
*/
bool Sudoku::solve() {
    int row, col;
    // If no empty cell found, puzzle is solved
    if (!find_empty_cell(row, col))
        return true;
    for (int num = 1; num <= 9; num++) {
        if (is_valid(row, col, num)) {
            board[row][col] = num;
            // Recursively solve the puzzle
            if (solve()) 
                return true;
            board[row][col] = 0; //backtrack
        }
    }
    return false;
}

// Do not modify code below this line
int main() {
    Sudoku sudoku;
    sudoku.read_board();
    sudoku.solve();
    sudoku.write_board();
}
