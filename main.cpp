#include <raylib.h>
#include "SudokuBoard.hpp"
#include "Player.hpp"
#include "draw.hpp"

void resize(float &window_w, float &screen_h);

int main(void)
{
    float window_w = 700.0f;
    float window_h = 800.0f;
    
    SudokuBoard board;
    board.initialize_board(17);
    Player player;

    InitWindow(window_w, window_h, "sudoku");
    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        if (IsWindowResized())
            resize(window_w, window_h);
        player.update_selected_position(window_w, window_h);
        BeginDrawing();
        highlight_selected_square(player.get_selected_row(), player.get_selected_col(), window_w, window_h);
        draw_board(board, window_w, window_h);
        ClearBackground(WHITE);
        EndDrawing();
    }
    CloseWindow();
    return 0;
}

void resize(float &window_w, float &window_h)
{
    window_w = GetScreenWidth();
    window_h = GetScreenHeight();
}