#include "../header/board.h"

Board::Board(DrawBoardStrategy *draw_strategy, int num_h, int num_v)
    : draw_strategy_(draw_strategy), num_h_(num_h), num_v_(num_v)
{
    capacity_ = num_h_ * num_v_;
    num_pieces_ = 0;
    data_ = std::vector<int>(capacity_, 0);
}

void Board::draw_board() const
{
    draw_strategy_->draw();
}

void Board::clear_at(const int x, const int y)
{
    num_pieces_--;
    data_[xy_to_index(x, y)] = 0;
}

void Board::set_at(const int x, const int y, const int value)
{
    if (data_[xy_to_index(x, y)] == 0)
    {
        num_pieces_++;
    }
    data_[xy_to_index(x, y)] = value;
}

int Board::xy_to_index(const int x, const int y) const
{
    return y * num_h_ + x;
}

std::pair<int, int> Board::index_to_xy(const int index) const
{
    return {index % num_h_, index / num_h_};
}

void Board::print() const
{
    for (int i = 0; i < num_v_; i++)
    {
        std::cout << data_[i] << " ";
        if ((i + 1) % num_h_ == 0)
        {
            std::cout << std::endl;
        }
    }
}
