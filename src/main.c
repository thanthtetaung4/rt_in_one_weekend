#include "../inc/rt.h"

int main() {
    int width = 800, height = 600;
    t_camera camera = {
        .P = vec3_create(0, 0, -1),
        .D = vec3_create(0, 0, 1),
        .fov = PI / 4 // 60 degrees in radians
    };

    t_sphere scene[] = {
        { .center = {0, -1, 3}, .radius = 1, .color = {255, 0, 0} },
        { .center = {2, 2, 4},  .radius = 1, .color = {0, 0, 255} },
        { .center = {-2, 3, 4}, .radius = 1, .color = {0, 255, 0} },
        { .center = {0, -5001, 0}, .radius = 5000, .color = {255, 255, 0} } // ground
    };

    FILE *f = fopen("image.ppm", "w");
    if (!f) {
        perror("Cannot open output file");
        return 1;
    }

    render_scene(f, camera, scene, 4, width, height);
    fclose(f);
    printf("Rendered image.ppm\n");
    return 0;
}
