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

void render_scene_with_cylinders(FILE *f, t_camera camera,
                                t_sphere *spheres, int num_spheres,
                                t_cylinder *cylinders, int num_cylinders,
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
            t_color color = TraceRayWithCylinders(camera.P, ray_dir, 1.0, DBL_MAX,
                                                 spheres, num_spheres,
                                                 cylinders, num_cylinders,
                                                 background);
            fprintf(f, "%d %d %d ", color.r, color.g, color.b);
        }
        fprintf(f, "\n");
    }
}

void render_scene_with_planes(FILE *f, t_camera camera,
                             t_sphere *spheres, int num_spheres,
                             t_cylinder *cylinders, int num_cylinders,
                             t_plane *planes, int num_planes,
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
            t_color color = TraceRayWithPlanes(camera.P, ray_dir, 1.0, DBL_MAX,
                                              spheres, num_spheres,
                                              cylinders, num_cylinders,
                                              planes, num_planes,
                                              background);
            fprintf(f, "%d %d %d ", color.r, color.g, color.b);
        }
        fprintf(f, "\n");
    }
}

void render_scene_with_lighting(FILE *f, t_camera camera,
                               t_sphere *spheres, int num_spheres,
                               t_cylinder *cylinders, int num_cylinders,
                               t_plane *planes, int num_planes,
                               t_ambient_light ambient,
                               t_point_light *lights, int num_lights,
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
            t_color color = TraceRayWithLighting(camera.P, ray_dir, 1.0, DBL_MAX,
                                                spheres, num_spheres,
                                                cylinders, num_cylinders,
                                                planes, num_planes,
                                                ambient, lights, num_lights,
                                                background);
            fprintf(f, "%d %d %d ", color.r, color.g, color.b);
        }
        fprintf(f, "\n");
    }
}
