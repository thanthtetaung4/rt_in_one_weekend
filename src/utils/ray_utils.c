/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taung <taung@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 14:25:36 by taung             #+#    #+#             */
/*   Updated: 2025/07/11 14:30:34 by taung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	IntersectRaySphere(t_ray ray, t_sphere sphere, double *t1, double *t2)
{
	t_vec3	CO;
	double	a;
	double	b;
	double	c;
	double	discriminant;

	CO = vec3_sub(ray.origin, sphere.center);
	a = vec3_dot(ray.dir, ray.dir);
	b = 2 * vec3_dot(CO, ray.dir);
	c = vec3_dot(CO, CO) - sphere.radius * sphere.radius;
	discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
	{
		*t1 = DBL_MAX;
		*t2 = DBL_MAX;
		return ;
	}
	*t1 = (-b + sqrt(discriminant)) / (2 * a);
	*t2 = (-b - sqrt(discriminant)) / (2 * a);
}

static void	check_cylinder_caps(t_vec3 O, t_vec3 D, t_cylinder cylinder, double *t1, double *t2)
{
	t_vec3	top_center;
	t_vec3	bottom_center;
	double	denom_top;
	double	denom_bottom;
	double	t_top;
	double	t_bottom;
	t_vec3	hit_point;
	t_vec3	to_hit;

	top_center = vec3_add(cylinder.center, vec3_scale(cylinder.axis, cylinder.height / 2.0));
	bottom_center = vec3_sub(cylinder.center, vec3_scale(cylinder.axis, cylinder.height / 2.0));
	denom_top = vec3_dot(D, cylinder.axis);
	if (ft_fabs(denom_top) > 1e-6)
	{
		t_top = vec3_dot(vec3_sub(top_center, O), cylinder.axis) / denom_top;
		if (t_top > 0)
		{
			hit_point = vec3_add(O, vec3_scale(D, t_top));
			to_hit = vec3_sub(hit_point, top_center);
			if (vec3_dot(to_hit, to_hit) <= cylinder.radius * cylinder.radius)
			{
				if (t_top < *t1)
					*t1 = t_top;
				else if (t_top < *t2)
					*t2 = t_top;
			}
		}
	}
	denom_bottom = vec3_dot(D, cylinder.axis);
	if (ft_fabs(denom_bottom) > 1e-6)
	{
		t_bottom = vec3_dot(vec3_sub(bottom_center, O), cylinder.axis) / denom_bottom;
		if (t_bottom > 0)
		{
			hit_point = vec3_add(O, vec3_scale(D, t_bottom));
			to_hit = vec3_sub(hit_point, bottom_center);
			if (vec3_dot(to_hit, to_hit) <= cylinder.radius * cylinder.radius)
			{
				if (t_bottom < *t1)
					*t1 = t_bottom;
				else if (t_bottom < *t2)
					*t2 = t_bottom;
			}
		}
	}
}

void	IntersectRayCylinder(t_ray ray, t_cylinder cylinder, double *t1, double *t2)
{
	t_vec3	CO;
	double	D_dot_axis;
	double	CO_dot_axis;
	t_vec3	D_perp;
	t_vec3	CO_perp;
	double	a;
	double	b;
	double	c;
	double	discriminant;
	double	t1_inf;
	double	t2_inf;
	double	half_height;
	double	y1;
	double	y2;

	CO = vec3_sub(ray.origin, cylinder.center);
	D_dot_axis = vec3_dot(ray.dir, cylinder.axis);
	CO_dot_axis = vec3_dot(CO, cylinder.axis);
	D_perp = vec3_sub(ray.dir, vec3_scale(cylinder.axis, D_dot_axis));
	CO_perp = vec3_sub(CO, vec3_scale(cylinder.axis, CO_dot_axis));
	a = vec3_dot(D_perp, D_perp);
	b = 2 * vec3_dot(D_perp, CO_perp);
	c = vec3_dot(CO_perp, CO_perp) - cylinder.radius * cylinder.radius;
	discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
	{
		*t1 = DBL_MAX;
		*t2 = DBL_MAX;
		return ;
	}
	t1_inf = (-b + sqrt(discriminant)) / (2 * a);
	t2_inf = (-b - sqrt(discriminant)) / (2 * a);
	half_height = cylinder.height / 2.0;
	y1 = CO_dot_axis + t1_inf * D_dot_axis;
	y2 = CO_dot_axis + t2_inf * D_dot_axis;
	*t1 = DBL_MAX;
	*t2 = DBL_MAX;
	if (t1_inf > 0 && y1 >= -half_height && y1 <= half_height)
		*t1 = t1_inf;
	if (t2_inf > 0 && y2 >= -half_height && y2 <= half_height)
		*t2 = t2_inf;
	check_cylinder_caps(ray.origin, ray.dir, cylinder, t1, t2);
}

void	IntersectRayPlane(t_ray ray, t_plane plane, double *t)
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

t_hit	get_cylinder_hit(t_ray ray, t_cylinder cylinder, double t)
{
	t_hit	hit;
	t_vec3		to_center;
	double		projection;
	double		half_height;
	t_vec3		top_center;
	t_vec3		bottom_center;
	t_vec3		normal;

	hit.t = t;
	hit.point = vec3_add(ray.origin, vec3_scale(ray.dir, t));
	to_center = vec3_sub(hit.point, cylinder.center);
	projection = vec3_dot(to_center, cylinder.axis);
	half_height = cylinder.height / 2.0;
	top_center = vec3_add(cylinder.center, vec3_scale(cylinder.axis, half_height));
	bottom_center = vec3_sub(cylinder.center, vec3_scale(cylinder.axis, half_height));
	if (ft_fabs(projection - half_height) < 0.001)
		hit.normal = cylinder.axis;
	else if (ft_fabs(projection + half_height) < 0.001)
		hit.normal = vec3_scale(cylinder.axis, -1);
	else
	{
		normal = vec3_sub(to_center, vec3_scale(cylinder.axis, projection));
		hit.normal = vec3_normalize(normal);
	}
	hit.material = cylinder.material;
	hit.hit = 1;
	return (hit);
}

t_hit	get_plane_hit(t_ray ray, t_plane plane, double t)
{
	t_hit	hit;

	hit.t = t;
	hit.point = vec3_add(ray.origin, vec3_scale(ray.dir, t));
	hit.normal = plane.normal;
	hit.material = plane.material;
	hit.hit = 1;
	return (hit);
}

t_hit	TraceRayHit(t_ray ray, t_scene *scene)
{
	t_hit	closest_hit;
	int			i;
	double		t1;
	double		t2;

	ft_bzero(&closest_hit, sizeof(t_hit));
	closest_hit.t = DBL_MAX;
	closest_hit = hit_spheres(ray, scene->num_spheres, scene->spheres, closest_hit);
	closest_hit = hit_cylinders(ray, scene->num_cylinders, scene->cylinders, closest_hit);
	closest_hit = hit_planes(ray, scene->num_planes, scene->planes, closest_hit);
	return (closest_hit);
}

t_color	TraceRay(t_ray ray, t_scene *scene)
{
	t_hit	hit;
	t_vec3		view_direction;

	hit = TraceRayHit(ray, scene);
	if (!hit.hit)
		return (scene->background);
	view_direction = vec3_normalize(vec3_sub(ray.origin, hit.point));
	return (calculate_lighting(hit, view_direction, scene));
}
