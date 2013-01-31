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
                //iterate cells
                break;
            }
        }
    }


    return 0;

}

