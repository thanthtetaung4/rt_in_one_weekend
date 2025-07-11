/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoo <aoo@student.42singapore.sg>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 05:21:03 by aoo               #+#    #+#             */
/*   Updated: 2025/07/12 05:50:08 by aoo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	intersect_sphere(t_ray ray, t_sphere sphere, double *t1, double *t2)
{
	t_quadratic	q;
	double		sqrt_discriminant;

	q.co = vec3_sub(ray.origin, sphere.center);
	q.a = vec3_dot(ray.dir, ray.dir);
	q.b = 2 * vec3_dot(q.co, ray.dir);
	q.discriminant = q.b * q.b - 4 * q.a * (vec3_dot(q.co, q.co) - sphere.radius
			* sphere.radius);
	if (q.discriminant < 0)
	{
		*t1 = DBL_MAX;
		*t2 = DBL_MAX;
		return ;
	}
	sqrt_discriminant = sqrt(q.discriminant);
	*t1 = (-q.b + sqrt_discriminant) / (2 * q.a);
	*t2 = (-q.b - sqrt_discriminant) / (2 * q.a);
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
