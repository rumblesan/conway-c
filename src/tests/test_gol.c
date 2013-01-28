
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

char * test_gol() {
    mu_run_test(test_creation);

    return 0;
}

