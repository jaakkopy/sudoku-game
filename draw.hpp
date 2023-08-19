#ifndef DRAW_HPP
#define DRAW_HPP

#include "SudokuBoard.hpp"

void draw_board(const SudokuBoard &board, float window_width, float window_height);
void highlight_selected_square(int selected_row, int selected_col, float window_width, float window_height);

#endif