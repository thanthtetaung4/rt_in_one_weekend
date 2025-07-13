/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taung <taung@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 05:31:13 by aoo               #+#    #+#             */
/*   Updated: 2025/07/14 02:37:10 by taung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	free_data(t_data *data)
{
	if (data->mlx_win)
		mlx_destroy_window(data->mlx, data->mlx_win);
	if (data->mlx)
	{
		mlx_destroy_display(data->mlx);
		free(data->mlx);
	}
	if (data->scene)
		free_scene(data->scene);
	ft_bzero(data, sizeof(t_data));
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 2)
		return (print_error("Too many arguments\n"));
	ft_bzero(&data, sizeof(t_data));
	if (!create_scene(argv[1], &data))
		return (free_data(&data),
			!print_error("Error: Failed to create scene\n"));
	data.mlx = mlx_init();
	if (!data.mlx)
		return (free_data(&data),
			!print_error("Error: Failed to initialize MLX\n"));
	data.mlx_win = mlx_new_window(data.mlx, WIDTH, HEIGHT, "Ray Tracer");
	if (!data.mlx_win)
		return (free_data(&data),
			!print_error("Error: Failed to create window\n"));
	printf("Rendering scene to window...\n");
	render_to_mlx_image(data.scene, &data);
	printf("Rendering complete! Press ESC to exit.\n");
	mlx_key_hook(data.mlx_win, key_hook, &data);
	mlx_hook(data.mlx_win, 17, 0, close_hook, &data);
	mlx_loop(data.mlx);
	return (0);
}
