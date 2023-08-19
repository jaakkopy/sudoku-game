#include <raylib.h>
#include "SudokuBoard.hpp"
#include "Player.hpp"
#include "draw.hpp"

void resize(float &window_w, float &screen_h);
#include <iostream>
int main(void)
{
    float window_w = 700.0f;
    float window_h = 800.0f;
    
    SudokuBoard board;
    int clues = 17;
    board.initialize_board(clues);
    Player player;

    InitWindow(window_w, window_h, "sudoku");
    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        if (IsWindowResized())
            resize(window_w, window_h);
        
        player.update_selected_position(window_w, window_h);
        int check_number = player.check_number_pressed();
        if (check_number > 0)
            board.set(player.get_selected_row(), player.get_selected_col(), check_number);
        
        int is_ok = -1;
        switch (player.check_character_pressed())
        {
        case 's':
            board.solve_game(0);
            break;
        case 'r':
            board.initialize_board(clues);
            break;
        case 'v':
            is_ok = board.verify_solution();
            break;
        }
        if (is_ok != -1)
        {
            std::cout << is_ok << std::endl;
        }

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