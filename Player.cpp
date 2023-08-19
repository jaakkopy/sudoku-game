#include <raylib.h>
#include <iostream>
#include "Player.hpp"

void Player::update_selected_position(float window_w, float window_h)
{
    Vector2 mpos = GetMousePosition();
    selected_row = (int)mpos.y / (window_h / 9);
    selected_col = (int)mpos.x / (window_w / 9);
}

int Player::get_selected_row()
{
    return selected_row;
}

int Player::get_selected_col()
{
    return selected_col;
}

int Player::check_number_pressed()
{
    int key1 = KEY_KP_1;
    int key9 = KEY_KP_9;
    for (int k = key1; k <= key9; ++k)
    {
        if (IsKeyPressed(k))
            return k - KEY_KP_0;
    }
    return 0;
}
