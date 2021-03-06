#ifndef GOL_H
#define GOL_H

typedef struct gol_grid *GOL;
typedef struct gol_grid {

    int cells_x;
    int cells_y;

    int **grid;

} GOL_Grid;

GOL gol_create_grid(int x, int y);

void gol_randomise_grid(GOL g, float threshold);

int gol_set_grid_coord(GOL g, int x, int y, int value);

int gol_get_grid_coord(GOL g, int x, int y);

GOL gol_iterate_grid(GOL g);

void gol_cleanup_grid(GOL g);

#endif
