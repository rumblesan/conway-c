#include <stdlib.h>

#include "core/gol.h"

GOL gol_create_grid(int x_val, int y_val) {

    GOL g = malloc(sizeof(GOL_Grid));

    g->cells_x = x_val;
    g->cells_y = y_val;

    g->grid = (int **) malloc(sizeof(int *) * (g->cells_x + 2));

    // Add an extra row of cells onto each edge
    // This will be used as a buffer when iterating a grid
    // It will always be zero
    for (int x = 0; x < (g->cells_x + 2); x++) {
        g->grid[x] = (int *) malloc(sizeof(int) * (g->cells_y + 2));

        for (int y = 0; y < (g->cells_y + 2); y++) {
            g->grid[x][y] = 0;
        }

    }

    return g;
}

void gol_randomise_grid(GOL g, float threshold) {

    for (int x = 0; x < g->cells_x; x++) {
        for (int y = 0; y < g->cells_x; y++) {
            if ((rand() / (float) RAND_MAX) > threshold) {
                gol_set_grid_coord(g, x, y, 1);
            } else {
                gol_set_grid_coord(g, x, y, 0);
            }
        }
    }

}

int gol_set_grid_coord(GOL g, int x, int y, int value) {
    if ((x >= 0) && (x < g->cells_x) && (y >= 0) && (y < g->cells_y)) {
        g->grid[x+1][y+1] = value;
        return 1;
    }
    return 0;
}

int gol_get_grid_coord(GOL g, int x, int y) {
    if ((x >= 0) && (x < g->cells_x) && (y >= 0) && (y < g->cells_y)) {
        return g->grid[x+1][y+1];
    }
    return -1;
}

GOL gol_iterate_grid(GOL g) {

    GOL new_g = gol_create_grid(g->cells_x, g->cells_y);

    // Iterate between 1 and (cells_x + 1) so we don't touch the buffer
    int value;
    for (int x = 1; x < (g->cells_x + 1); x++) {
        for (int y = 1; y < (g->cells_x + 1); y++) {

            value = 0;
            value += g->grid[x-1][y-1];
            value += g->grid[x-1][y];
            value += g->grid[x-1][y+1];
            value += g->grid[x][y-1];
            value += g->grid[x][y+1];
            value += g->grid[x+1][y-1];
            value += g->grid[x+1][y];
            value += g->grid[x+1][y+1];

            if (g->grid[x][y] == 0) {
                if (value == 3) {
                    new_g->grid[x][y] = 1;
                }
            } else {
                if (value < 2) {
                    new_g->grid[x][y] = 0;
                } else if (value < 4) {
                    new_g->grid[x][y] = 1;
                } else {
                    new_g->grid[x][y] = 0;
                }
            }
        }
    }

    gol_cleanup_grid(g);

    return new_g;
}

void gol_cleanup_grid(GOL g) {

    for (int i = 0; i < (g->cells_x + 2); i++) {
        free(g->grid[i]);
    }

    free(g->grid);

}

