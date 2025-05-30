#pragma once
#include <vector>
#include <utility>
#include <iostream>

#include <graphics.h>
#include "../header/draw_board_strategy.h"

class Board
{
private:
    std::vector<int> data_;
    int num_pieces_;
    int capacity_;
    int num_h_;
    int num_v_;
    DrawBoardStrategy *draw_strategy_;

public:
    Board() = delete;
    Board(DrawBoardStrategy *draw_strategy, int num_h, int num_v);

    void draw_board() const;

    bool is_full() const { return capacity_ == num_pieces_; }
    int get_num() const { return this->num_pieces_; };
    int get_at(const int x, const int y) const { return data_[xy_to_index(x, y)]; }

    void clear_at(const int x, const int y);
    void set_at(const int x, const int y, const int value);

    int operator[](const int index) const { return data_[index]; }
    int &operator[](const int index) { return data_[index]; }

    void print() const;

private:
    int xy_to_index(const int x, const int y) const;
    std::pair<int, int> index_to_xy(const int index) const;
};

// public:
//     // user defined
//     int width_;
//     int height_;
//     int margin_;
//     int num_grids_v_;
//     int num_grids_h_;
//     bool weiqi_mode_;
//
//     // derived from user defined fields
//     int board_size_v_;
//     int board_size_h_;
//     int grid_size_v_;
//     int grid_size_h_;
//     int capacity_;
//
//     // data in board
//     std::vector<int> data_;
//     int num_pieces_;
//
// public:
//     Board() = delete;
//     Board(const int width, const int height, const int margin, const int num_grids_v, const int num_grids_h, const bool weiqi_mode);
//
//     void draw_board() const;
//     bool is_full() const { return capacity_ == num_pieces_; }
//     int get_num() const { return this->num_pieces_; };
//     int get_at(const int x, const int y) const { return data_[xy_to_index(x, y)]; }
//
//     void clear_at(const int x, const int y);
//     void set_at(const int x, const int y, const int value);
//
//     int operator[](const int index) const { return data_[index]; }
//
//     int &operator[](const int index) { return data_[index]; }
//
//     void print() const;
//