#include <stdlib.h>

#include "core/gol.h"

GOL gol_create_grid(int x, int y) {

    GOL g = malloc(sizeof(GOL_Grid));

    g->cells_x = x;
    g->cells_y = y;

    g->grid = (int **) malloc(sizeof(int *) * g->cells_x);

    for (int i = 0; i < g->cells_x; i++) {
        g->grid[i] = (int *) malloc(sizeof(int) * g->cells_y);

        for (int j = 0; j < g->cells_y; j++) {
            g->grid[i][j] = 0;
        }

    }

    return g;
}

void gol_cleanup_grid(GOL g) {

    for (int i = 0; i < g->cells_x; i++) {
        free(g->grid[i]);
    }

    free(g->grid);

}

