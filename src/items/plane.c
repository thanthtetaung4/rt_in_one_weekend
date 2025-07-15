/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoo <aoo@student.42singapore.sg>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 05:20:59 by aoo               #+#    #+#             */
/*   Updated: 2025/07/14 13:53:03 by aoo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static t_hit	get_plane_hit(t_ray ray, t_plane plane, double t)
{
	t_hit	hit;

	hit.t = t;
	hit.point = vec3_add(ray.origin, vec3_scale(ray.dir, t));
	hit.normal = plane.normal;
	hit.material = plane.material;
	hit.hit = 1;
	return (hit);
}

void	intersect_plane(t_ray ray, t_plane plane, double *t)
{
	double	denom;
	t_vec3	to_plane;

	denom = vec3_dot(ray.dir, plane.normal);
	if (ft_fabs(denom) < 1e-6)
	{
		*t = DBL_MAX;
		return ;
	}
	to_plane = vec3_sub(plane.point, ray.origin);
	*t = vec3_dot(to_plane, plane.normal) / denom;
	if (*t < 0)
		*t = DBL_MAX;
}

t_hit	hit_planes(t_ray ray, int num_planes, t_plane *planes,
		t_hit closest_hit)
{
	int		i;
	double	t1;

	i = 0;
	while (i < num_planes)
	{
		intersect_plane(ray, planes[i], &t1);
		if (t1 >= ray.t_min && t1 <= ray.t_max && t1 < closest_hit.t)
			closest_hit = get_plane_hit(ray, planes[i], t1);
		i++;
	}
	return (closest_hit);
}
