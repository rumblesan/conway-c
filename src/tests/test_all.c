#include <stdio.h>

#include "tests/min_unit.h"
#include "tests/test_gol.h"
#include "tests/test_gfx.h"

int tests_run;

int main(int argc, char *argv[]) {

    printf("\n");
    printf("*****************\n");
    printf("* Running tests *\n");
    printf("*****************\n\n");

    int result = 0;

    tests_run = 0;
    char *gol_results = test_gol();
    if (gol_results != 0) {
        printf("%s\n", gol_results);
    } else {
        printf("GOL TESTS PASSED\n");
    }
    printf("    Tests run: %d\n", tests_run);
    printf("\n");

    result = result || (gol_results != 0);

    tests_run = 0;
    char *gfx_results = test_gfx();
    if (gfx_results != 0) {
        printf("%s\n", gfx_results);
    } else {
        printf("GFX TESTS PASSED\n");
    }
    printf("    Tests run: %d\n", tests_run);
    printf("\n");

    result = result || (gfx_results != 0);

    return result;
}

