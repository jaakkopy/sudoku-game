#include <time.h>
#include <random>
#include <algorithm>
#include "SudokuBoard.hpp"

SudokuBoard::SudokuBoard()
{
    nums = std::vector<int>(82, 0);
}

void SudokuBoard::initialize_board(int clues)
{
    std::fill(nums.begin(), nums.end(), 0);
    clue_positions.clear();
    // Fill out the first row with randomly ordered numbers from 1 to 9 to randomize the outcome of the solving algorithm
    std::vector<int> first_row = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    std::random_shuffle(first_row.begin(), first_row.end());
    for (int i = 0; i < 9; ++i)
    {
        this->set(0, i, first_row.at(i));
    }
    solve_game(0);
    srand(time(NULL));
    int remove_amout = 81 - clues;
    remove_amout = remove_amout > 0 ? remove_amout : 0;
    std::set<std::tuple<int, int>> already_removed;
    while (remove_amout)
    {
        int random_r = random() % 9;
        int random_c = random() % 9;
        std::tuple<int, int> random_slot = {random_r, random_c};
        if (already_removed.find(random_slot) == already_removed.end())
        {
            this->set(random_r, random_c, 0);
            already_removed.insert(random_slot);
            --remove_amout;
        }
    }
    for (int i = 0; i < 81; ++i)
    {
        if (nums.at(i) != 0)
            clue_positions.insert(std::tuple<int, int>(i/9, i%9));
    }
}

int SudokuBoard::get(int r, int c) const
{
    return this->nums.at(r * 9 + c);
}

void SudokuBoard::set(int r, int c, int num)
{
    if (clue_positions.find(std::tuple<int, int>(r, c)) == clue_positions.end())
        this->nums.at(r * 9 + c) = num;
}

bool SudokuBoard::solve_game(int i)
{
    // bitmap for the numbers 1-9
    unsigned all_found = 0b1111111110; 
    while (nums.at(i)) 
        i++;
    if (i == 81)
        return true;
    int col = i % 9;
    int row_first = i - col;
    int block_first = ( (i/3) % 3 ) * 3 + (i/27) * 27;
    // check off the numbers found in the row, column, and block
    for (int j = 0; j < 9; ++j)
    {
        //                     row                                 column                             block
        all_found &= ~( (1u << nums.at(row_first + j)) | (1u << nums.at( (i + j * 9) % 81)) | (1u << nums.at(block_first + (j % 3) + 9 * (j/3))));
    }
    for (int j = 1; j <= 9; j++)
    {
        // if number j is not used, try to place it here
        if (all_found & (1u << j))
        {
            nums.at(i) = j; 
            if(solve_game(i+1))
                // reached the end with this combination; return true
                return true;  
        }
    }
    // All of the numbers were used or none of the combinations led to success. Mark the spot as 0 and backtrack
    nums.at(i) = 0;
    return false; 
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
            if (nums.at(r * 9 + c) == 0)
                return false; // the board is not completed yet
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

bool SudokuBoard::is_clue_square(int r, int c) const
{
    return clue_positions.find(std::tuple<int, int>(r, c)) != clue_positions.end();
}
