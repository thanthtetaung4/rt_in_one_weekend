/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_obj.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoo <aoo@student.42singapore.sg>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 14:21:45 by taung             #+#    #+#             */
/*   Updated: 2025/07/12 03:28:44 by aoo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	print_pl(t_plane *planes, int num_planes)
{
	int	i;

	i = 0;
	while (i < num_planes)
	{
		printf("plane : ");
		print_xyz(planes[i].point);
		printf(", ");
		print_xyz(planes[i].normal);
		printf(", ");
		print_rgb(planes[i].material.color);
		print_mat(planes[i].material);
		printf("\n");
		i++;
	}
}

void	print_sp(t_sphere *spheres, int sp_count)
{
	int	i;

	i = 0;
	while (i < sp_count)
	{
		printf("sphere : ");
		print_xyz(spheres[i].center);
		printf(", radius - %f, ", spheres[i].radius);
		print_rgb(spheres[i].material.color);
		print_mat(spheres[i].material);
		printf("\n");
		i++;
	}
}

void	print_cy(t_cylinder *cylinders, int num_cylinders)
{
	int	i;

	i = 0;
	while (i < num_cylinders)
	{
		printf("cylinder : ");
		print_xyz(cylinders[i].center);
		printf(", ");
		print_xyz(cylinders[i].axis);
		printf(", radius - %f, height - %f, ", cylinders[i].radius,
			cylinders[i].half_height * 2.0);
		print_rgb(cylinders[i].material.color);
		print_mat(cylinders[i].material);
		printf("\n");
		i++;
	}
}

void	print_l(t_point_light *lights, int num_lights)
{
	int	i;

	i = 0;
	while (i < num_lights)
	{
		printf("light : ");
		print_xyz(lights[i].position);
		printf(", intensity - %f, ", lights[i].intensity);
		print_rgb(lights[i].color);
		printf("\n");
		i++;
	}
}
