#include <stdint.h>

#include "core/colour.h"

uint32_t colour_create(uint8_t r, uint8_t g, uint8_t b) {
    return (r << 16) + (g << 8) + (b);
}

