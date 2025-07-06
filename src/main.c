#include "../inc/rt.h"
#include "../mlx/mlx.h"

// Global variables for MLX
void *mlx_ptr;
void *win_ptr;
void *img_ptr;
char *img_data;
int img_width = 800, img_height = 600;
int bits_per_pixel, size_line, endian;

// Scene data (moved to global for access in event handlers)
t_camera camera;
t_sphere scene[4];
t_cylinder cylinders[2];
t_plane plane;
t_ambient_light ambient;
t_point_light lights[2];

// Function to convert color to MLX format
int color_to_mlx(t_color color) {
    return (color.r << 16) | (color.g << 8) | color.b;
}

// Function to render scene to MLX image
void render_to_mlx_image() {
    t_color background = {0, 0, 0};
    t_camera_view view = setup_camera(camera, img_width, img_height);

    for (int y = 0; y < img_height; y++) {
        for (int x = 0; x < img_width; x++) {
            t_vec3 pixel = vec3_add(view.pixel00,
                vec3_add(vec3_scale(view.pixel_delta_u, x),
                         vec3_scale(view.pixel_delta_v, img_height - 1 - y)));
            t_vec3 ray_dir = vec3_normalize(vec3_sub(pixel, camera.P));
            t_color color = TraceRayWithLighting(camera.P, ray_dir, 1.0, DBL_MAX,
                                                scene, 4, cylinders, 2, &plane, 1,
                                                ambient, lights, 2, background);

            // Convert color to MLX format and put pixel
            int mlx_color = color_to_mlx(color);
            mlx_pixel_put(mlx_ptr, win_ptr, x, y, mlx_color);
        }
    }
}

// Key hook function
int key_hook(int keycode, void *param) {
    (void)param;
    if (keycode == 65307) { // ESC key
        mlx_destroy_window(mlx_ptr, win_ptr);
        mlx_destroy_display(mlx_ptr);
        free(mlx_ptr);
        exit(0);
    }
    return 0;
}

// Close window hook function
int close_hook(void *param) {
    (void)param;
    mlx_destroy_window(mlx_ptr, win_ptr);
    mlx_destroy_display(mlx_ptr);
    free(mlx_ptr);
    exit(0);
}

int main() {
    // Initialize MLX
    mlx_ptr = mlx_init();
    if (!mlx_ptr) {
        printf("Error: Failed to initialize MLX\n");
        return 1;
    }

    // Create window
    win_ptr = mlx_new_window(mlx_ptr, img_width, img_height, "Ray Tracer");
    if (!win_ptr) {
        printf("Error: Failed to create window\n");
        mlx_destroy_display(mlx_ptr);
        free(mlx_ptr);
        return 1;
    }

    // Setup camera
    camera = (t_camera){
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

    // Setup scene objects
    scene[0] = (t_sphere){ .center = {0, -1, 3}, .radius = 1, .material = red_material };
    scene[1] = (t_sphere){ .center = {2, 2, 4},  .radius = 1, .material = blue_material };
    scene[2] = (t_sphere){ .center = {-2, 3, 4}, .radius = 1, .material = green_material };
    scene[3] = (t_sphere){ .center = {0, -5001, 0}, .radius = 5000, .material = yellow_material }; // ground

    // Setup cylinders
    cylinders[0] = (t_cylinder){
        .center = {0, 0, 5},
        .axis = vec3_normalize(vec3_create(0, 1, 0)), // vertical cylinder
        .radius = 0.5,
        .height = 2.0,
        .material = magenta_material
    };
    cylinders[1] = (t_cylinder){
        .center = {3, 0, 4},
        .axis = vec3_normalize(vec3_create(1, 0, 0)), // horizontal cylinder
        .radius = 0.3,
        .height = 1.5,
        .material = cyan_material
    };

    // Setup plane
    plane = (t_plane){
        .point = {0, 0, 8},
        .normal = vec3_normalize(vec3_create(0, 0, -1)), // facing camera
        .material = cyan_material
    };

    // Setup lighting
    ambient = (t_ambient_light){
        .intensity = 0.3,
        .color = {255, 255, 255} // white ambient light
    };

    lights[0] = (t_point_light){
        .position = {2, 3, -2},
        .intensity = 1.0,
        .color = {255, 255, 255} // white point light
    };
    lights[1] = (t_point_light){
        .position = {-2, 2, 2},
        .intensity = 0.8,
        .color = {255, 0, 0} // warm light
    };

    // Render scene to window
    printf("Rendering scene to window...\n");
    render_to_mlx_image();
    printf("Rendering complete! Press ESC to exit.\n");

    // Set up event hooks
    mlx_key_hook(win_ptr, key_hook, NULL);
    mlx_hook(win_ptr, 17, 0, close_hook, NULL); // 17 is the close button event

    // Start the event loop
    mlx_loop(mlx_ptr);

    return 0;
}
