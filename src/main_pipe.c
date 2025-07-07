#include "../inc/rt.h"
#include "../mlx/mlx.h"

void	*mlx_ptr;
void	*win_ptr;
void	*img_ptr;
char	*img_data;
int		bits_per_pixel;
int		size_line;
int		endian;
t_scene	*scene;

// Function to convert color to MLX format
static int	color_to_mlx(t_color color)
{
	return ((color.r << 16) | (color.g << 8) | color.b);
}

// Function to render scene to MLX image
static void	render_to_mlx_image(void)
{
	t_camera_view	view;
	t_vec3			pixel;
	t_vec3			ray_dir;
	t_color			color;
	int				mlx_color;
	int				y;
	int				x;

	view = setup_camera(scene->camera, scene->width, scene->height);
	y = 0;
	while (y < scene->height)
	{
		x = 0;
		while (x < scene->width)
		{
			pixel = vec3_add(view.pixel00,
				vec3_add(vec3_scale(view.pixel_delta_u, x),
					vec3_scale(view.pixel_delta_v, scene->height - 1 - y)));
			ray_dir = vec3_normalize(vec3_sub(pixel, scene->camera.P));
			color = TraceRay(scene->camera.P, ray_dir, 1.0, DBL_MAX, scene);
			mlx_color = color_to_mlx(color);
			mlx_pixel_put(mlx_ptr, win_ptr, x, y, mlx_color);
			x++;
		}
		y++;
	}
}

// Key hook function
static int	key_hook(int keycode, void *param)
{
	(void)param;
	if (keycode == 65307)
	{
		free_scene(scene);
		mlx_destroy_window(mlx_ptr, win_ptr);
		mlx_destroy_display(mlx_ptr);
		free(mlx_ptr);
		exit(0);
	}
	return (0);
}

// Close window hook function
static int	close_hook(void *param)
{
	(void)param;
	free_scene(scene);
	mlx_destroy_window(mlx_ptr, win_ptr);
	mlx_destroy_display(mlx_ptr);
	free(mlx_ptr);
	exit(0);
}

int	main(void)
{
	mlx_ptr = mlx_init();
	if (!mlx_ptr)
	{
		printf("Error: Failed to initialize MLX\n");
		return (1);
	}
	scene = create_scene();
	if (!scene)
	{
		printf("Error: Failed to create scene\n");
		mlx_destroy_display(mlx_ptr);
		free(mlx_ptr);
		return (1);
	}
	setup_pipe_scene(scene);
	win_ptr = mlx_new_window(mlx_ptr, scene->width, scene->height, "Pipe Scene - Ray Tracer");
	if (!win_ptr)
	{
		printf("Error: Failed to create window\n");
		free_scene(scene);
		mlx_destroy_display(mlx_ptr);
		free(mlx_ptr);
		return (1);
	}
	printf("Rendering pipe scene to window...\n");
	render_to_mlx_image();
	printf("Rendering complete! Press ESC to exit.\n");
	mlx_key_hook(win_ptr, key_hook, NULL);
	mlx_hook(win_ptr, 17, 0, close_hook, NULL);
	mlx_loop(mlx_ptr);
	return (0);
}
