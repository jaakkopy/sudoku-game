#include <raylib.h>
#include "SudokuBoard.hpp"
#include "Player.hpp"
#include "draw.hpp"

#define AMOUNT_CLUES 17

void resize(float &window_w, float &screen_h);
void handle_number_input(SudokuBoard &board, Player &player, float window_w, float window_h);
int handle_character_input(SudokuBoard &board, int input);

int main(void)
{
    float window_w = 800.0f;
    float window_h = 800.0f;

    SudokuBoard board;
    board.initialize_board(AMOUNT_CLUES);
    Player player;

    InitWindow(window_w, window_h, "sudoku");
    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        if (IsWindowResized())
            resize(window_w, window_h);

        handle_number_input(board, player, window_w, window_h);        

        BeginDrawing();
        ClearBackground(WHITE);

        highlight_selected_square(player.get_selected_row(), player.get_selected_col(), window_w, window_h);
        draw_board(board, window_w, window_h);

        int player_character_input = player.check_character_pressed();
        int is_ok = handle_character_input(board, player_character_input);
        if (is_ok != -1)
        {
            if (is_ok == 1)
                DrawText("Correct!", window_w / 2 - 50 * window_h / window_w, window_h / 2, 50 * window_h / window_w, GREEN);
            else
                DrawText("Wrong", window_w / 2 - 50 * window_h / window_w, window_h / 2, 50 * window_h / window_w, RED);
        }

        EndDrawing();
        if (is_ok != -1)
            WaitTime(1);
    }
    CloseWindow();
    return 0;
}

void resize(float &window_w, float &window_h)
{
    window_w = GetScreenWidth();
    window_h = GetScreenHeight();
}

void handle_number_input(SudokuBoard &board, Player &player, float window_w, float window_h)
{
    player.update_selected_position(window_w, window_h);
    int check_number = player.check_number_pressed();
    if (check_number > 0)
        board.set(player.get_selected_row(), player.get_selected_col(), check_number);
}

int handle_character_input(SudokuBoard &board, int input)
{
    int is_ok = -1;
    if (input == 's')
    {
        board.solve_game();
    }
    if (input == 'r')
    {
        board.initialize_board(AMOUNT_CLUES);
    }
    if (input == 'v')
    {
        is_ok = board.verify_solution();
    }
    
    return is_ok;
}
