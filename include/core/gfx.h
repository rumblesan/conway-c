#ifndef GFX_H
#define GFX_H

#include <SDL/SDL.h>

#include "core/gol.h"

#define BPP 4
#define DEPTH 32

typedef struct gfx_screen *Screen;
typedef struct gfx_screen {

    int width;
    int height;

    int cell_size;

    SDL_Surface *screen;

} GFX_Screen;

Screen gfx_create_screen();

Screen gfx_create_screen(int cell_size);

void gfx_draw_screen(GOL g, Screen s);

void gfx_cleanup_screen(Screen s);

#endif
