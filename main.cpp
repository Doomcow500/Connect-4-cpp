#include <iostream>
#include <vector>
#include <limits> 

using namespace std;

const int ROWS = 6;
const int COLS = 7;
const char EMPTY = ' ';
const char PLAYER_1 = 'X';
const char PLAYER_2 = 'O';

class Connect4 {
private:
    vector<vector<char>> board;
    char currentPlayer;

public:
    Connect4() {
        board.resize(ROWS, vector<char>(COLS, EMPTY));
        currentPlayer = PLAYER_1;
    }

    void printBoard() {
        cout << " 1 2 3 4 5 6 7\n";
        for (int i = 0; i < ROWS; ++i) {
            for (int j = 0; j < COLS; ++j) {
                cout << "|";
                cout << board[i][j];
            }
            cout << "|\n";
        }
        cout << "---------------\n";
    }

    bool isValidMove(int col) {
        return col >= 0 && col < COLS && board[0][col] == EMPTY;
    }

    void makeMove(int col) {
        for (int i = ROWS - 1; i >= 0; --i) {
            if (board[i][col] == EMPTY) {
                board[i][col] = currentPlayer;
                break;
            }
        }
    }

    bool checkWin() {
        // Check for horizontal win
        for (int i = 0; i < ROWS; ++i) {
            for (int j = 0; j < COLS - 3; ++j) {
                if (board[i][j] == currentPlayer && board[i][j + 1] == currentPlayer &&
                    board[i][j + 2] == currentPlayer && board[i][j + 3] == currentPlayer) {
                    return true;
                }
            }
        }

        // Check for vertical win
        for (int i = 0; i < ROWS - 3; ++i) {
            for (int j = 0; j < COLS; ++j) {
                if (board[i][j] == currentPlayer && board[i + 1][j] == currentPlayer &&
                    board[i + 2][j] == currentPlayer && board[i + 3][j] == currentPlayer) {
                    return true;
                }
            }
        }

        // Check for diagonal (down-right) win
        for (int i = 0; i < ROWS - 3; ++i) {
            for (int j = 0; j < COLS - 3; ++j) {
                if (board[i][j] == currentPlayer && board[i + 1][j + 1] == currentPlayer &&
                    board[i + 2][j + 2] == currentPlayer && board[i + 3][j + 3] == currentPlayer) {
                    return true;
                }
            }
        }

        // Check for diagonal (up-right) win
        for (int i = 3; i < ROWS; ++i) {
            for (int j = 0; j < COLS - 3; ++j) {
                if (board[i][j] == currentPlayer && board[i - 1][j + 1] == currentPlayer &&
                    board[i - 2][j + 2] == currentPlayer && board[i - 3][j + 3] == currentPlayer) {
                    return true;
                }
            }
        }

        return false;
    }

    bool isBoardFull() {
        for (int i = 0; i < ROWS; ++i) {
            for (int j = 0; j < COLS; ++j) {
                if (board[i][j] == EMPTY) {
                    return false;
                }
            }
        }
        return true;
    }

    void switchPlayer() {
        currentPlayer = (currentPlayer == PLAYER_1) ? PLAYER_2 : PLAYER_1;
    }

    char getCurrentPlayer() {
        return currentPlayer;
    }
};

int main() {
    Connect4 game;
    int col;

    cout << "Connect 4 - Two Players\n";
    cout << "Player 1: X, Player 2: O\n";

    while (true) {
        game.printBoard();

        cout << "Player " << game.getCurrentPlayer() << ", enter a column (1-7): ";
        cin >> col;

        if (cin.fail() || col < 1 || col > 7) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please try again.\n";
            continue;
        }

        col--; 

        if (game.isValidMove(col)) {
            game.makeMove(col);

            if (game.checkWin()) {
                game.printBoard();
                cout << "Player " << game.getCurrentPlayer() << " wins!\n";
                break;
            }

            if (game.isBoardFull()) {
                game.printBoard();
                cout << "It's a draw!\n";
                break;
            }

            game.switchPlayer();
        } else {
            cout << "Column is full. Try again.\n";
        }
    }

    return 0;
}