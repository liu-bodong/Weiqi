#include "../header/board.h"

Board::Board(const int width, const int height, const int margin, const int num_grids_v, const int num_grids_h, const bool weiqi_mode) : width_(width), height_(height), margin_(margin), num_grids_v_(num_grids_v), num_grids_h_(num_grids_h), weiqi_mode_(weiqi_mode)
{
    board_size_v_ = height_ - 2 * margin_;
    board_size_h_ = width_ - 2 * margin_;
    grid_size_v_ = board_size_v_ / num_grids_v_;
    grid_size_h_ = board_size_h_ / num_grids_h_;
    if (weiqi_mode_)
    {
        capacity_ = (num_grids_h_ + 1) * (num_grids_v_ + 1);
    }
    else
    {
        capacity_ = num_grids_h_ * num_grids_v_;
    }
    std::vector<int> vec(capacity_, 0);
    data_ = vec;
}

void Board::draw_board() const
{
    int num_lines_v = num_grids_v_;
    int num_lines_h = num_grids_h_;

    for (int i = 0; i <= num_lines_v; i++)
    {
        line(margin_, margin_ + i * grid_size_v_, margin_ + board_size_h_, margin_ + i * grid_size_v_);
    }

    for (int i = 0; i <= num_lines_h; i++)
    {
        line(margin_ + i * grid_size_h_, margin_, margin_ + i * grid_size_h_, margin_ + board_size_v_); // vertical line
    }
}

void Board::clear_at(const int x, const int y)
{
    num_pieces_--;
    data_[convert_from_xy(x, y)] = 0;
}

void Board::set_at(const int x, const int y, const int value)
{
    if (data_[convert_from_xy(x, y)] == 0)
    {
        num_pieces_++;
    }
    data_[convert_from_xy(x, y)] = value;
}
