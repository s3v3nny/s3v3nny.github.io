#include <ncurses.h>
#include <stdlib.h>

#define MAX_ROWS 10
#define MAX_COLS 10

void drawPlayers(int row, int col, char players[MAX_ROWS][MAX_COLS], int count) {
    clear();
    mvprintw(0, 0, "Нажмите 'S' для продолжения, 'C' для новой игры, 'Escape' для выхода");
    mvprintw(1, 0, "Число выполненных поворотов: %d", count);

    for (int i = 0; i < MAX_ROWS; ++i) {
        for (int j = 0; j < MAX_COLS; ++j) {
            if (players[i][j] != ' ') {
                if (i == row && j == col) {
                    attron(A_REVERSE);
                    printw("%c", players[i][j]);
                    attroff(A_REVERSE);
                } else {
                    printw("%c", players[i][j]);
                }
            } else {
                printw(" ");
            }
        }
        printw("\n");
    }

    refresh();
}

int main() {
    initscr();
    curs_set(0);
    keypad(stdscr, TRUE);
    noecho();

    char players[MAX_ROWS][MAX_COLS] = {' '};
    int count = 0, row = 0, col = 0;
    int numRows, numCols, K;
    int numPlayers = 0;

    mvprintw(2, 0, "Width and height of rectangle (between %d and %d): ", MAX_ROWS, MAX_COLS);
    scanw("%d %d", &numRows, &numCols);

    mvprintw(3, 0, "Value of K: ");
    scanw("%d", &K);

    if (numRows < 1 || numRows > MAX_ROWS || numCols < 1 || numCols > MAX_COLS || K < 1) {
        endwin();
        printf("Invalid input.\n");
        return 1;
    }

    for (int i = 0; i < numRows; ++i) {
        for (int j = 0; j < numCols; ++j) {
            if ((i == 0 || i == numRows - 1 || j == 0 || j == numCols - 1) && numPlayers < 26) {
                players[i][j] = 'A' + numPlayers++;
            }
        }
    }

    int playerCounter = 0;

    while (1) {
        drawPlayers(row, col, players, count);

        int ch = getch();
        if (ch == 'S' || ch == 's') {
            count++;
            if (col < numCols - 1 && row == 0) {
                col++;
            } else if (row < numRows - 1 && col == numCols - 1) {
                row++;
            } else if (col > 0 && row == numRows - 1) {
                col--;
            } else if (row > 0 && col == 0) {
                row--;
            }

            if (players[row][col] != ' ') {
                if (++playerCounter % K == 0) {
                    players[row][col] = ' ';
                }
            }
        } else if (ch == 'C' || ch == 'c') {
            count = 0;
            row = 0;
            col = 0;
            numPlayers = 0;
            playerCounter = 0;
            for (int i = 0; i < MAX_ROWS; ++i) {
                for (int j = 0; j < MAX_COLS; ++j) {
                    players[i][j] = ' ';
                }
            }
            for (int i = 0; i < numRows; ++i) {
                for (int j = 0; j < numCols; ++j) {
                    if ((i == 0 || i == numRows - 1 || j == 0 || j == numCols - 1) && numPlayers < 26) {
                        players[i][j] = 'A' + numPlayers++;
                    }
                }
            }
        } else if (ch == 27) { // Escape key
            break;
        }
    }

    endwin();
    return 0;
}
