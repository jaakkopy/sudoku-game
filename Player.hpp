#ifndef PLAYER_HPP
#define PLAYER_HPP

class Player
{
public:
    void update_selected_position(float window_w, float window_h);
    int get_selected_row();
    int get_selected_col();
    int check_number_pressed();
    int check_character_pressed();
private:
    int selected_row, selected_col;
};

#endif