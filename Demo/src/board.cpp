#include "../header/board.h"

Board::Board(const int width, const int height, const int margin, const int num_grids_v, const int num_grids_h) : width_(width), height_(height), margin_(margin), num_grids_v_(num_grids_v), num_grids_h_(num_grids_h)
{
    board_size_v_ = height_ - 2 * margin_;
    board_size_h_ = width_ - 2 * margin_;
    grid_size_v_ = board_size_v_ / num_grids_v_;
    grid_size_h_ = board_size_h_ / num_grids_h_;
    capacity_ = num_grids_h_ * num_grids_v_;
}

void Board::draw_board() const
{
    for (int i = 0; i <= this->num_grids_v_; i++)
    {
        line(margin_, margin_ + i * grid_size_v_, margin_ + board_size_h_, margin_ + i * grid_size_v_);
    }

    for (int i = 0; i <= this->num_grids_v_; i++)
    {
        line(margin_ + i * grid_size_h_, margin_, margin_ + i * grid_size_h_, margin_ + board_size_v_); // vertical line
    }
}
