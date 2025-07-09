#include "rt.h"

// Function to convert color to MLX format
static int	color_to_mlx(t_color color)
{
	return ((color.r << 16) | (color.g << 8) | color.b);
}

static void	render_to_mlx_image(t_scene *scene, t_data *data)
{
	t_camera_view	view;
	t_ray			ray;
	t_vec3			pixel;
	int				xy[2];

	ray = init_ray(scene->camera.P, vec3_create(0, 0, 0), 1.0, DBL_MAX);
	view = setup_camera(scene->camera, scene);
	xy[1] = 0;
	while (xy[1] < scene->height)
	{
		xy[0] = 0;
		while (xy[0] < scene->width)
		{
			pixel = vec3_add(view.pixel00,
					vec3_add(vec3_scale(view.pixel_delta_u, xy[0]),
						vec3_scale(view.pixel_delta_v, scene->height - 1
							- xy[1])));
			ray.dir = vec3_normalize(vec3_sub(pixel, scene->camera.P));
			mlx_pixel_put(data->mlx, data->mlx_win, xy[0], xy[1],
				color_to_mlx(TraceRay(ray, scene)));
			xy[0]++;
		}
		xy[1]++;
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
	data.mlx = mlx_init();
	if (!data.mlx)
		return (print_error("Error: Failed to initialize MLX\n"));  // need scence_free
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
	printf("=================== Data Check ===================\n");
	print_data(data);
	printf("=================== Data Check Done ===================\n");
	printf("Rendering scene to window...\n");
	render_to_mlx_image(data.scene, &data);
	printf("Rendering complete! Press ESC to exit.\n");
	mlx_key_hook(data.mlx_win, key_hook, &data);
	mlx_hook(data.mlx_win, 17, 0, close_hook, &data);
	mlx_loop(data.mlx);
	return (0);
}
