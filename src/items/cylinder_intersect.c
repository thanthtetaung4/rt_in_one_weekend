/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_intersect.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoo <aoo@student.42singapore.sg>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 05:27:52 by aoo               #+#    #+#             */
/*   Updated: 2025/07/12 05:27:53 by aoo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	intersect_cyl_cap(t_ray ray, t_cylinder cylinder, t_quadratic *q,
		t_vec3 cap_center)
{
	t_vec3	hit_point;
	t_vec3	to_hit;
	double	t_cap;
	double	denom;

	denom = vec3_dot(ray.dir, cylinder.axis);
	if (ft_fabs(denom) > 1e-6)
	{
		t_cap = vec3_dot(vec3_sub(cap_center, ray.origin), cylinder.axis)
			/ denom;
		if (t_cap > 0)
		{
			hit_point = vec3_add(ray.origin, vec3_scale(ray.dir, t_cap));
			to_hit = vec3_sub(hit_point, cap_center);
			if (vec3_dot(to_hit, to_hit) <= cylinder.radius * cylinder.radius)
			{
				if (t_cap < q->t1)
					q->t1 = t_cap;
				else if (t_cap < q->t2)
					q->t2 = t_cap;
			}
		}
	}
}

static void	check_cylinder_caps(t_quadratic *q, t_ray ray, t_cylinder cylinder)
{
	t_vec3	top_center;
	t_vec3	bottom_center;

	top_center = vec3_add(cylinder.center, vec3_scale(cylinder.axis,
				cylinder.half_height));
	bottom_center = vec3_sub(cylinder.center, vec3_scale(cylinder.axis,
				cylinder.half_height));
	intersect_cyl_cap(ray, cylinder, q, top_center);
	intersect_cyl_cap(ray, cylinder, q, bottom_center);
}

static void	validate_cylinder_sides(t_quadratic *q, t_cylinder cyl,
		double d_dot_axis, double co_dot_axis)
{
	double	y1;
	double	y2;
	double	t1_inf;
	double	t2_inf;

	y1 = co_dot_axis + q->t1 * d_dot_axis;
	y2 = co_dot_axis + q->t2 * d_dot_axis;
	t1_inf = q->t1;
	t2_inf = q->t2;
	q->t1 = DBL_MAX;
	q->t2 = DBL_MAX;
	if (t1_inf > 0 && y1 >= -cyl.half_height && y1 <= cyl.half_height)
		q->t1 = t1_inf;
	if (q->t2 > 0 && y2 >= -cyl.half_height && y2 <= cyl.half_height)
		q->t2 = t2_inf;
}

static t_quadratic	setup_cylinder_quadratic(t_ray ray, t_cylinder cyl,
		double *dot_axis_d, double *dot_axis_co)
{
	t_quadratic	q;
	t_vec3		d_prep;
	t_vec3		co_prep;
	double		sqrt_disc;

	q.co = vec3_sub(ray.origin, cyl.center);
	*dot_axis_d = vec3_dot(ray.dir, cyl.axis);
	*dot_axis_co = vec3_dot(q.co, cyl.axis);
	d_prep = vec3_sub(ray.dir, vec3_scale(cyl.axis, *dot_axis_d));
	co_prep = vec3_sub(q.co, vec3_scale(cyl.axis, *dot_axis_co));
	q.a = vec3_dot(d_prep, d_prep);
	q.b = 2 * vec3_dot(d_prep, co_prep);
	q.c = vec3_dot(co_prep, co_prep) - cyl.radius * cyl.radius;
	q.discriminant = q.b * q.b - 4 * q.a * q.c;
	q.t1 = DBL_MAX;
	q.t2 = DBL_MAX;
	if (q.discriminant >= 0)
	{
		sqrt_disc = sqrt(q.discriminant);
		q.t1 = (-q.b - sqrt_disc) / (2 * q.a);
		q.t2 = (-q.b + sqrt_disc) / (2 * q.a);
	}
	return (q);
}

void	intersect_cylinder(t_ray ray, t_cylinder cylinder, double *t1,
		double *t2)
{
	t_quadratic	q;
	double		d_dot_axis;
	double		co_dot_axis;

	q = setup_cylinder_quadratic(ray, cylinder, &d_dot_axis, &co_dot_axis);
	if (q.discriminant < 0)
	{
		*t1 = DBL_MAX;
		*t2 = DBL_MAX;
		return ;
	}
	validate_cylinder_sides(&q, cylinder, d_dot_axis, co_dot_axis);
	check_cylinder_caps(&q, ray, cylinder);
	*t1 = q.t1;
	*t2 = q.t2;
}
