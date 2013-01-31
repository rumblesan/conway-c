#include <stdio.h>

#include "core/gfx.h"
#include "core/gol.h"

int main(int argc, char* argv[])
{

    int running = 1;

    Screen s = gfx_create_screen();

    if (!s) {
        return 1;
    }

    SDL_Event event;

    GOL g = gol_create_grid(100, 100);

    gol_randomise_grid(g, 0.9);
    g = gol_iterate_grid(g);
    gfx_draw_screen(g, s);

    while(running) {
        while(SDL_PollEvent(&event)) {

            switch (event.type) {

            case SDL_QUIT:
                running = 0;
                break;

            case SDL_KEYDOWN:
                switch (event.key.keysym.sym) {
                case SDLK_ESCAPE:
                    // Escape key
                    running = 0;
                    break;
                default:
                    break;
                }
                break;

            case SDL_MOUSEBUTTONDOWN:
                g = gol_iterate_grid(g);
                gfx_draw_screen(g, s);
                break;
            }
        }
    }

    gol_cleanup_grid(g);

    gfx_cleanup_screen(s);

    return 0;

}

