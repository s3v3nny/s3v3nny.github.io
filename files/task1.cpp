#include <ncurses.h>
#include <stdlib.h>

#define MAX_ROWS 10
#define MAX_COLS 10

void drawPlayers(int row, int col, int players[MAX_ROWS][MAX_COLS], int count) {
    clear();
    mvprintw(0, 0, "Нажмите 'S' для продолжения, 'C' для новой игры, 'Escape' для выхода");
    mvprintw(1, 0, "Число выполненных поворотов: %d", count);

    for (int i = 0; i < MAX_ROWS; ++i) {
        for (int j = 0; j < MAX_COLS; ++j) {
            if (players[i][j] > 0) {
                if (i == row && j == col) {
                    attron(A_REVERSE);
                    printw("И");
                    attroff(A_REVERSE);
                } else {
                    printw("O");
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

    int players[MAX_ROWS][MAX_COLS] = {0};
    int count = 0, row = 0, col = 0;
    int numRows, numCols;

    mvprintw(2, 0, "Введите количество строк и столбцов для прямоугольника (не более %d на %d): ", MAX_ROWS, MAX_COLS);
    scanw("%d %d", &numRows, &numCols);

    if (numRows < 1 || numRows > MAX_ROWS || numCols < 1 || numCols > MAX_COLS) {
        endwin();
        printf("Некорректные размеры прямоугольника.\n");
        return 1;
    }

    for (int i = 0; i < numCols; ++i) {
        players[0][i] = i + 1;
        players[numRows - 1][i] = i + numCols + 1;
    }

    for (int i = 1; i < numRows - 1; ++i) {
        players[i][0] = 2 * numCols + numRows - i;
        players[i][numCols - 1] = numCols + i;
    }

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
        } else if (ch == 'C' || ch == 'c') {
            count = 0;
            row = 0;
            col = 0;
        } else if (ch == 27) { // Escape key
            break;
        }
    }

    endwin();
    return 0;
}
