#ifndef GOL_H
#define GOL_H

typedef struct gol_grid *GOL;
typedef struct gol_grid {

    int cells_x;
    int cells_y;

    int **grid;

} GOL_Grid;

GOL gol_create_grid(int x, int y);

int gol_set_grid_coord(GOL g, int x, int y, int value);

GOL gol_iterate_grid(GOL g);

void gol_cleanup_grid(GOL g);

#endif
