/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taung <taung@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 17:36:57 by taung             #+#    #+#             */
/*   Updated: 2025/07/14 19:34:52 by taung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int	alloc_sp(t_data *data)
{
	data->scene->spheres = (t_sphere *)ft_calloc(data->scene->num_spheres,
			sizeof(t_sphere));
	if (!data->scene->spheres)
		return (0);
	return (1);
}

int	alloc_l(t_data *data)
{
	data->scene->lights = (t_point_light *)ft_calloc(data->scene->num_lights,
			sizeof(t_point_light));
	if (!data->scene->lights)
		return (0);
	return (1);
}

int	alloc_cy(t_data *data)
{
	data->scene->cylinders = (t_cylinder *)ft_calloc(data->scene->num_cylinders,
			sizeof(t_cylinder));
	if (!data->scene->cylinders)
		return (0);
	return (1);
}

int	alloc_pl(t_data *data)
{
	data->scene->planes = (t_plane *)ft_calloc(data->scene->num_planes,
			sizeof(t_plane));
	if (!data->scene->planes)
		return (0);
	return (1);
}

int	init_scene(char *filename, t_data *data)
{
	if (check_objs(filename))
	{
		count_onl(filename, data);
		if (data->scene->num_lights > 0)
			if (!alloc_l(data))
				return (0);
		if (data->scene->num_spheres > 0)
			if (!alloc_sp(data))
				return (0);
		if (data->scene->num_planes > 0)
			if (!alloc_pl(data))
				return (0);
		if (data->scene->num_cylinders > 0)
			if (!alloc_cy(data))
				return (0);
		return (1);
	}
	return (0);
}
