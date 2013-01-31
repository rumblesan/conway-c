#include <stdlib.h>

#include "tests/min_unit.h"
#include "tests/test_gfx.h"
#include "core/gfx.h"


static char * test_creation() {
    Screen s = gfx_create_screen();

    gfx_cleanup_screen(s);
    return 0;
}

char * test_gfx() {
    mu_run_test(test_creation);

    return 0;
}

