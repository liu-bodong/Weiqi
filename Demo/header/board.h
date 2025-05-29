#pragma once
#include <graphics.h>
#include <vector>
#include <iostream>

class Board
{
public:
    // user defined
    int width_;
    int height_;
    int margin_;
    int num_grids_v_;
    int num_grids_h_;
    bool weiqi_mode_;

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
    Board(const int width, const int height, const int margin, const int num_grids_v, const int num_grids_h, const bool weiqi_mode);

    void draw_board() const;
    bool is_full() const { return capacity_ == num_pieces_; }
    int get_num() const { return this->num_pieces_; };
    int get_at(const int x, const int y) const { return data_[convert_from_xy(x, y)]; }

    void clear_at(const int x, const int y);
    void set_at(const int x, const int y, const int value);

    int operator[](const int index) const { return data_[index]; }

    int& operator[](const int index) { return data_[index]; }

public:
    int convert_from_xy(const int x, const int y) const;
};