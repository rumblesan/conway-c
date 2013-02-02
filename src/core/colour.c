#include <stdint.h>

#include "core/colour.h"

uint32_t colour_create(uint8_t r, uint8_t g, uint8_t b) {
    return (r << 16) + (g << 8) + (b);
}

uint8_t colour_get_red(colour c) {
    return (c >> 16) & 255;
}

uint8_t colour_get_green(colour c) {
    return (c >> 8) & 255;
}

uint8_t colour_get_blue(colour c) {
    return (c >> 0) & 255;
}

