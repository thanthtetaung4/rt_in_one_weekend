#ifndef COLOR_H
#define COLOR_H

#include <stdio.h>
#include "vec3.h"

typedef vec3 color;

void write_color(FILE* out, color pixel_color);

#endif
