#include <raylib.h>
#include <iostream>
#include "Player.hpp"

void Player::update_selected_position(float window_w, float window_h)
{
    Vector2 mpos = GetMousePosition();
    selected_row = (int)mpos.y / (window_h / 9);
    selected_col = (int)mpos.x / (window_w / 9);
    std::cout << selected_row << " " << selected_col << std::endl;
}

int Player::get_selected_row()
{
    return selected_row;
}

int Player::get_selected_col()
{
    return selected_col;
}
