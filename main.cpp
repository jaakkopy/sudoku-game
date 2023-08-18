#include <raylib.h>
#include "SudokuBoard.hpp"
#include "draw.hpp"

void resize(float &screen_w, float &screen_h);

int main(void)
{
    float screen_w = 700.0f;
    float screen_h = 800.0f;
    
    SudokuBoard board;

    InitWindow(screen_w, screen_h, "sudoku");
    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        if (IsWindowResized())
            resize(screen_w, screen_h);

        BeginDrawing();
        draw_board(board, screen_w, screen_h);
        ClearBackground(WHITE);
        EndDrawing();
    }
    CloseWindow();
    return 0;
}

void resize(float &screen_w, float &screen_h)
{
    screen_w = GetScreenWidth();
    screen_h = GetScreenHeight();
}