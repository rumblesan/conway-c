#include <stdio.h>
#include <SDL/SDL.h>
#include <math.h>

#include "core/gfx.h"
#include "core/gol.h"
#include "core/colour.h"

void setpixel(Screen s, int x, int y, colour c)
{
    Uint32 *pixmem32;
    Uint32 colour;  
 
    colour = SDL_MapRGB( s->screen->format, colour_get_red(c), colour_get_green(c), colour_get_blue(c));
  
    pixmem32 = (Uint32*) s->screen->pixels  + y + x;
    *pixmem32 = colour;
}

void draw_rect(Screen s, int x_coord, int y_coord, int height, int width, colour c) {

    int yPos;

    for (int y = 0; y < height; y++) {
        yPos = (((y_coord * height) + y) * s->screen->pitch) / BPP;
        for (int x = 0; x < width; x++) {
            setpixel(s, (x + (x_coord * width)), yPos, c);
        }
    }

}

Screen gfx_create_screen(int cell_size) {

    Screen s = (Screen) malloc(sizeof(GFX_Screen));

    if (SDL_Init(SDL_INIT_VIDEO) < 0 ) {
        return 0;
    }

    if (!(s->screen = SDL_SetVideoMode(0, 0, DEPTH, SDL_FULLSCREEN|SDL_HWSURFACE)))
    {
        SDL_Quit();
        return 0;
    }

    const SDL_VideoInfo* vid_info = SDL_GetVideoInfo();

    s->width  = vid_info->current_w;
    s->height = vid_info->current_h;

    s->cell_size = cell_size;

    return s;
}

void gfx_draw_screen(GOL g, Screen s)
{ 
    if(SDL_MUSTLOCK(s->screen)) 
    {
        if(SDL_LockSurface(s->screen) < 0) return;
    }

    for (int x = 0; x < g->cells_x; x++) {
        for (int y = 0; y < g->cells_y; y++) {
            if (gol_get_grid_coord(g, x, y)) {
                draw_rect(s, x, y, s->cell_size, s->cell_size, colour_create(255, 255, 255));
            } else {
                draw_rect(s, x, y, s->cell_size, s->cell_size, colour_create(0, 0, 0));
            }
        }
    }

    if(SDL_MUSTLOCK(s->screen)) {
        SDL_UnlockSurface(s->screen);
    }
  
    SDL_Flip(s->screen); 
}

void gfx_cleanup_screen(Screen s) {

    SDL_Quit();
    free(s);
}

