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

        int rows_offset = 4;
        int cols_offset = 4;

        for (int i = 0; i < num_players; ++i) {
            int row = rows_offset + (i / 5) * 4;
            int col = cols_offset + (i % 5) * 8;

            if (i == current_player) {
                attron(A_REVERSE);
            }
            mvaddch(row, col, players[i]);
            attroff(A_REVERSE);
            refresh();
            usleep(500000); // Пауза 0.5 секунды
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
