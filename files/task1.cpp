#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>

#define MAX_PLAYERS 10
#define ESC 27

int main() {
    initscr(); // Инициализация экрана ncurses
    noecho(); // Не выводить вводимые символы
    curs_set(FALSE); // Скрыть курсор

    int rows, cols;
    getmaxyx(stdscr, rows, cols); // Получение размеров окна

    int numPlayers;
    int playerX[MAX_PLAYERS], playerY[MAX_PLAYERS];
    int currentTurn = 0, turns = 0, k;
    int ch;

    clear();
    mvprintw(0, 0, "Введите количество игроков (не более %d): ", MAX_PLAYERS);
    refresh();
    scanw("%d", &numPlayers);

    if (numPlayers <= 0 || numPlayers > MAX_PLAYERS) {
        endwin();
        printf("Неверное количество игроков.\n");
        return 1;
    }

    for (int i = 0; i < numPlayers; ++i) {
        playerX[i] = i % (cols - 2) + 1;
        playerY[i] = i / (cols - 2) + 1;
    }

    mvprintw(rows - 1, 0, "Нажмите 'C' для начальной позиции, 'S' для продолжения, 'Esc' для выхода");

    while ((ch = getch()) != ESC) {
        switch (ch) {
            case 'C':
            case 'c':
                turns = 0;
                currentTurn = 0;
                break;
            case 'S':
            case 's':
                ++turns;
                ++currentTurn;
                mvprintw(rows - 2, 0, "Текущий ход: %d", turns);
                refresh();
                break;
        }

        if (turns > 0 && currentTurn % numPlayers == 0) {
            mvprintw(playerY[currentTurn % numPlayers], playerX[currentTurn % numPlayers], " ");
            refresh();
        }
    }

    endwin();
    return 0;
}
