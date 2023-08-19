#ifndef BOARD_HPP
#define BOARD_HPP

#include <tuple>
#include <set>
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
    bool is_clue_square(int r, int c) const;
private:
    bool solve(int i);
    std::set<std::tuple<int, int>> clue_positions; // unmodifiable squares
    std::vector<int> nums;
};

#endif