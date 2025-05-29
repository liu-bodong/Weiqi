#include <graphics.h>
#include <vector>
#include <iostream>

class Board
{
private:
    // user defined
    int width_;
    int height_;
    int margin_;
    int num_grids_v_;
    int num_grids_h_;

    // derived from user defined fields
    int board_size_v_;
    int board_size_h_;
    int grid_size_v_;
    int grid_size_h_;
    int capacity_;

    // data in board
    std::vector<int> data_;
    int num_pieces_;

public:
    Board() = delete;
    Board(const int width, const int height, const int margin, const int num_grids_v, const int num_grids_h);

    void draw_board() const;
    bool is_full() const { return capacity_ == num_pieces_; }
    int get_num() const { return this -> num_pieces_; };
    int get_at(const int x, const int y) const { return data_[convert_from_xy(x, y)]; }

    int operator[](const int index) const { return data_[index]; }

    int &operator[](const int index) { return data_[index]; }

private:
    int convert_from_xy(const int x, const int y) const { return (x - 1) * num_grids_h_ + y - 1; }
};