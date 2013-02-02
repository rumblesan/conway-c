#ifndef COLOUR_H
#define COLOUR_H

#include <stdint.h>

typedef uint32_t colour;

colour colour_create(uint8_t r, uint8_t g, uint8_t b);

uint8_t colour_get_red(colour c);
uint8_t colour_get_green(colour c);
uint8_t colour_get_blue(colour c);

#endif
