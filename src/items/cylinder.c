/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoo <aoo@student.42singapore.sg>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 05:23:20 by aoo               #+#    #+#             */
/*   Updated: 2025/07/12 05:27:37 by aoo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_hit	get_cylinder_hit(t_ray ray, t_cylinder cylinder, double t)
{
	t_gch_calc	data;

	data.hit.t = t;
	data.hit.point = vec3_add(ray.origin, vec3_scale(ray.dir, t));
	data.to_center = vec3_sub(data.hit.point, cylinder.center);
	data.projection = vec3_dot(data.to_center, cylinder.axis);
	data.half_height = cylinder.half_height;
	data.top_center = vec3_add(cylinder.center, vec3_scale(cylinder.axis,
				data.half_height));
	data.bottom_center = vec3_sub(cylinder.center, vec3_scale(cylinder.axis,
				data.half_height));
	if (ft_fabs(data.projection - data.half_height) < 0.001)
		data.hit.normal = cylinder.axis;
	else if (ft_fabs(data.projection + data.half_height) < 0.001)
		data.hit.normal = vec3_scale(cylinder.axis, -1);
	else
	{
		data.normal = vec3_sub(data.to_center, vec3_scale(cylinder.axis,
					data.projection));
		data.hit.normal = vec3_normalize(data.normal);
	}
	data.hit.material = cylinder.material;
	data.hit.hit = 1;
	return (data.hit);
}

t_hit	hit_cylinders(t_ray ray, int num_cylinders, t_cylinder *cylinders,
		t_hit closest_hit)
{
	int		i;
	double	t1;
	double	t2;

	i = 0;
	while (i < num_cylinders)
	{
		intersect_cylinder(ray, cylinders[i], &t1, &t2);
		if (t1 >= ray.t_min && t1 <= ray.t_max && t1 < closest_hit.t)
			closest_hit = get_cylinder_hit(ray, cylinders[i], t1);
		if (t2 >= ray.t_min && t2 <= ray.t_max && t2 < closest_hit.t)
			closest_hit = get_cylinder_hit(ray, cylinders[i], t2);
		i++;
	}
	return (closest_hit);
}
