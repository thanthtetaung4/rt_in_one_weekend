#include "rt.h"

// Function to convert color to MLX format
static int	color_to_mlx(t_color color)
{
	return ((color.r << 16) | (color.g << 8) | color.b);
}

static void	render_to_mlx_image(t_data *data)
{
	t_camera_view	view;
	t_vec3			pixel;
	t_vec3			ray_dir;
	t_color			color;
	int				mlx_color;
	int				y;
	int				x;

	printf("h: %d, w: %d\n", data->scene->width, data->scene->height);
	view = setup_camera(data->scene->camera, data->scene->width, data->scene->height); // (scene);
	y = 0;
	while (y < data->scene->height)
	{
		x = 0;
		while (x < data->scene->width)
		{
			pixel = vec3_add(view.pixel00,
					vec3_add(vec3_scale(view.pixel_delta_u, x),
						vec3_scale(view.pixel_delta_v, data->scene->height - 1 - y)));
			ray_dir = vec3_normalize(vec3_sub(pixel, data->scene->camera.P));
			color = TraceRay(data->scene->camera.P, ray_dir, 1.0, DBL_MAX, data->scene);
			print_rgb(color);
			printf("\n");
			mlx_color = color_to_mlx(color);
			mlx_pixel_put(data->mlx, data->mlx_win, x, y, mlx_color);
			x++;
		}
		y++;
	}
}

static int	close_hook(t_data *data)
{
	if (data->mlx && data->mlx_win)
	{	mlx_destroy_window(data->mlx, data->mlx_win);
		mlx_destroy_display(data->mlx);
		free(data->mlx);
		exit(0);
	}
	return (0);
}

static int	key_hook(int keycode, void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (keycode == 65307)
		close_hook(data);
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	data;

	ft_bzero(&data, sizeof(t_data));
	data.scene = create_scene();
	if (!data.scene)
		return(print_error("Error: Failed to create scene\n"));
	// printf("h: %d, w: %d\n", data.scene->height, data.scene->width);

	// parser(argv[1], &data);
	data.mlx = mlx_init();
	if (!data.mlx)
		return (print_error("Error: Failed to initialize MLX\n"));  // need scence_free
	// if (!parse_rt_file(argv[1], scene))
	if (!parser(argv[1], &data))
	{

		free_scene(data.scene);
		mlx_destroy_display(data.mlx);
		free(data.mlx);
		return (print_error("Error: Failed to parse input file\n"));
	}
	data.mlx_win = mlx_new_window(data.mlx, data.scene->width, data.scene->height,
			"Ray Tracer");
	if (!data.mlx_win)
	{
		free_scene(data.scene);
		mlx_destroy_display(data.mlx);
		free(data.mlx);
		return (print_error("Error: Failed to create window\n"));
	}
	printf("Rendering scene to window...\n");
	render_to_mlx_image(&data);
	printf("Rendering complete! Press ESC to exit.\n");
	mlx_key_hook(data.mlx_win, key_hook, &data);
	mlx_hook(data.mlx_win, 17, 0, close_hook, &data);
	mlx_loop(data.mlx);
	return (0);
}
