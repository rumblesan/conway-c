#include <stdlib.h>

#include "tests/min_unit.h"
#include "tests/test_gol.h"
#include "core/gol.h"


static char * test_creation() {
    GOL g = gol_create_grid(10, 10);

    mu_assert("Error: grid x cells should be 10", g->cells_x == 10);
    mu_assert("Error: grid y cells should be 10", g->cells_y == 10);

    for (int x = 0; x < (g->cells_x + 2); x++) {
        for (int y = 0; y < (g->cells_y + 2); y++) {
            mu_assert("Error: grid cells should be zero", g->grid[x][y] == 0);
        }
    }

    gol_cleanup_grid(g);
    return 0;
}

static char * test_iterate_creation() {
    GOL g = gol_create_grid(10, 10);

    GOL new_g = gol_iterate_grid(g);

    mu_assert("Error: iterated grid should be a new grid", g != new_g);

    for (int x = 0; x < (g->cells_x + 2); x++) {
        for (int y = 0; y < (g->cells_y + 2); y++) {
            mu_assert("Error: iterated grid cells should be zero", new_g->grid[x][y] == 0);
        }
    }

    gol_cleanup_grid(new_g);
    return 0;
}

static char * test_set_grid_coord() {
    GOL g = gol_create_grid(10, 10);

    int ok_check_value = gol_set_grid_coord(g, 1, 1, 1);

    mu_assert("Error: set correct coord should return 1", ok_check_value == 1);
    mu_assert("Error: set_grid_coord should include offset", g->grid[2][2] == 1);

    int bad_check_value = gol_set_grid_coord(g, 1, 13, 1);

    mu_assert("Error: set incorrect coord should return 0", bad_check_value == 0);

    gol_cleanup_grid(g);
    return 0;
}

static char * test_get_grid_coord() {
    GOL g = gol_create_grid(10, 10);

    gol_set_grid_coord(g, 1, 1, 1);
    int ok_grid_value = gol_get_grid_coord(g, 1, 1);

    mu_assert("Error: get correct coord should return 1", ok_grid_value == 1);

    int bad_grid_value = gol_get_grid_coord(g, 1, 13);

    mu_assert("Error: get incorrect coord should return -1", bad_grid_value == -1);

    gol_cleanup_grid(g);
    return 0;
}

static char * test_iterate_all_zeros() {
    GOL g = gol_create_grid(10, 10);

    GOL new_g = gol_iterate_grid(g);

    for (int x = 0; x < new_g->cells_x; x++) {
        for (int y = 0; y < new_g->cells_y; y++) {
            // All the cells should be unchanged
            mu_assert("Error: grid coord should be 0", gol_get_grid_coord(new_g, x, y) == 0);
        }
    }

    gol_cleanup_grid(new_g);
    return 0;
}

static char * test_iterate_all_ones() {
    GOL g = gol_create_grid(10, 10);

    // add the 2 because we have the buffers on the grid
    // make sure to set all the buffers to 1
    // otherwise corner cells won't die
    for (int x = 0; x < (g->cells_x + 2); x++) {
        for (int y = 0; y < (g->cells_y + 2); y++) {
            g->grid[x][y] = 1;
        }
    }

    GOL new_g = gol_iterate_grid(g);

    for (int x = 0; x < new_g->cells_x; x++) {
        for (int y = 0; y < new_g->cells_y; y++) {
            // All the cells should have died due to overcrowding
            mu_assert("Error: grid coord should be 0", gol_get_grid_coord(new_g, x, y) == 0);
        }
    }

    gol_cleanup_grid(new_g);
    return 0;
}

// No specific test cases
// Just exercise all the code to check for errors
static char * test_iterate_rand_grid() {
    GOL g = gol_create_grid(10, 10);

    for (int x = 0; x < g->cells_x; x++) {
        for (int y = 0; y < g->cells_y; y++) {
            gol_set_grid_coord(g, x, y, rand()%2);
        }
    }

    GOL new_g = gol_iterate_grid(g);

    gol_cleanup_grid(new_g);
    return 0;
}

char * test_gol() {
    mu_run_test(test_creation);
    mu_run_test(test_set_grid_coord);
    mu_run_test(test_get_grid_coord);
    mu_run_test(test_iterate_creation);
    mu_run_test(test_iterate_all_zeros);
    mu_run_test(test_iterate_all_ones);
    mu_run_test(test_iterate_rand_grid);

    return 0;
}

