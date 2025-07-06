#include "../../inc/rt.h"

void render_scene(FILE *f, t_scene *scene) {
    t_camera_view view = setup_camera(scene->camera, scene->width, scene->height);

    fprintf(f, "P3\n%d %d\n255\n", scene->width, scene->height);

    for (int y = 0; y < scene->height; y++) {
        for (int x = 0; x < scene->width; x++) {
            t_vec3 pixel = vec3_add(view.pixel00,
                vec3_add(vec3_scale(view.pixel_delta_u, x),
                         vec3_scale(view.pixel_delta_v, scene->height - 1 - y)));
            t_vec3 ray_dir = vec3_normalize(vec3_sub(pixel, scene->camera.P));
            t_color color = TraceRay(scene->camera.P, ray_dir, 1.0, DBL_MAX, scene);
            fprintf(f, "%d %d %d ", color.r, color.g, color.b);
        }
        fprintf(f, "\n");
    }
}

void render_scene_with_cylinders(FILE *f, t_scene *scene) {
    t_camera_view view = setup_camera(scene->camera, scene->width, scene->height);

    fprintf(f, "P3\n%d %d\n255\n", scene->width, scene->height);

    for (int y = 0; y < scene->height; y++) {
        for (int x = 0; x < scene->width; x++) {
            t_vec3 pixel = vec3_add(view.pixel00,
                vec3_add(vec3_scale(view.pixel_delta_u, x),
                         vec3_scale(view.pixel_delta_v, scene->height - 1 - y)));
            t_vec3 ray_dir = vec3_normalize(vec3_sub(pixel, scene->camera.P));
            t_color color = TraceRayWithCylinders(scene->camera.P, ray_dir, 1.0, DBL_MAX, scene);
            fprintf(f, "%d %d %d ", color.r, color.g, color.b);
        }
        fprintf(f, "\n");
    }
}

void render_scene_with_planes(FILE *f, t_scene *scene) {
    t_camera_view view = setup_camera(scene->camera, scene->width, scene->height);

    fprintf(f, "P3\n%d %d\n255\n", scene->width, scene->height);

    for (int y = 0; y < scene->height; y++) {
        for (int x = 0; x < scene->width; x++) {
            t_vec3 pixel = vec3_add(view.pixel00,
                vec3_add(vec3_scale(view.pixel_delta_u, x),
                         vec3_scale(view.pixel_delta_v, scene->height - 1 - y)));
            t_vec3 ray_dir = vec3_normalize(vec3_sub(pixel, scene->camera.P));
            t_color color = TraceRayWithPlanes(scene->camera.P, ray_dir, 1.0, DBL_MAX, scene);
            fprintf(f, "%d %d %d ", color.r, color.g, color.b);
        }
        fprintf(f, "\n");
    }
}

void render_scene_with_lighting(FILE *f, t_scene *scene) {
    t_camera_view view = setup_camera(scene->camera, scene->width, scene->height);

    fprintf(f, "P3\n%d %d\n255\n", scene->width, scene->height);

    for (int y = 0; y < scene->height; y++) {
        for (int x = 0; x < scene->width; x++) {
            t_vec3 pixel = vec3_add(view.pixel00,
                vec3_add(vec3_scale(view.pixel_delta_u, x),
                         vec3_scale(view.pixel_delta_v, scene->height - 1 - y)));
            t_vec3 ray_dir = vec3_normalize(vec3_sub(pixel, scene->camera.P));
            t_color color = TraceRayWithLighting(scene->camera.P, ray_dir, 1.0, DBL_MAX, scene);
            fprintf(f, "%d %d %d ", color.r, color.g, color.b);
        }
        fprintf(f, "\n");
    }
}
