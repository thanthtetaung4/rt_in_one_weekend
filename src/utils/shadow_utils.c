/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoo <aoo@student.42singapore.sg>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 18:11:42 by taung             #+#    #+#             */
/*   Updated: 2025/07/12 04:09:19 by aoo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static int	check_sphere_shadows(t_ray shadow_ray, double light_distance,
		t_scene *scene)
{
	int		i;
	double	t1;
	double	t2;

	i = 0;
	while (i < scene->num_spheres)
	{
		intersect_sphere(shadow_ray, scene->spheres[i], &t1, &t2);
		if (t1 > 0.001 && t1 < light_distance)
			return (1);
		if (t2 > 0.001 && t2 < light_distance)
			return (1);
		i++;
	}
	return (0);
}

static int	check_cylinder_shadows(t_ray shadow_ray, double light_distance,
		t_scene *scene)
{
	int		i;
	double	t1;
	double	t2;

	i = 0;
	while (i < scene->num_cylinders)
	{
		intersect_cylinder(shadow_ray, scene->cylinders[i], &t1, &t2);
		if (t1 > 0.001 && t1 < light_distance)
			return (1);
		if (t2 > 0.001 && t2 < light_distance)
			return (1);
		i++;
	}
	return (0);
}

static int	check_plane_shadows(t_ray shadow_ray, double light_distance,
		t_scene *scene)
{
	int		i;
	double	t;

	i = 0;
	while (i < scene->num_planes)
	{
		intersect_plane(shadow_ray, scene->planes[i], &t);
		if (t > 0.001 && t < light_distance)
			return (1);
		i++;
	}
	return (0);
}

int	is_in_shadow(t_vec3 hit_point, t_vec3 light_direction,
		double light_distance, t_scene *scene)
{
	t_ray	shadow_ray;

	ft_bzero(&shadow_ray, sizeof(t_ray));
	shadow_ray.origin = hit_point;
	shadow_ray.dir = light_direction;
	if (check_sphere_shadows(shadow_ray, light_distance, scene))
		return (1);
	if (check_cylinder_shadows(shadow_ray, light_distance, scene))
		return (1);
	if (check_plane_shadows(shadow_ray, light_distance, scene))
		return (1);
	return (0);
}
