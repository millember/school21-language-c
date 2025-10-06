#include <stdio.h>

void pong_display(int X_BALL, int Y_BALL, int count_1, int count_2, int player1, int player2);
int current_coord(int speed, int coord);
int racket_movement(int step, int player);
void display_clear();

const int X_SIZE = 80, Y_SIZE = 25;
const char Y_WALL = '|';
const char X_WALL = '_';
const char BALL = 'o';
const char RAKET = '#';
const int STEP = 3;
const int POINTS_FOR_VICTORY = 21;

int main() {
    int speed_x = 1, speed_y = 1;
    int coord_x = 2, coord_y = 13;
    int check_leftr = 0, check_right = 0;
    int player1 = 5, player2 = 22;
    int step = 1;

    while (check_leftr < POINTS_FOR_VICTORY && check_right < POINTS_FOR_VICTORY) {
        display_clear();
        pong_display(coord_x, coord_y, check_leftr, check_right, player1, player2);
        fflush(stdout);

        if (step == 1) {
            player1 = racket_movement(step, player1);
            step = 2;
        } else {
            player2 = racket_movement(step, player2);
            step = 1;
        }

        for (int i = 0; i < STEP; i++) {
            if (coord_x == 2 && coord_y <= player1 + 1 && coord_y >= player1 - 1) speed_x = 1;
            if (coord_x == X_SIZE - 2 && coord_y <= player2 + 1 && coord_y >= player2 - 1) speed_x = -1;
            if (coord_x == 1 || coord_x == X_SIZE - 1) speed_x = -speed_x;
            if (coord_y == 1 || coord_y == Y_SIZE - 1) speed_y = -speed_y;
            if (coord_x == 1) check_right++;
            if (coord_x == X_SIZE - 1) check_leftr++;
            coord_x = current_coord(speed_x, coord_x);
            coord_y = current_coord(speed_y, coord_y);
        }
    }

    display_clear();
    if (check_leftr == POINTS_FOR_VICTORY)
        printf("Player 1 wins!");
    else
        printf("Player 2 wins!");

    return 0;
}

void display_clear() {
    printf("\033[H\033[J");
    fflush(stdout);
}

int racket_movement(int step, int player) {
    int result = player;
    char key = 0;
    while (1) {
        if (step == 1) {
            if (scanf("%c", &key) == 1 &&
                (key == 'A' || key == 'a' || key == 'Z' || key == 'z' || key == ' ') &&
                (getchar() == '\n' || getchar() == EOF)) {
                if (result > 1 && (key == 'A' || key == 'a')) {
                    result -= STEP;
                } else if (key == 'Z' || key == 'z') {
                    result += STEP;
                }
                break;
            }
        } else {
            if (scanf("%c", &key) == 1 &&
                (key == 'K' || key == 'k' || key == 'M' || key == 'm' || key == ' ') &&
                (getchar() == '\n' || getchar() == EOF)) {
                if (result > 1 && (key == 'K' || key == 'k')) {
                    result -= STEP;
                } else if (result < Y_SIZE - 2 && (key == 'M' || key == 'm')) {
                    result += STEP;
                }
                break;
            }
        }
    }
    return result;
}

int current_coord(int speed, int coord) { return coord + speed; }

void pong_display(int X_BALL, int Y_BALL, int count_1, int count_2, int player1, int player2) {
    for (int i = 0; i < X_SIZE / 2 - 2; i++) {
        printf(" ");
    }
    printf("%d : %d\n", count_1, count_2);

    for (int i = 0; i <= Y_SIZE; i++) {
        for (int j = 0; j <= X_SIZE; j++) {
            if ((j == 0) || (j == X_SIZE) || (j == X_SIZE / 2)) {
                printf("%c", Y_WALL);
            } else if ((i == 0) || (i == Y_SIZE)) {
                printf("%c", X_WALL);
            } else if (j == X_BALL && i == Y_BALL) {
                printf("%c", BALL);
            } else if ((j == 1 && (i == player1 - 1 || i == player1 || i == player1 + 1)) ||
                       (j == (X_SIZE - 1) && (i == player2 - 1 || i == player2 || i == player2 + 1))) {
                printf("%c", RAKET);
            } else {
                printf(" ");
            }
        }
        printf("\n");
    }
}
