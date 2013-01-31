#include <SDL/SDL.h>

#include "core/gfx.h"
#include "core/gol.h"

void setpixel(Screen s, int x, int y, colour r, colour g, colour b)
{
    Uint32 *pixmem32;
    Uint32 colour;  
 
    colour = SDL_MapRGB( s->screen->format, r, g, b );
  
    pixmem32 = (Uint32*) s->screen->pixels  + y + x;
    *pixmem32 = colour;
}

void draw_rect(Screen s, int x_coord, int y_coord, int height, int width, colour r, colour g, colour b) {

    int yPos;

    for (int y = 0; y < height; y++) {
        yPos = ((y_coord + y) * s->screen->pitch) / BPP;
        for (int x = 0; x < width; x++) {
            setpixel(s, (x + x_coord), yPos, r, g, b);
        }
    }

}

Screen gfx_create_screen() {

    Screen s = (Screen) malloc(sizeof(GFX_Screen));

    const SDL_VideoInfo* vid_info = SDL_GetVideoInfo();

    s->width  = vid_info->current_w;
    s->height = vid_info->current_h;

    if (SDL_Init(SDL_INIT_VIDEO) < 0 ) {
        return 0;
    }

    if (!(s->screen = SDL_SetVideoMode(0, 0, DEPTH, SDL_FULLSCREEN|SDL_HWSURFACE)))
    {
        SDL_Quit();
        return 0;
    }

    return s;
}

void gfx_draw_screen(GOL g, Screen s)
{ 
    if(SDL_MUSTLOCK(s->screen)) 
    {
        if(SDL_LockSurface(s->screen) < 0) return;
    }

    // Drawing from grid goes here

    if(SDL_MUSTLOCK(s->screen)) {
        SDL_UnlockSurface(s->screen);
    }
  
    SDL_Flip(s->screen); 
}

void gfx_cleanup_screen(Screen s) {

    SDL_Quit();
    free(s);
}

