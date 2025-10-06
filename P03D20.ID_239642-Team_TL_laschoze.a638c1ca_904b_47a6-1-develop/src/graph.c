
#include "graph.h"

void init(char pol[ROWS][COLS]) {
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            pol[i][j] = TOCH;
        }
    }
}
void prin_pol(char pol[ROWS][COLS]) {
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            printf("%c", pol[i][j]);
        }
        if (i < ROWS - 1) {
            printf("\n");
        }
    }
}
