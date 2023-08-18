#include <tuple>
#include <set>
#include <time.h>
#include <random>
#include <algorithm>
#include "SudokuBoard.hpp"

SudokuBoard::SudokuBoard()
{
    nums = std::vector<int>(81, 0);
}

void SudokuBoard::initialize_board(int clues)
{
    std::fill(nums.begin(), nums.end(), 0);
    // Fill out the first row with randomly ordered numbers from 1 to 9. Without random clues the solving algorithm would always create the same solution
    std::vector<int> first_row = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    std::random_shuffle(first_row.begin(), first_row.end());
    for (int i = 0; i < 9; ++i)
    {
        this->set(0, i, first_row.at(i));
    }
    solve_game();
    srand(time(NULL));
    int remove_amout = 81 - clues;
    remove_amout = remove_amout > 0 ? remove_amout : 0;
    std::set<std::tuple<int, int>> already_removed;
    while (remove_amout)
    {
        int random_r = random() % 9;
        int random_c = random() % 9;
        std::tuple<int, int> random_slot = {random_r, random_c};
        if (already_removed.find(random_slot) != already_removed.end())
        {
            this->set(random_r, random_c, 0);
            already_removed.insert(random_slot);
            --remove_amout;
        }
    }
}

int SudokuBoard::get(int r, int c) const
{
    return this->nums.at(r * 9 + c);
}

void SudokuBoard::set(int r, int c, int num)
{
    this->nums.at(r * 9 + c) = num;
}

void SudokuBoard::solve_game()
{
}

bool SudokuBoard::verify_solution() const
{
    std::vector<unsigned int> row_checks(9, 0);
    std::vector<unsigned int> col_checks(9, 0);
    std::vector<unsigned int> block_checks(9, 0);
    for (int r = 0; r < 9; ++r)
    {
        for (int c = 0; c < 9; ++c)
        {
            row_checks.at(r) |= (1 << this->get(r, c));
            col_checks.at(c) |= (1 << this->get(r, c));
            block_checks.at((r / 3) * 3 + c / 3) |= (1 << this->get(r, c));
        }
    }
    unsigned int should_be = 0b1111111110; // 1 to 9 check
    for (int i = 0; i < 9; ++i)
    {
        if (row_checks.at(i) != should_be || col_checks.at(i) != should_be || block_checks.at(i) != should_be)
            return false;
    }
    return true;
}