#include "../inc/color.h"

void write_color(FILE* out, color pixel_color) {
    double r = pixel_color.x;
    double g = pixel_color.y;
    double b = pixel_color.z;

    // Convert to [0,255] range
    int rbyte = (int)(255.999 * r);
    int gbyte = (int)(255.999 * g);
    int bbyte = (int)(255.999 * b);

    // Write to file
    fprintf(out, "%d %d %d\n", rbyte, gbyte, bbyte);
}
