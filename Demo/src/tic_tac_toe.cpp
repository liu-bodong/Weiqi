#include <graphics.h>
#include <vector>
#include <iostream>
#include "../header/board.h"

enum e_state
{
    E = 0,
    A = 1,
    B = 2
};

int width = 500;

int margin = 10;
int board_size = width - 2 * margin;
int grid_size = board_size / 3;

// void DrawBoard(int margin, int board_size)
// {
//     line(margin, margin, margin + board_size, margin);                           /// top
//     line(margin, margin + board_size, margin + board_size, margin + board_size); // bottom
//     line(margin, margin, margin, margin + board_size);                           // left
//     line(margin + board_size, margin, margin + board_size, margin + board_size); // right

//     line(margin, margin + grid_size, margin + board_size, margin + grid_size);         // horizontal line 1
//     line(margin, margin + 2 * grid_size, margin + board_size, margin + 2 * grid_size); // horizontal line 2
//     line(margin + grid_size, margin, margin + grid_size, margin + board_size);         // vertical line 1
//     line(margin + 2 * grid_size, margin, margin + 2 * grid_size, margin + board_size); // vertical line 2
// }

int positionOnBoard(std::vector<int> &board, int x, int y)
{
    int cell_size = grid_size;
    int row = (y - margin) / cell_size;
    int col = (x - margin) / cell_size;
    if (row < 0 || row > 2 || col < 0 || col > 2)
    {
        return -1; // Invalid position
    }
    return row * 3 + col; // Return the index in the board vector
}

/**
 * Checks the current state of the game:
 * Returns:
 *   -1 if game is draw
 *   0  if game is not over yet
 *   1  if game is won by A
 *   2  if game is won by B
 *
 */
int CheckWinCon(const std::vector<int> &board, const int index)
{
    bool not_filled = false;
    for (auto grid : board)
    {
        if (grid == 0)
        {
            not_filled = true;
            break;
        }
    }
    // check row
    if (board[index] == board[(index + 1) % 3] && board[index] == board[(index + 2) % 3])
    {
        return board[index];
    }

    // check col
    if (board[index] == board[(index + 3) % 9] && board[index] == board[(index + 6) % 9])
    {
        return board[index];
    }

    // check diagonal
    if ((index == 0 || index == 4 || index == 8) && (board[0] == board[4] && board[0] == board[8]))
    {
        return board[index];
    }
    if ((index == 2 || index == 4 || index == 6) && (board[2] == board[4] && board[4] == board[6]))
    {
        return board[index];
    }

    return not_filled - 1;
}

void DrawCircle(const std::vector<int> &board)
{
    for (int idx = 0; idx < 9; idx++)
    {
        if (board[idx] == e_state::B || board[idx] == e_state::E)
        {
            continue;
        }
        int i = (idx) % 3 + 1;
        int j = (idx) / 3 + 1;
        circle(i * grid_size + margin - grid_size / 2, j * grid_size + margin - grid_size / 2, grid_size / 2 - 5);
        circle(i * grid_size + margin - grid_size / 2, j * grid_size + margin - grid_size / 2, grid_size / 2 - 8);
    }
}

void DrawCross(const std::vector<int> &board)
{
    for (int idx = 0; idx < 9; idx++)
    {
        if (board[idx] == e_state::A || board[idx] == e_state::E)
        {
            continue;
        }
        int i = (idx) % 3;
        int j = (idx) / 3;
        line(margin + i * grid_size, margin + j * grid_size, margin + (i + 1) * grid_size, margin + (j + 1) * grid_size);
        line(margin + (i + 1) * grid_size, margin + j * grid_size, margin + i * grid_size, margin + (j + 1) * grid_size);
    }
}

int main()
{
    initgraph(width, width);

    Board board = Board(width, width, margin, 3, 3);

    bool running = true;

    bool current_player = 0; // 0 for player A, 1 for player B

    // mouse position
    int x = 0;
    int y = 0;
    int pos = 0;

    BeginBatchDraw();

    while (running)
    {

        const DWORD start_time = GetTickCount();

        // Monitor user input
        ExMessage msg;

        while (peekmessage(&msg))
        {

            if (msg.message == WM_LBUTTONDOWN)
            {
                x = msg.x;
                y = msg.y;
                pos = positionOnBoard(board, x, y);

                if (pos != -1 && board[pos] == e_state::E)
                {
                    if (!current_player)
                    {
                        board[pos] = e_state::A;
                        current_player = !current_player;
                    }
                    else
                    {
                        board[pos] = e_state::B;
                        current_player = !current_player;
                    }
                }
            }
        }

        // Draw
        board.draw_board();
        DrawCircle(board);
        DrawCross(board);

        FlushBatchDraw();

        // Check Win Condition
        int win_condition = CheckWinCon(board, pos);
        if (win_condition == -1)
        {
            MessageBox(GetHWnd(), _T("draw"), _T("game over"), MB_OK);
            running = false;
        }
        else if (win_condition == 1)
        {
            MessageBox(GetHWnd(), _T("A won"), _T("game over"), MB_OK);
            running = false;
        }
        else if (win_condition == 2)
        {
            MessageBox(GetHWnd(), _T("B won"), _T("game over"), MB_OK);
            running = false;
        }

        const DWORD end_time = GetTickCount();
        const DWORD delta_time = end_time - start_time;

        if (delta_time < 1000 / 60)
        {
            Sleep(1000 / 60 - delta_time);
        }
    }

    EndBatchDraw();
}
