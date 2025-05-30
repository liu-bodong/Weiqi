#pragma once

#include <graphics.h>
#include "draw_board_strategy.h"

class ChessDrawBoardStrategy : public DrawBoardStrategy
{
public:
    ChessDrawBoardStrategy(int width, int height, int margin, int num_lines_v, int num_lines_h)
        : DrawBoardStrategy(width, height, margin, num_lines_v, num_lines_h) {}
    void draw() const override;
};