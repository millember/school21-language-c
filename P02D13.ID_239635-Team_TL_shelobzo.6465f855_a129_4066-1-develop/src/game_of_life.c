#include <ncurses.h>
#include <stdio.h>

#define WIDTH 80
#define HEIGHT 25
#define ALIVE '#'
#define DEAD '.'

void init_grid(char grid[HEIGHT][WIDTH]);
void draw_grid(char grid[HEIGHT][WIDTH], int speed);
int count_neighbors(char grid[HEIGHT][WIDTH], int y, int x);
void next_generation(char grid[HEIGHT][WIDTH]);

int main() {
    char grid[HEIGHT][WIDTH];

    FILE *original_stdin = stdin;

    init_grid(grid);

    stdin = freopen("/dev/tty", "r", stdin);
    if (stdin != NULL) {
        int speed = 100;

        initscr();
        cbreak();
        noecho();
        nodelay(stdscr, TRUE);
        curs_set(0);

        while (1) {
            int ch = getch();
            if (ch == ' ') break;
            if ((ch == 'A' || ch == 'a') && speed > 10) speed -= 10;
            if ((ch == 'Z' || ch == 'z') && speed < 1000) speed += 10;

            clear();
            draw_grid(grid, speed);
            refresh();

            next_generation(grid);
            napms(speed);
        }

        endwin();

        stdin = original_stdin;
    } else {
        fprintf(stderr, "Error restoring stdin\n");
    }

    return 0;
}

void init_grid(char grid[HEIGHT][WIDTH]) {
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            grid[y][x] = DEAD;
        }
    }

    int y, x;
    while (scanf("%d %d", &y, &x) == 2) {
        if (y >= 0 && y < HEIGHT && x >= 0 && x < WIDTH) {
            grid[y][x] = ALIVE;
        }
    }
}

void draw_grid(char grid[HEIGHT][WIDTH], int speed) {
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            mvaddch(y, x, grid[y][x]);
        }
    }

    if (HEIGHT + 1 < LINES) {
        mvprintw(HEIGHT, 0, "Speed: %dms", speed);
    }
    if (HEIGHT + 2 < LINES) {
        mvprintw(HEIGHT + 1, 0, "A/a: faster  Z/z: slower  SPACE: exit");
    }
}

int count_neighbors(char grid[HEIGHT][WIDTH], int y, int x) {
    int count = 0;
    for (int dy = -1; dy <= 1; dy++) {
        for (int dx = -1; dx <= 1; dx++) {
            if (dx == 0 && dy == 0) continue;

            int nx = (x + dx + WIDTH) % WIDTH;
            int ny = (y + dy + HEIGHT) % HEIGHT;

            if (grid[ny][nx] == ALIVE) count++;
        }
    }
    return count;
}

void next_generation(char grid[HEIGHT][WIDTH]) {
    char new_grid[HEIGHT][WIDTH];

    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            int neighbors = count_neighbors(grid, y, x);

            if (grid[y][x] == ALIVE) {
                new_grid[y][x] = (neighbors == 2 || neighbors == 3) ? ALIVE : DEAD;
            } else {
                new_grid[y][x] = (neighbors == 3) ? ALIVE : DEAD;
            }
        }
    }

    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            grid[y][x] = new_grid[y][x];
        }
    }
}