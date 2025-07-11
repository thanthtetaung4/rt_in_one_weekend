/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taung <taung@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 14:20:53 by taung             #+#    #+#             */
/*   Updated: 2025/07/11 14:22:16 by taung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	print_ambient(t_ambient_light amb)
{
	printf("ambient : ratio - %f, ", amb.intensity);
	print_rgb(amb.color);
	printf("\n");
}

int	print_2d_array(char **arr)
{
	int	i;

	i = 0;
	while (arr && arr[i])
	{
		printf("\t%s\n", arr[i]);
		i++;
	}
	return (1);
}

void	print_camera(t_camera camera)
{
	printf("camera : ");
	print_xyz(camera.p);
	printf(", ");
	print_xyz(camera.d);
	printf(", fov - %f\n", camera.fov);
}

int	print_data(t_data data)
{
	printf("Successfully parsed data 🎉🎉\n");
	printf("================== Data Start =================\n");
	print_ambient(data.scene->ambient);
	print_camera(data.scene->camera);
	print_l(data.scene->lights, data.scene->num_lights);
	print_sp(data.scene->spheres, data.scene->num_spheres);
	print_cy(data.scene->cylinders, data.scene->num_cylinders);
	print_pl(data.scene->planes, data.scene->num_planes);
	printf("================== Data End =================\n");
	return (10);
}
