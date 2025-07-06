#include "../inc/rt.h"
#include "../mlx/mlx.h"

// Global variables for MLX
void *mlx_ptr;
void *win_ptr;
void *img_ptr;
char *img_data;
int bits_per_pixel, size_line, endian;

// Scene data (moved to global for access in event handlers)
t_scene *scene;

// Function to convert color to MLX format
int color_to_mlx(t_color color) {
    return (color.r << 16) | (color.g << 8) | color.b;
}

// Function to render scene to MLX image
void render_to_mlx_image() {
    t_camera_view view = setup_camera(scene->camera, scene->width, scene->height);

    for (int y = 0; y < scene->height; y++) {
        for (int x = 0; x < scene->width; x++) {
            t_vec3 pixel = vec3_add(view.pixel00,
                vec3_add(vec3_scale(view.pixel_delta_u, x),
                         vec3_scale(view.pixel_delta_v, scene->height - 1 - y)));
            t_vec3 ray_dir = vec3_normalize(vec3_sub(pixel, scene->camera.P));
            t_color color = TraceRayWithLighting(scene->camera.P, ray_dir, 1.0, DBL_MAX, scene);

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
        free_scene(scene);
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
    free_scene(scene);
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

    // Create scene
    scene = create_scene();
    if (!scene) {
        printf("Error: Failed to create scene\n");
        mlx_destroy_display(mlx_ptr);
        free(mlx_ptr);
        return 1;
    }

    // Setup box scene
    setup_box_scene(scene);

    // Create window
    win_ptr = mlx_new_window(mlx_ptr, scene->width, scene->height, "Box Scene - Ray Tracer");
    if (!win_ptr) {
        printf("Error: Failed to create window\n");
        free_scene(scene);
        mlx_destroy_display(mlx_ptr);
        free(mlx_ptr);
        return 1;
    }

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
