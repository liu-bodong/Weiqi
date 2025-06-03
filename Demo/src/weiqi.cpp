#include <graphics.h>
#include <iostream>
#include "../header/board.h"
#include "../header/draw_board_strategy.h"
#include "../header/weiqi_draw_board_strategy.h"
// #include "stone.cpp"

enum e_state
{
    E = 0, // Empty
    B = 1, // Black stone
    W = 2  // White stone
};

/**
 * @brief Translates the x, y coordinates on screen to the index on the board.
 *
 * @param board
 * @param x
 * @param y
 * @return int
 */
std::pair<int, int> positionOnBoard(const DrawBoardStrategy *dbs, int x, int y)
{
    int cell_size_v = dbs->grid_size_v_;
    int cell_size_h = dbs->grid_size_h_;
    int row = (y - dbs->margin_) / cell_size_v;
    int col = (x - dbs->margin_) / cell_size_h;
    if (row < 0 || row >= dbs->num_lines_v_ - 1 || col < 0 || col >= dbs->num_lines_h_ - 1)
    {
        return {-1, -1}; // Invalid position
    }
    return {col, row}; // Return as (col, row
}

void DrawStones(Board &board)
{
    auto dbs = board.draw_strategy_;
    int grid_size = dbs->grid_size_h_;
    int margin = dbs->margin_;
    int weiqi_offset = grid_size / 2;
    int size = (dbs->num_lines_h_ - 1) * (dbs->num_lines_v_ - 1);
    for (int i = 0; i < board.num_h_; i++)
    {
        for (int j = 0; j < board.num_v_; j++)
        {
            if (board.get_at(i, j) == e_state::B)
            {
                setfillcolor(BLACK);
                solidcircle(margin + weiqi_offset + i * grid_size, margin + weiqi_offset + j * grid_size, grid_size / 2 - 1);
            }
            else if (board.get_at(i, j) == e_state::W)
            {
                setfillcolor(WHITE);
                setlinecolor(BLACK);
                fillcircle(margin + weiqi_offset + i * grid_size, margin + weiqi_offset + j * grid_size, grid_size / 2 - 1);
            }
        }
    }
}

// void DrawCursor(Board &board, const int ind, const int cur_player)
// {
//     auto pair = board.index_to_xy(ind);
//     int x = pair.first;
//     int y = pair.second;
//     int grid_size = board.grid_size_h_;
//     int margin = board.margin_;
//     int weiqi_offset = grid_size / 2;
//     if (cur_player == 0) // Black player
//     {
//         setfillcolor(BLACK);
//         solidcircle(margin + weiqi_offset + x * grid_size, margin + weiqi_offset + y * grid_size, grid_size / 2 - 5);
//     }
//     else // White player
//     {
//         setfillcolor(WHITE);
//         setlinecolor(BLACK);
//         fillcircle(margin + weiqi_offset + x * grid_size, margin + weiqi_offset + y * grid_size, grid_size / 2 - 5);
//     }
// }

int main()
{
    WeiqiDrawBoardStrategy *draw_strategy = new WeiqiDrawBoardStrategy(800, 800, 10, 19, 19);
    Board board = Board(draw_strategy, 19, 19); // Create a Weiqi board with 19x19 grids
    initgraph(800, 800);
    bool running = true;
    bool current_player = 0; // 0 for black, 1 for white
    int x = 0;
    int y = 0;
    std::pair<int, int> pos_pair;

    BeginBatchDraw();

    setbkcolor(0xCDEBFF);

    while (running)
    {
        const DWORD start_time = GetTickCount();

        ExMessage msg;

        while (peekmessage(&msg))
        {
            if (msg.message == WM_MOUSEMOVE)
            {
                x = msg.x;
                y = msg.y;
                pos_pair = positionOnBoard(draw_strategy, x, y);
            }

            if (msg.message == WM_LBUTTONDOWN)
            {
                // x = msg.x;
                // y = msg.y;
                auto [col, row] = positionOnBoard(draw_strategy, msg.x, msg.y);

                if (col != -1 && row != -1 && board.get_at(col, row) == e_state::E)
                {
                    if (!current_player)
                    {
                        board.set_at(col, row, e_state::B);
                        current_player = !current_player;
                        // board.print();
                    }
                    else
                    {
                        board.set_at(col, row, e_state::W);
                        current_player = !current_player;
                        // board.print();
                    }
                }
            }
        }

        // Draw
        cleardevice();
        board.draw_board();
        /*        / *DrawCursor* /(board, cur_ind, current_player);*/
        DrawStones(board);

        FlushBatchDraw();

        // Check Win Condition

        // Optimization: Limit the frame rate to 60 FPS
        const DWORD end_time = GetTickCount();
        const DWORD delta_time = end_time - start_time;

        if (delta_time < 1000 / 120)
        {
            Sleep(1000 / 120 - delta_time);
        }
    }

    EndBatchDraw();
}