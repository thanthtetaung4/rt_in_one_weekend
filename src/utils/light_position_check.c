/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_position_check.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taung <taung@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 20:09:45 by taung             #+#    #+#             */
/*   Updated: 2025/07/14 02:16:26 by taung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int	is_light_in_sphere(t_point_light light, t_sphere sphere)
{
	double	dist;

	dist = vec3_length(vec3_sub(light.position, sphere.center));
	return (dist < sphere.radius);
}

int	is_light_in_cylinder(t_point_light light, t_cylinder cylinder)
{
	t_vec3	to_light;
	double	proj;
	t_vec3	radial;

	to_light = vec3_sub(light.position, cylinder.center);
	proj = vec3_dot(to_light, cylinder.axis);
	if (proj < -cylinder.half_height || proj > cylinder.half_height)
		return (0);
	radial = vec3_sub(to_light, vec3_scale(cylinder.axis, proj));
	return (vec3_length(radial) < cylinder.radius);
}

int	is_light_on_plane(t_point_light light, t_plane plane)
{
	t_vec3	to_light;

	to_light = vec3_sub(light.position, plane.point);
	return (fabs(vec3_dot(to_light, plane.normal)) < 1e-6);
}

int	check_light_positions(const t_scene *scene, t_point_light light)
{
	int	j;

	j = 0;
	while (j < scene->num_spheres)
		if (is_light_in_sphere(light, scene->spheres[j++]))
			return (0);
	j = 0;
	while (j < scene->num_cylinders)
		if (is_light_in_cylinder(light, scene->cylinders[j++]))
			return (0);
	j = 0;
	while (j < scene->num_planes)
		if (is_light_on_plane(light, scene->planes[j++]))
			return (0);
	return (1);
}
