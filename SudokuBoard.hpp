#ifndef BOARD_HPP
#define BOARD_HPP

#include <vector>

class SudokuBoard
{
public:
    SudokuBoard();
    void initialize_board(int clues);
    int get(int r, int c) const; 
    void set(int r, int c, int num);
    void solve_game();
    bool verify_solution() const;
private:
    std::vector<int> nums;
};

#endif