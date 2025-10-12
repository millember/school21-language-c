#include <ncurses.h>
#include <stdio.h>

void pong_display(int X_BALL, int Y_BALL, int count_1, int count_2, int player1, int player2);
int current_coord(int speed, int coord);
int racket_movement(int step, int player);
void display_clear();
void ncurses_init();

const int X_SIZE = 80, Y_SIZE = 25;
const char Y_WALL = '|';
const char X_WALL = '_';
const char BALL = 'o';
const char RAKET = '#';
const int STEP = 3;
const int POINTS_FOR_VICTORY = 21;
const int DELAY = 20000000;

int main() {
    initscr();
    ncurses_init();

    int speed_x = 1, speed_y = 1;
    int coord_x = 2, coord_y = 13;
    int check_leftr = 0, check_right = 0;
    int player1 = 5, player2 = 22;

    while (check_leftr < POINTS_FOR_VICTORY && check_right < POINTS_FOR_VICTORY) {
        display_clear();
        pong_display(coord_x, coord_y, check_leftr, check_right, player1, player2);

        for (int i = 0; i < DELAY / 3; i++) {
        }
        player1 = racket_movement(1, player1);

        for (int i = 0; i < DELAY / 3 * 2; i++) {
        }
        player2 = racket_movement(2, player2);

        if (coord_x == 2 && coord_y <= player1 + 1 && coord_y >= player1 - 1) speed_x = 1;
        if (coord_x == X_SIZE - 2 && coord_y <= player2 + 1 && coord_y >= player2 - 1) speed_x = -1;
        if (coord_x == 1 || coord_x == X_SIZE - 1) speed_x = -speed_x;
        if (coord_y == 1 || coord_y == Y_SIZE - 1) speed_y = -speed_y;
        if (coord_x == 1) check_right++;
        if (coord_x == X_SIZE - 1) check_leftr++;
        coord_x = current_coord(speed_x, coord_x);
        coord_y = current_coord(speed_y, coord_y);
    }

    display_clear();

    if (check_leftr == POINTS_FOR_VICTORY)
        printf("Player 1 wins!");
    else
        printf("Player 2 wins!");
    endwin();

    return 0;
}

void ncurses_init() {
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);
    curs_set(0);
}

void display_clear() {
    clear();
    refresh();
}

int racket_movement(int step, int player) {
    int result = player;
    char key = getch();

    if (step == 1) {
        if (result > 2 && (key == 'A' || key == 'a')) {
            result -= STEP;
        } else if (result < Y_SIZE - 3 && (key == 'Z' || key == 'z')) {
            result += STEP;
        }
    } else {
        if (result > 2 && (key == 'K' || key == 'k')) {
            result -= STEP;
        } else if (result < Y_SIZE - 3 && (key == 'M' || key == 'm')) {
            result += STEP;
        }
    }

    return result;
}

int current_coord(int speed, int coord) { return coord + speed; }

void pong_display(int X_BALL, int Y_BALL, int count_1, int count_2, int player1, int player2) {
    mvprintw(1, X_SIZE / 2 - 2, "%d   %d", count_1, count_2);
    for (int i = 0; i < Y_SIZE; i++) {
        for (int j = 0; j < X_SIZE; j++) {
            if ((j == 0) || (j == X_SIZE - 1) || (j == X_SIZE / 2)) {
                mvaddch(i, j, Y_WALL);
            } else if ((i == 0) || (i == Y_SIZE - 1)) {
                mvaddch(i, j, X_WALL);
            } else if (j == X_BALL && i == Y_BALL) {
                mvaddch(i, j, BALL);
            } else if ((j == 1 && (i == player1 - 1 || i == player1 || i == player1 + 1)) ||
                       (j == (X_SIZE - 2) && (i == player2 - 1 || i == player2 || i == player2 + 1))) {
                mvaddch(i, j, RAKET);
            }
        }
    }
    refresh();
}