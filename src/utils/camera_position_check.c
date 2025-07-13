/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_position_check.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taung <taung@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 02:49:40 by taung             #+#    #+#             */
/*   Updated: 2025/07/14 03:40:19 by taung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static int	is_camera_in_sphere(const t_scene *scene, t_camera camera)
{
	int		i;
	double	dist;

	i = 0;
	while (i < scene->num_spheres)
	{
		dist = vec3_length(vec3_sub(camera.p, scene->spheres[i].center));
		if (dist < scene->spheres[i].radius)
			return (1);
		i++;
	}
	return (0);
}

static int	is_camera_in_cylinder(const t_scene *scene, t_camera camera)
{
	int		i;
	t_vec3	to_cam;
	double	proj;
	t_vec3	radial;

	i = 0;
	while (i < scene->num_cylinders)
	{
		to_cam = vec3_sub(camera.p, scene->cylinders[i].center);
		proj = vec3_dot(to_cam, scene->cylinders[i].axis);
		if (proj < -scene->cylinders[i].half_height / 2.0
			|| proj > scene->cylinders[i].half_height / 2.0)
		{
			i++;
			continue ;
		}
		radial = vec3_sub(to_cam, vec3_scale(scene->cylinders[i].axis, proj));
		if (vec3_length(radial) < scene->cylinders[i].radius)
			return (1);
		i++;
	}
	return (0);
}

int	check_c_pos(const t_scene *scene, t_camera camera, t_point_light light)
{
	int	i;

	i = 0;
	while (i < scene->num_planes)
		if (is_light_on_plane(light, scene->planes[i++]))
			return (1);
	if (is_camera_in_sphere(scene, camera))
		return (0);
	if (is_camera_in_cylinder(scene, camera))
		return (0);
	return (1);
}
