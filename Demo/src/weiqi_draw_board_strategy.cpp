#include "../header/weiqi_draw_board_strategy.h"

void WeiqiDrawBoardStrategy::draw() const
{
    setlinecolor(BLACK);
    int offset = get_grid_size_h() / 2;
    for (int i = 0; i < num_lines_v_; i++)
    {
        line(margin_ + offset,
             margin_ + i * get_grid_size_v() + offset,
             margin_ + get_board_size_h() - offset,
             margin_ + i * get_grid_size_v() + offset);
    }
    for (int j = 0; j < num_lines_h_; j++)
    {
        line(margin_ + j * get_grid_size_h() + offset,
             margin_ + offset,
             margin_ + j * get_grid_size_h() + offset,
             margin_ + get_board_size_v() - offset);
    }
    // star positions
    setfillcolor(BLACK);
    solidcircle(margin_ + offset + 3 * grid_size_h_, margin_ + offset + 3 * grid_size_v_, 4);
    solidcircle(margin_ + offset + 9 * grid_size_h_, margin_ + offset + 3 * grid_size_v_, 4);
    solidcircle(margin_ + offset + 15 * grid_size_h_, margin_ + offset + 3 * grid_size_v_, 4);
    solidcircle(margin_ + offset + 3 * grid_size_h_, margin_ + offset + 9 * grid_size_v_, 4);
    solidcircle(margin_ + offset + 9 * grid_size_h_, margin_ + offset + 9 * grid_size_v_, 4);
    solidcircle(margin_ + offset + 15 * grid_size_h_, margin_ + offset + 9 * grid_size_v_, 4);
    solidcircle(margin_ + offset + 3 * grid_size_h_, margin_ + offset + 15 * grid_size_v_, 4);
    solidcircle(margin_ + offset + 9 * grid_size_h_, margin_ + offset + 15 * grid_size_v_, 4);
    solidcircle(margin_ + offset + 15 * grid_size_h_, margin_ + offset + 15 * grid_size_v_, 4);
}