/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoo <aoo@student.42singapore.sg>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 05:21:03 by aoo               #+#    #+#             */
/*   Updated: 2025/07/12 05:21:04 by aoo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	intersect_sphere(t_ray ray, t_sphere sphere, double *t1, double *t2)
{
	t_vec3	co;
	double	a;
	double	b;
	double	discriminant;

	co = vec3_sub(ray.origin, sphere.center);
	a = vec3_dot(ray.dir, ray.dir);
	b = 2 * vec3_dot(co, ray.dir);
	discriminant = b * b - 4 * a * (vec3_dot(co, co) - sphere.radius
			* sphere.radius);
	if (discriminant < 0)
	{
		*t1 = DBL_MAX;
		*t2 = DBL_MAX;
		return ;
	}
	*t1 = (-b + sqrt(discriminant)) / (2 * a);
	*t2 = (-b - sqrt(discriminant)) / (2 * a);
}

t_hit	get_sphere_hit(t_ray ray, t_sphere sphere, double t)
{
	t_hit	hit;

	hit.t = t;
	hit.point = vec3_add(ray.origin, vec3_scale(ray.dir, t));
	hit.normal = vec3_normalize(vec3_sub(hit.point, sphere.center));
	hit.material = sphere.material;
	hit.hit = 1;
	return (hit);
}

t_hit	hit_spheres(t_ray ray, int num_spheres, t_sphere *spheres,
		t_hit closest_hit)
{
	int		i;
	double	t1;
	double	t2;

	i = 0;
	while (i < num_spheres)
	{
		intersect_sphere(ray, spheres[i], &t1, &t2);
		if (t1 >= ray.t_min && t1 <= ray.t_max && t1 < closest_hit.t)
			closest_hit = get_sphere_hit(ray, spheres[i], t1);
		if (t2 >= ray.t_min && t2 <= ray.t_max && t2 < closest_hit.t)
			closest_hit = get_sphere_hit(ray, spheres[i], t2);
		i++;
	}
	return (closest_hit);
}
