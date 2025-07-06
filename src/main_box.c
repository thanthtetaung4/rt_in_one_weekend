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
t_sphere *spheres;
t_cylinder *cylinders;
t_plane *planes;
t_point_light *lights;
t_ambient_light ambient;
int num_spheres, num_cylinders = 2, num_planes, num_lights;

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
                                                spheres, num_spheres,
                                                cylinders, num_cylinders,
                                                planes, num_planes,
                                                ambient, lights, num_lights,
                                                background);

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
        free_scene(spheres, cylinders, planes, lights);
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
    free_scene(spheres, cylinders, planes, lights);
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
    win_ptr = mlx_new_window(mlx_ptr, img_width, img_height, "Box Scene - Ray Tracer");
    if (!win_ptr) {
        printf("Error: Failed to create window\n");
        mlx_destroy_display(mlx_ptr);
        free(mlx_ptr);
        return 1;
    }

    // Camera positioned to look into the box
    camera = (t_camera){
        .P = vec3_create(0, 0, -4),  // Position camera outside the box
        .D = vec3_create(0, 0, 1),   // Look into the box
        .fov = PI / 3                 // 60 degrees field of view
    };

    // Setup the box scene
    setup_box_scene(&spheres, &num_spheres, &cylinders, num_cylinders,
                    &planes, &num_planes, &ambient, &lights, &num_lights);

    // Render scene to window
    printf("Rendering box scene to window...\n");
    render_to_mlx_image();
    printf("Rendering complete! Press ESC to exit.\n");

    // Set up event hooks
    mlx_key_hook(win_ptr, key_hook, NULL);
    mlx_hook(win_ptr, 17, 0, close_hook, NULL); // 17 is the close button event

    // Start the event loop
    mlx_loop(mlx_ptr);

    return 0;
}
