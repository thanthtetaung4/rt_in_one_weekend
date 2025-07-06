#include "../inc/rt.h"

int main() {
    int width = 800, height = 600;

    // Camera positioned to look into the box
    t_camera camera = {
        .P = vec3_create(0, 0, -4),  // Position camera outside the box
        .D = vec3_create(0, 0, 1),   // Look into the box
        .fov = PI / 3                 // 60 degrees field of view
    };

    // Scene objects
    t_sphere *spheres;
    t_cylinder *cylinders;
    t_plane *planes;
    t_point_light *lights;
    t_ambient_light ambient;
    int num_spheres, num_cylinders = 2, num_planes, num_lights;

    // Setup the box scene
    setup_box_scene(&spheres, &num_spheres, &cylinders, num_cylinders,
                    &planes, &num_planes, &ambient, &lights, &num_lights);

    FILE *f = fopen("box_scene.ppm", "w");
    if (!f) {
        perror("Cannot open output file");
        free_scene(spheres, cylinders, planes, lights);
        return 1;
    }

    // Render the box scene with lighting
    render_scene_with_lighting(f, camera, spheres, num_spheres,
                              cylinders, num_cylinders,
                              planes, num_planes,
                              ambient, lights, num_lights,
                              width, height);

    fclose(f);
    printf("Rendered box_scene.ppm with 4 black planes, 3 spheres, and 2 cylinders\n");

    // Free allocated memory
    free_scene(spheres, cylinders, planes, lights);

    return 0;
}
