#pragma once

class DrawBoardStrategy
{
public:
    int width_;
    int height_;
    int margin_;
    int num_lines_v_;
    int num_lines_h_;

    int board_size_v_;
    int board_size_h_;
    int grid_size_v_;
    int grid_size_h_;

public:
    DrawBoardStrategy() = delete;
    DrawBoardStrategy(int width, int height, int margin, int num_lines_v, int num_lines_h)
        : width_(width), height_(height), margin_(margin), num_lines_v_(num_lines_v), num_lines_h_(num_lines_h)
    {
        board_size_v_ = height - 2 * margin;
        board_size_h_ = width - 2 * margin;
        grid_size_v_ = board_size_v_ / num_lines_v_;
        grid_size_h_ = board_size_h_ / num_lines_h_;
    }
    virtual ~DrawBoardStrategy() = default;

    virtual void draw() const = 0;

    int get_board_size_v() const { return board_size_v_; }
    int get_board_size_h() const { return board_size_h_; }
    int get_grid_size_v() const { return grid_size_v_; }
    int get_grid_size_h() const { return grid_size_h_; }
};
