#include <stdio.h>

#include "graph.h"
#include "input.h"
#include "polish_note.h"

int main() {
    char symbols[MAX_LEN];
    char pol[ROWS][COLS];
    int exit_flag = 0;
    printf(
        "Поддерживаемые операции:\n sin(x) - синус от числа x;\n cos(x) - косинус от числа x;\n tan(x) - "
        "тангенс от числа x;\n ctg(x) - котангенс от числа x;\n sqrt(x) - котангенс от числа x;\n ln(x) - "
        "логарифм натуральный от числа x.\n \"+\" - операция сложения;\n \"-\" - операция вычитания;\n \"*\" "
        "- операция умножения;\n \"/\" - операция деления;\n \"~\" - унарный минус.\n");
    printf("Введите выражение без пробелов:\n");
    input(symbols, &exit_flag);
    if (exit_flag) {
        printf("n/a\n");
        return 1;
    }
    init(pol);
    double step_x = (4.0 * M_PI) / (COLS - 1);
    printf("\n");
    for (int i = 0; i < COLS; i++) {
        double result = to_polsky(symbols, i * step_x);
        int y = ROWS - 1 - round((1.0 - result) * (ROWS - 1) / 2.0);
        if (y >= 0 && y < ROWS) pol[y][i] = '*';
    }
    prin_pol(pol);
    return 0;
}
