#include "../inc/rt.h"

// Scene with 4 black planes forming a box and objects inside
void setup_box_scene(t_sphere **spheres, int *num_spheres,
                     t_cylinder **cylinders, int num_cylinders,
                     t_plane **planes, int *num_planes,
                     t_ambient_light *ambient,
                     t_point_light **lights, int *num_lights) {

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
        .ambient = 0.2,
        .diffuse = 0.7,
        .specular = 0.4,
        .shininess = 60
    };

    t_material black_material = {
        .color = {20, 20, 20},  // Very dark gray, not pure black
        .ambient = 0.1,
        .diffuse = 0.3,
        .specular = 0.1,
        .shininess = 10
    };

    // Allocate memory for objects
    *spheres = malloc(3 * sizeof(t_sphere));
    *cylinders = malloc(2 * sizeof(t_cylinder));
    *planes = malloc(4 * sizeof(t_plane));
    *lights = malloc(2 * sizeof(t_point_light));

    // Set counts
    *num_spheres = 3;
    *num_planes = 4;
    *num_lights = 2;

    // Setup spheres
    (*spheres)[0] = (t_sphere){
        .center = {0, 0, 2},
        .radius = 0.8,
        .material = red_material
    };

    (*spheres)[1] = (t_sphere){
        .center = {-1.5, 0, 1},
        .radius = 0.6,
        .material = blue_material
    };

    (*spheres)[2] = (t_sphere){
        .center = {1.5, 0, 1},
        .radius = 0.6,
        .material = green_material
    };

    // Setup cylinders
    (*cylinders)[0] = (t_cylinder){
        .center = {0, -0.5, 0},
        .axis = vec3_normalize(vec3_create(0, 1, 0)), // vertical
        .radius = 0.4,
        .height = 1.5,
        .material = yellow_material
    };

    (*cylinders)[1] = (t_cylinder){
        .center = {0, 0.5, 0},
        .axis = vec3_normalize(vec3_create(1, 0, 0)), // horizontal
        .radius = 0.3,
        .height = 2.0,
        .material = yellow_material
    };

    // Setup 4 black planes forming a box
    // Left plane
    (*planes)[0] = (t_plane){
        .point = {-3, 0, 0},
        .normal = vec3_normalize(vec3_create(1, 0, 0)), // facing right
        .material = black_material
    };

    // Right plane
    (*planes)[1] = (t_plane){
        .point = {3, 0, 0},
        .normal = vec3_normalize(vec3_create(-1, 0, 0)), // facing left
        .material = black_material
    };

    // Top plane
    (*planes)[2] = (t_plane){
        .point = {0, 3, 0},
        .normal = vec3_normalize(vec3_create(0, -1, 0)), // facing down
        .material = black_material
    };

    // Bottom plane
    (*planes)[3] = (t_plane){
        .point = {0, -3, 0},
        .normal = vec3_normalize(vec3_create(0, 1, 0)), // facing up
        .material = black_material
    };

    // Setup lighting
    *ambient = (t_ambient_light){
        .intensity = 0.2,
        .color = {255, 255, 255}
    };

    (*lights)[0] = (t_point_light){
        .position = {0, 2, -2},
        .intensity = 1.0,
        .color = {255, 255, 255}
    };

    (*lights)[1] = (t_point_light){
        .position = {2, 0, 2},
        .intensity = 0.8,
        .color = {255, 255, 255}
    };
}

// Function to free scene memory
void free_scene(t_sphere *spheres, t_cylinder *cylinders,
                t_plane *planes, t_point_light *lights) {
    free(spheres);
    free(cylinders);
    free(planes);
    free(lights);
}
