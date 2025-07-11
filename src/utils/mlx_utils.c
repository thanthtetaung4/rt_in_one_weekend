/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoo <aoo@student.42singapore.sg>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 05:31:55 by aoo               #+#    #+#             */
/*   Updated: 2025/07/12 05:31:56 by aoo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

// Function to convert color to MLX format
int	color_to_mlx(t_color color)
{
	return ((color.r << 16) | (color.g << 8) | color.b);
}

int	close_hook(t_data *data)
{
	printf("You closed the window!\n");
	free_data(data);
	exit(0);
	return (0);
}

int	key_hook(int keycode, void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (keycode == 65307)
		close_hook(data);
	return (0);
}
