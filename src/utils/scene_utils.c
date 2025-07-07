#include "../../inc/rt.h"

t_scene *create_scene(void) {
    t_scene *scene = malloc(sizeof(t_scene));
    if (!scene) {
        printf("Error: Failed to allocate scene\n");
        return NULL;
    }

    // Initialize with default values
    scene->spheres = NULL;
    scene->num_spheres = 0;
    scene->cylinders = NULL;
    scene->num_cylinders = 0;
    scene->planes = NULL;
    scene->num_planes = 0;
    scene->lights = NULL;
    scene->num_lights = 0;
    scene->background = (t_color){0, 0, 0};
    scene->width = 800;
    scene->height = 600;

    return scene;
}

void free_scene(t_scene *scene) {
    if (!scene) return;

    if (scene->spheres) {
        free(scene->spheres);
        scene->spheres = NULL;
    }
    if (scene->cylinders) {
        free(scene->cylinders);
        scene->cylinders = NULL;
    }
    if (scene->planes) {
        free(scene->planes);
        scene->planes = NULL;
    }
    if (scene->lights) {
        free(scene->lights);
        scene->lights = NULL;
    }

    free(scene);
}

void setup_regular_scene(t_scene *scene) {
    if (!scene) return;

    // Setup camera
    scene->camera = (t_camera){
        .P = vec3_create(0, 0, -1),
        .D = vec3_create(0, 0, 1),
        .fov = PI / 4 // 45 degrees in radians
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

    // Setup spheres
    scene->num_spheres = 4;
    scene->spheres = malloc(scene->num_spheres * sizeof(t_sphere));
    scene->spheres[0] = (t_sphere){ .center = {0, -1, 3}, .radius = 1, .material = red_material };
    scene->spheres[1] = (t_sphere){ .center = {2, 2, 4},  .radius = 1, .material = blue_material };
    scene->spheres[2] = (t_sphere){ .center = {-2, 3, 4}, .radius = 1, .material = green_material };
    scene->spheres[3] = (t_sphere){ .center = {0, -5001, 0}, .radius = 5000, .material = yellow_material }; // ground

    // Setup cylinders
    scene->num_cylinders = 2;
    scene->cylinders = malloc(scene->num_cylinders * sizeof(t_cylinder));
    scene->cylinders[0] = (t_cylinder){
        .center = {0, 0, 5},
        .axis = vec3_normalize(vec3_create(0, 1, 0)), // vertical cylinder
        .radius = 0.5,
        .height = 2.0,
        .material = magenta_material
    };
    scene->cylinders[1] = (t_cylinder){
        .center = {3, 0, 4},
        .axis = vec3_normalize(vec3_create(1, 0, 0)), // horizontal cylinder
        .radius = 0.3,
        .height = 1.5,
        .material = cyan_material
    };

    // Setup planes
    scene->num_planes = 1;
    scene->planes = malloc(scene->num_planes * sizeof(t_plane));
    scene->planes[0] = (t_plane){
        .point = {0, 0, 8},
        .normal = vec3_normalize(vec3_create(0, 0, -1)), // facing camera
        .material = cyan_material
    };

    // Setup lighting
    scene->ambient = (t_ambient_light){
        .intensity = 0.3,
        .color = {255, 255, 255} // white ambient light
    };

    scene->num_lights = 2;
    scene->lights = malloc(scene->num_lights * sizeof(t_point_light));
    scene->lights[0] = (t_point_light){
        .position = {2, 3, -2},
        .intensity = 1.0,
        .color = {255, 255, 255} // white point light
    };
    scene->lights[1] = (t_point_light){
        .position = {-2, 2, 2},
        .intensity = 0.8,
        .color = {255, 0, 0} // warm light
    };
}

void setup_box_scene(t_scene *scene) {
    if (!scene) return;

    // Setup camera for box scene - positioned to look into the box
    scene->camera = (t_camera){
        .P = vec3_create(0, 0, -4),  // Position camera outside the box
        .D = vec3_create(0, 0, 1),   // Look into the box
        .fov = PI / 3                 // 60 degrees field of view
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

    // Setup spheres
    scene->num_spheres = 3;
    scene->spheres = malloc(scene->num_spheres * sizeof(t_sphere));
    scene->spheres[0] = (t_sphere){
        .center = {0, 0, 2},
        .radius = 0.8,
        .material = red_material
    };
    scene->spheres[1] = (t_sphere){
        .center = {-1.5, 0, 1},
        .radius = 0.6,
        .material = blue_material
    };
    scene->spheres[2] = (t_sphere){
        .center = {1.5, 0, 1},
        .radius = 0.6,
        .material = green_material
    };

    // Setup cylinders
    scene->num_cylinders = 2;
    scene->cylinders = malloc(scene->num_cylinders * sizeof(t_cylinder));
    scene->cylinders[0] = (t_cylinder){
        .center = {0, -0.5, 0},
        .axis = vec3_normalize(vec3_create(0, 1, 0)), // vertical
        .radius = 0.4,
        .height = 1.5,
        .material = yellow_material
    };
    scene->cylinders[1] = (t_cylinder){
        .center = {0, 0.5, 0},
        .axis = vec3_normalize(vec3_create(1, 0, 0)), // horizontal
        .radius = 0.3,
        .height = 2.0,
        .material = yellow_material
    };

    // Setup 4 black planes forming a box
    scene->num_planes = 4;
    scene->planes = malloc(scene->num_planes * sizeof(t_plane));

    // Left plane
    scene->planes[0] = (t_plane){
        .point = {-3, 0, 0},
        .normal = vec3_normalize(vec3_create(1, 0, 0)), // facing right
        .material = black_material
    };

    // Right plane
    scene->planes[1] = (t_plane){
        .point = {3, 0, 0},
        .normal = vec3_normalize(vec3_create(-1, 0, 0)), // facing left
        .material = black_material
    };

    // Top plane
    scene->planes[2] = (t_plane){
        .point = {0, 3, 0},
        .normal = vec3_normalize(vec3_create(0, -1, 0)), // facing down
        .material = black_material
    };

    // Bottom plane
    scene->planes[3] = (t_plane){
        .point = {0, -3, 0},
        .normal = vec3_normalize(vec3_create(0, 1, 0)), // facing up
        .material = black_material
    };

    // Setup lighting
    scene->ambient = (t_ambient_light){
        .intensity = 0.2,
        .color = {255, 255, 255}
    };

    scene->num_lights = 2;
    scene->lights = malloc(scene->num_lights * sizeof(t_point_light));
    scene->lights[0] = (t_point_light){
        .position = {0, 2, -2},
        .intensity = 1.0,
        .color = {255, 255, 255}
    };
    scene->lights[1] = (t_point_light){
        .position = {2, 0, 2},
        .intensity = 0.8,
        .color = {255, 255, 255}
    };
}

void setup_pipe_scene(t_scene *scene) {
    if (!scene) return;

    // Setup camera inside the pipe - positioned at the center looking forward
    scene->camera = (t_camera){
        .P = vec3_create(0, 0, 0),  // Camera at the center of the pipe
        .D = vec3_create(0, 0, 1),  // Looking forward along the pipe
        .fov = PI / 4                // 45 degrees field of view
    };

    // Define materials
    t_material pipe_material = {
        .color = {100, 100, 100},  // Gray pipe material
        .ambient = 0.3,
        .diffuse = 0.5,
        .specular = 0.2,
        .shininess = 20
    };

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

    t_material purple_material = {
        .color = {128, 0, 128},
        .ambient = 0.2,
        .diffuse = 0.6,
        .specular = 0.4,
        .shininess = 40
    };

    // Setup the infinite pipe (large cylinder)
    scene->num_cylinders = 1;
    scene->cylinders = malloc(scene->num_cylinders * sizeof(t_cylinder));
    scene->cylinders[0] = (t_cylinder){
        .center = {0, 0, 0},  // Pipe centered at origin
        .axis = vec3_normalize(vec3_create(0, 0, 1)), // Pipe extends along Z-axis
        .radius = 5.0,  // Large radius for pipe
        .height = 100.0, // Very tall to simulate infinite pipe
        .material = pipe_material
    };

    // Setup small spheres floating inside the pipe
    scene->num_spheres = 5;
    scene->spheres = malloc(scene->num_spheres * sizeof(t_sphere));
    scene->spheres[0] = (t_sphere){
        .center = {1.5, 1.0, 3},
        .radius = 0.4,
        .material = red_material
    };
    scene->spheres[1] = (t_sphere){
        .center = {-1.2, 0.8, 5},
        .radius = 0.3,
        .material = blue_material
    };
    scene->spheres[2] = (t_sphere){
        .center = {0.8, -1.5, 7},
        .radius = 0.5,
        .material = green_material
    };
    scene->spheres[3] = (t_sphere){
        .center = {-0.5, -0.8, 9},
        .radius = 0.2,
        .material = yellow_material
    };
    scene->spheres[4] = (t_sphere){
        .center = {2.0, -0.3, 11},
        .radius = 0.35,
        .material = purple_material
    };

    // Setup small cylinders floating inside the pipe
    scene->num_cylinders = 3;  // Update to include small cylinders
    scene->cylinders = realloc(scene->cylinders, scene->num_cylinders * sizeof(t_cylinder));

    // Keep the pipe as the first cylinder
    scene->cylinders[0] = (t_cylinder){
        .center = {0, 0, 0},
        .axis = vec3_normalize(vec3_create(0, 0, 1)),
        .radius = 2.0,
        .height = 100.0,
        .material = pipe_material
    };

    // Add small floating cylinders
    scene->cylinders[1] = (t_cylinder){
        .center = {0.5, 1.8, 4},
        .axis = vec3_normalize(vec3_create(1, 0, 0)), // horizontal
        .radius = 0.2,
        .height = 0.8,
        .material = yellow_material
    };
    scene->cylinders[2] = (t_cylinder){
        .center = {-1.8, -0.5, 6},
        .axis = vec3_normalize(vec3_create(0, 1, 0)), // vertical
        .radius = 0.15,
        .height = 0.6,
        .material = purple_material
    };

    // No planes needed for pipe scene
    scene->num_planes = 0;
    scene->planes = NULL;

    // Setup lighting - multiple lights to illuminate the pipe interior
    scene->ambient = (t_ambient_light){
        .intensity = 0.4,  // Higher ambient for pipe interior
        .color = {255, 255, 255}
    };

    scene->num_lights = 3;
    scene->lights = malloc(scene->num_lights * sizeof(t_point_light));
    scene->lights[0] = (t_point_light){
        .position = {0, 0, -2},  // Light behind camera
        .intensity = 1.0,
        .color = {255, 255, 255}
    };
    scene->lights[1] = (t_point_light){
        .position = {2, 2, 8},  // Light ahead and to the side
        .intensity = 0.8,
        .color = {255, 255, 255}
    };
    scene->lights[2] = (t_point_light){
        .position = {-2, -2, 12},  // Light further ahead
        .intensity = 0.6,
        .color = {255, 200, 200}  // Warm light
    };
}
