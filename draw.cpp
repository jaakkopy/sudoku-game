#include <raylib.h>
#include <string>
#include "draw.hpp"

void draw_grid(const float window_width, const float window_height)
{
    Vector2 horizontal_start = {0, 0};
    Vector2 horizontal_end = {window_width, 0};
    Vector2 vertical_start = {0, 0};
    Vector2 vertical_end = {0, window_height};

    const float horizontal_step = window_height / 3;
    const float horizontal_inner_step = horizontal_step / 3;
    const float vertical_step = window_width / 3;
    const float vertical_inner_step = vertical_step / 3;

    for (float outer_box = 0; outer_box <= window_height; outer_box += horizontal_step)
    {
        horizontal_start.y = outer_box;
        horizontal_end.y = outer_box;
        DrawLineV(horizontal_start, horizontal_end, BLACK);
        for (float inner_box = outer_box + horizontal_inner_step; inner_box < outer_box + horizontal_step; inner_box += horizontal_inner_step)
        {
            horizontal_start.y = inner_box;
            horizontal_end.y = inner_box;
            DrawLineV(horizontal_start, horizontal_end, LIGHTGRAY);
        }
    }
    for (float outer_box = 0; outer_box <= window_width; outer_box += vertical_step)
    {
        vertical_start.x = outer_box;
        vertical_end.x = outer_box;
        DrawLineV(vertical_start, vertical_end, BLACK);
        for (float inner_box = outer_box + vertical_inner_step; inner_box < outer_box + vertical_step; inner_box += vertical_inner_step)
        {
            vertical_start.x = inner_box;
            vertical_end.x = inner_box;
            DrawLineV(vertical_start, vertical_end, LIGHTGRAY);
        }
    }
}

void draw_board(const SudokuBoard &board, float window_width, float window_height)
{
    draw_grid(window_width, window_height);
    int blocks_horizontal = window_width / 9;
    int blocks_vertical = window_height / 9;
    float font_size = blocks_vertical / blocks_horizontal;
    for (int r = 0; r < 9; ++r)
    {
        for (int c = 0; c < 9; ++c)
        {
            int num = board.get(r, c);
            if (num != 0)
            {
                Color color = BLACK;
                if (board.is_clue_square(r, c))
                    color = GRAY;
                DrawText(TextFormat("%i", num), blocks_horizontal * ((float)c + 0.5), blocks_vertical * ((float)r + 0.5), font_size, color);
            }
        }
    }
}

void highlight_selected_square(int selected_row, int selected_col, float window_width, float window_height)
{
    DrawRectangle(selected_col * window_width / 9, selected_row * window_height / 9, window_width / 9, window_height / 9, GREEN);
}
