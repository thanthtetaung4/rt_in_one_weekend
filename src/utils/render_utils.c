#include "../../inc/rt.h"

void render_scene(FILE *f, t_camera camera, t_sphere *spheres, int num_spheres,
                  int width, int height) {
    t_color background = {0, 0, 0};
    t_camera_view view = setup_camera(camera, width, height);

    fprintf(f, "P3\n%d %d\n255\n", width, height);

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            t_vec3 pixel = vec3_add(view.pixel00,
                vec3_add(vec3_scale(view.pixel_delta_u, x),
                         vec3_scale(view.pixel_delta_v, height - 1 - y)));
            t_vec3 ray_dir = vec3_normalize(vec3_sub(pixel, camera.P));
            t_color color = TraceRay(camera.P, ray_dir, 1.0, DBL_MAX,
                                     spheres, num_spheres, background);
            fprintf(f, "%d %d %d ", color.r, color.g, color.b);
        }
        fprintf(f, "\n");
    }
}
