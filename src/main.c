#include "../inc/rt.h"

int main() {
    int width = 800, height = 600;
    t_camera camera = {
        .P = vec3_create(0, 0, -1),
        .D = vec3_create(0, 0, 1),
        .fov = PI / 4 // 60 degrees in radians
    };

    // Define materials
    t_material red_material = {
        .color = {255, 0, 0},
        .ambient = 0.2,
        .diffuse = 0.7,
        .specular = 0.3,
        .shininess = 50
    };

    t_material blue_material = {
        .color = {0, 0, 255},
        .ambient = 0.2,
        .diffuse = 0.8,
        .specular = 0.5,
        .shininess = 100
    };

    t_material green_material = {
        .color = {0, 255, 0},
        .ambient = 0.2,
        .diffuse = 0.6,
        .specular = 0.4,
        .shininess = 30
    };

    t_material yellow_material = {
        .color = {255, 255, 0},
        .ambient = 0.3,
        .diffuse = 0.5,
        .specular = 0.2,
        .shininess = 10
    };

    t_material magenta_material = {
        .color = {255, 0, 255},
        .ambient = 0.2,
        .diffuse = 0.7,
        .specular = 0.6,
        .shininess = 80
    };

    t_material cyan_material = {
        .color = {0, 255, 255},
        .ambient = 0.2,
        .diffuse = 0.6,
        .specular = 0.4,
        .shininess = 40
    };

    t_sphere scene[] = {
        { .center = {0, -1, 3}, .radius = 1, .material = red_material },
        { .center = {2, 2, 4},  .radius = 1, .material = blue_material },
        { .center = {-2, 3, 4}, .radius = 1, .material = green_material },
        { .center = {0, -5001, 0}, .radius = 5000, .material = yellow_material } // ground
    };

    // Add cylinders
    t_cylinder cylinders[] = {
        {
            .center = {0, 0, 5},
            .axis = vec3_normalize(vec3_create(0, 1, 0)), // vertical cylinder
            .radius = 0.5,
            .height = 2.0,
            .material = magenta_material
        },
        {
            .center = {3, 0, 4},
            .axis = vec3_normalize(vec3_create(1, 0, 0)), // horizontal cylinder
            .radius = 0.3,
            .height = 1.5,
            .material = cyan_material
        }
    };

    // Add a plane
    t_plane plane = {
        .point = {0, 0, 8},
        .normal = vec3_normalize(vec3_create(0, 0, -1)), // facing camera
        .material = cyan_material
    };

    // Setup lighting
    t_ambient_light ambient = {
        .intensity = 0.3,
        .color = {255, 255, 255} // white ambient light
    };

    t_point_light lights[] = {
        {
            .position = {2, 3, -2},
            .intensity = 1.0,
            .color = {255, 255, 255} // white point light
        },
        {
            .position = {-2, 2, 2},
            .intensity = 0.8,
            .color = {255, 0, 0} // warm light
        }
    };

    FILE *f = fopen("image.ppm", "w");
    if (!f) {
        perror("Cannot open output file");
        return 1;
    }

    // Render scene with lighting
    render_scene_with_lighting(f, camera, scene, 4, cylinders, 2, &plane, 1,
                              ambient, lights, 2, width, height);
    fclose(f);
    printf("Rendered image.ppm with lighting\n");
    return 0;
}
