#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <unistd.h>

#define MAX_PLAYERS 20

int main() {
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);

    int rows, cols;
    getmaxyx(stdscr, rows, cols);

    char players[MAX_PLAYERS] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J'};
    int num_players = 10;
    int k = 2; // Номер игрока для выхода
    int current_player = 0;
    int rounds = 0;

    while (1) {
        clear();
        mvprintw(rows / 2, cols / 2, "Round: %d", rounds);
        mvprintw(rows / 2 + 1, cols / 2, "Press 'S' to continue or 'C' to reset");

        int row_start = rows / 4;
        int col_start = cols / 4;

        int row = row_start;
        int col = col_start;
        int direction = 0; // 0 - right, 1 - down, 2 - left, 3 - up

        for (int i = 0; i < num_players; ++i) {
            if (i == current_player) {
                attron(A_REVERSE);
            }
            mvaddch(row, col, players[i]);
            attroff(A_REVERSE);
            refresh();
            usleep(500000); // Пауза 0.5 секунды

            switch (direction) {
                case 0:
                    col += 4;
                    if (col >= cols - col_start) {
                        direction = 1;
                        col = cols - col_start - 1;
                        row += 2;
                    }
                    break;
                case 1:
                    row += 2;
                    if (row >= rows - row_start) {
                        direction = 2;
                        row = rows - row_start - 1;
                        col -= 4;
                    }
                    break;
                case 2:
                    col -= 4;
                    if (col < col_start) {
                        direction = 3;
                        col = col_start;
                        row -= 2;
                    }
                    break;
                case 3:
                    row -= 2;
                    if (row < row_start) {
                        direction = 0;
                        row = row_start;
                        col += 4;
                    }
                    break;
                default:
                    break;
            }
        }

        char ch = getch();

        if (ch == 'S' || ch == 's') {
            if (num_players == 1) {
                mvprintw(rows / 2 + 2, cols / 2, "Winner is player %c", players[current_player]);
                refresh();
                usleep(2000000);
                break;
            }
            current_player = (current_player + k - 1) % num_players;
            for (int i = current_player; i < num_players - 1; ++i) {
                players[i] = players[i + 1];
            }
            num_players--;
            rounds++;
        } else if (ch == 'C' || ch == 'c') {
            num_players = 10;
            k = 2;
            current_player = 0;
            rounds = 0;
            for (int i = 0; i < num_players; ++i) {
                players[i] = 'A' + i;
            }
        } else if (ch == 27) { // Escape key
            break;
        }
    }

    endwin();
    return 0;
}
