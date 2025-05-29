#include <graphics.h>
#include <iostream>
#include "../header/board.h"
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
int positionOnBoard(const Board &board, int x, int y)
{
    int cell_size_v = board.grid_size_v_;
    int cell_size_h = board.grid_size_h_;
    int row = (y - board.margin_) / cell_size_v;
    int col = (x - board.margin_) / cell_size_h;
    if (row < 0 || row >= board.num_grids_v_ || col < 0 || col >= board.num_grids_h_)
    {
        return -1; // Invalid position
    }
    return board.xy_to_index(col, row); // Return the index in the board vector
}

void DrawWhite(Board &board)
{
    int grid_size = board.grid_size_h_;
    int margin = board.margin_;
    int weiqi_offset = grid_size / 2;
    for (int idx = 0; idx < 361; idx++)
    {
        if (board[idx] != e_state::B && board[idx] != e_state::E)
        {
            int i = (idx) % 19;
            int j = (idx) / 19;
            setfillcolor(WHITE);
            setlinecolor(BLACK);
            fillcircle(margin + weiqi_offset + i * grid_size, margin + weiqi_offset + j * grid_size, grid_size / 2 - 1);
        }
    }
}

void DrawBlack(Board &board)
{
    int grid_size = board.grid_size_h_;
    int margin = board.margin_;
    int weiqi_offset = grid_size / 2;
    for (int idx = 0; idx < 361; idx++)
    {
        if (board[idx] != e_state::W && board[idx] != e_state::E)
        {
            int i = (idx) % 19;
            int j = (idx) / 19;
            setfillcolor(BLACK);
            solidcircle(margin + weiqi_offset + i * grid_size, margin + weiqi_offset + j * grid_size, grid_size / 2 - 1);
        }
    }
}

void DrawCursor(Board &board, const int ind, const int cur_player)
{
    auto pair = board.index_to_xy(ind);
    int x = pair.first;
    int y = pair.second;
    int grid_size = board.grid_size_h_;
    int margin = board.margin_;
    int weiqi_offset = grid_size / 2;
    if (cur_player == 0) // Black player
    {
        setfillcolor(BLACK);
        solidcircle(margin + weiqi_offset + x * grid_size, margin + weiqi_offset + y * grid_size, grid_size / 2 - 5);
    }
    else // White player
    {
        setfillcolor(WHITE);
        setlinecolor(BLACK);
        fillcircle(margin + weiqi_offset + x * grid_size, margin + weiqi_offset + y * grid_size, grid_size / 2 - 5);
    }
}

int main()
{
    Board board = Board(800, 800, 10, 19, 19, true); // Create a Weiqi board with 19x19 gri
    initgraph(1000, 1000);
    bool running = true;
    bool current_player = 0; // 0 for black, 1 for white
    int x = 0;
    int y = 0;
    int cur_ind = -1;

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
                cur_ind = positionOnBoard(board, x, y);
            }

            if (msg.message == WM_LBUTTONDOWN)
            {
                // x = msg.x;
                // y = msg.y;
                int pos = positionOnBoard(board, msg.x, msg.y);

                if (pos != -1 && board[pos] == e_state::E)
                {
                    if (!current_player)
                    {
                        board[pos] = e_state::B;
                        current_player = !current_player;
                        // board.print();
                    }
                    else
                    {
                        board[pos] = e_state::W;
                        current_player = !current_player;
                        // board.print();
                    }
                }
            }
        }

        // Draw
        cleardevice();
        board.draw_board();
        DrawCursor(board, cur_ind, current_player);

        DrawBlack(board);
        DrawWhite(board);

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