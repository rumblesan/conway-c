
#include "tests/min_unit.h"
#include "tests/test_gol.h"
#include "core/gol.h"


static char * test_creation() {
    GOL g = gol_create_grid(10, 10);

    mu_assert("Error: grid x cells should be 10", g->cells_x == 10);
    mu_assert("Error: grid y cells should be 10", g->cells_y == 10);

    gol_cleanup_grid(g);
    return 0;
}

static char * test_iterate_creation() {
    GOL g = gol_create_grid(10, 10);

    GOL new_g = gol_iterate_grid(g);

    mu_assert("Error: iterated grid should be a new grid", g != new_g);

    gol_cleanup_grid(new_g);
    return 0;
}

static char * test_iterate_all_zeros() {
    GOL g = gol_create_grid(10, 10);

    GOL new_g = gol_iterate_grid(g);

    // add the 2 because we have the buffers on the grid
    for (int x = 0; x < (new_g->cells_x +  2); x++) {
        for (int y = 0; y < (new_g->cells_y + 2); y++) {
            mu_assert("Error: grid coord should be 0", new_g->grid[x][y] == 0);
        }
    }

    gol_cleanup_grid(new_g);
    return 0;
}

static char * test_iterate_all_ones() {
    GOL g = gol_create_grid(10, 10);

    // add the 2 because we have the buffers on the grid
    for (int x = 0; x < (g->cells_x + 2); x++) {
        for (int y = 0; y < (g->cells_y + 2); y++) {
            g->grid[x][y] = 1;
        }
    }

    GOL new_g = gol_iterate_grid(g);

    // offset by 1 because we only care about the inner section
    for (int x = 1; x < (new_g->cells_x + 1); x++) {
        for (int y = 1; y < (new_g->cells_y + 1); y++) {
            // All the cells should have died due to overcrowding
            mu_assert("Error: grid coord should be 0", new_g->grid[x][y] == 0);
        }
    }

    gol_cleanup_grid(new_g);
    return 0;
}

char * test_gol() {
    mu_run_test(test_creation);
    mu_run_test(test_iterate_creation);
    mu_run_test(test_iterate_all_zeros);
    mu_run_test(test_iterate_all_ones);

    return 0;
}

