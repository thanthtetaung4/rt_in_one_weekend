#include "../inc/rt.h"

#include <stdio.h>


color ray_color(ray r) {
    vec3 unit_direction = vec3_unit(ray_direction(r));
    double a = 0.5 * (unit_direction.y + 1.0);

    color white = vec3_create(1.0, 1.0, 1.0);
    color blue = vec3_create(0.5, 0.7, 1.0);

    // Linear interpolation: (1-a)*white + a*blue
    color c1 = vec3_scale(white, 1.0 - a);
    color c2 = vec3_scale(blue, a);
    return vec3_add(c1, c2);
}

int main() {
    // Image
    double aspect_ratio = 16.0 / 9.0;
    int image_width = 400;
    int image_height = (int)(image_width / aspect_ratio);
    if (image_height < 1) image_height = 1;

    // Camera parameters
    double focal_length = 1.0;
    double viewport_height = 2.0;
    double viewport_width = viewport_height * ((double)image_width / image_height);
    point3 camera_center = vec3_create(0, 0, 0);

    // Viewport vectors
    vec3 viewport_u = vec3_create(viewport_width, 0, 0);
    vec3 viewport_v = vec3_create(0, -viewport_height, 0);

    // Pixel delta vectors
    vec3 pixel_delta_u = vec3_div(viewport_u, (double)image_width);
    vec3 pixel_delta_v = vec3_div(viewport_v, (double)image_height);

    // Upper left corner of viewport
    vec3 half_u = vec3_scale(viewport_u, 0.5);
    vec3 half_v = vec3_scale(viewport_v, 0.5);
    vec3 focus_vec = vec3_create(0, 0, focal_length);

    vec3 viewport_upper_left = vec3_sub(
        vec3_sub(
            vec3_sub(camera_center, focus_vec), // camera_center - focal_length in z
            half_u
        ),
        half_v
    );

    // Location of upper left pixel center (offset by half pixel)
    vec3 half_pixel_offset = vec3_scale(vec3_add(pixel_delta_u, pixel_delta_v), 0.5);
    vec3 pixel00_loc = vec3_add(viewport_upper_left, half_pixel_offset);

    // Write PPM header
    printf("P3\n%d %d\n255\n", image_width, image_height);

    for (int j = 0; j < image_height; j++) {
        fprintf(stderr, "\rScanlines remaining: %d ", image_height - j);

        for (int i = 0; i < image_width; i++) {
            // Calculate pixel center position
            vec3 offset_u = vec3_scale(pixel_delta_u, (double)i);
            vec3 offset_v = vec3_scale(pixel_delta_v, (double)j);

            vec3 pixel_center = vec3_add(pixel00_loc, vec3_add(offset_u, offset_v));
            vec3 ray_direction = vec3_sub(pixel_center, camera_center);

            ray r = ray_create(camera_center, ray_direction);
            color pixel_color = ray_color(r);
            write_color(stdout, pixel_color);
        }
    }

    fprintf(stderr, "\rDone.                 \n");
    return 0;
}
