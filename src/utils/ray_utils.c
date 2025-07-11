
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

// void	do_smth_on_hit(t_ray ray, t_cylinder cylinder, t_quadratic *q, double denom, t_vec3 cap_center)
// {
// 	t_vec3	hit_point;
// 	t_vec3	to_hit;
// 	double	t_cap;

// 	if (ft_fabs(denom) > 1e-6)
// 	{
// 		t_cap = vec3_dot(vec3_sub(cap_center, ray.origin), cylinder.axis) / denom;
// 		if (t_cap > 0)
// 		{
// 			hit_point = vec3_add(ray.origin, vec3_scale(ray.dir, t_cap));
// 			to_hit = vec3_sub(hit_point, cap_center);
// 			if (vec3_dot(to_hit, to_hit) <= cylinder.radius * cylinder.radius)
// 			{
// 				if (t_cap < q->t1)
// 					q->t1 = t_cap;
// 				else if (t_cap < q->t2)
// 					q->t2 = t_cap;
// 			}
// 		}
// 	}
// }

// static void	check_cylinder_caps(t_ray ray, t_cylinder cylinder,
// 		t_quadratic	*q)
// {
// 	t_vec3	top_center;
// 	t_vec3	bottom_center;
// 	double	denom;

// 	top_center = vec3_add(cylinder.center, vec3_scale(cylinder.axis,
// 				cylinder.half_height));
// 	bottom_center = vec3_sub(cylinder.center, vec3_scale(cylinder.axis,
// 				cylinder.half_height));
// 	denom = vec3_dot(ray.dir, cylinder.axis);
// 	do_smth_on_hit(ray, cylinder, q, denom, top_center);
// 	do_smth_on_hit(ray, cylinder, q, denom, bottom_center);
// }






static void	check_cylinder_caps(t_ray ray, t_cylinder cylinder,
		double *t1, double *t2)
{
	t_vec3	top_center;
	t_vec3	bottom_center;
	double	denom_top;
	double	denom_bottom;
	double	t_top;
	double	t_bottom;
	t_vec3	hit_point;
	t_vec3	to_hit;

	top_center = vec3_add(cylinder.center, vec3_scale(cylinder.axis,
				cylinder.half_height / 2.0));
	bottom_center = vec3_sub(cylinder.center, vec3_scale(cylinder.axis,
				cylinder.half_height / 2.0));
	denom_top = vec3_dot(ray.dir, cylinder.axis);
	if (ft_fabs(denom_top) > 1e-6)
	{
		t_top = vec3_dot(vec3_sub(top_center, ray.origin), cylinder.axis) / denom_top;
		if (t_top > 0)
		{
			hit_point = vec3_add(ray.origin, vec3_scale(ray.dir, t_top));
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
	denom_bottom = vec3_dot(ray.dir, cylinder.axis);
	if (ft_fabs(denom_bottom) > 1e-6)
	{
		t_bottom = vec3_dot(vec3_sub(bottom_center, ray.origin), cylinder.axis)
			/ denom_bottom;
		if (t_bottom > 0)
		{
			hit_point = vec3_add(ray.origin, vec3_scale(ray.dir, t_bottom));
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

static t_quadratic	setup_cylinder_quadratic(t_ray ray, t_cylinder cyl,
	double *dot_axis_d, double *dot_axis_co)
{
	t_quadratic	q;
	t_vec3		d_prep;
	t_vec3		co_prep;

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
		double sqrt_disc = sqrt(q.discriminant);
		q.t1 = (-q.b - sqrt_disc) / (2 * q.a);
		q.t2 = (-q.b + sqrt_disc) / (2 * q.a);
	}
	return (q);
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

void	intersect_cylinder(t_ray ray, t_cylinder cylinder, double *t1, double *t2)
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
	*t1 = q.t1;
	*t2 = q.t2;
	check_cylinder_caps(ray, cylinder, t1, t2);
}

// void	intersect_cylinder(t_ray ray, t_cylinder cylinder, double *t1,
// 		double *t2)
// {
// 	t_vec3	co;
// 	double	D_dot_axis;
// 	double	CO_dot_axis;
// 	t_vec3	D_perp;
// 	t_vec3	CO_perp;
// 	double	a;
// 	double	b;
// 	double	c;
// 	double	discriminant;
// 	double	t1_inf;
// 	double	t2_inf;
// 	double	half_height;
// 	double	y1;
// 	double	y2;

// 	co = vec3_sub(ray.origin, cylinder.center);
// 	D_dot_axis = vec3_dot(ray.dir, cylinder.axis);
// 	CO_dot_axis = vec3_dot(co, cylinder.axis);
// 	D_perp = vec3_sub(ray.dir, vec3_scale(cylinder.axis, D_dot_axis));
// 	CO_perp = vec3_sub(co, vec3_scale(cylinder.axis, CO_dot_axis));
// 	a = vec3_dot(D_perp, D_perp);
// 	b = 2 * vec3_dot(D_perp, CO_perp);
// 	c = vec3_dot(CO_perp, CO_perp) - cylinder.radius * cylinder.radius;
// 	discriminant = b * b - 4 * a * c;
// 	if (discriminant < 0)
// 	{
// 		*t1 = DBL_MAX;
// 		*t2 = DBL_MAX;
// 		return ;
// 	}
// 	t1_inf = (-b + sqrt(discriminant)) / (2 * a);
// 	t2_inf = (-b - sqrt(discriminant)) / (2 * a);
// 	half_height = cylinder.half_height / 2.0;
// 	y1 = CO_dot_axis + t1_inf * D_dot_axis;
// 	y2 = CO_dot_axis + t2_inf * D_dot_axis;
// 	*t1 = DBL_MAX;
// 	*t2 = DBL_MAX;
// 	if (t1_inf > 0 && y1 >= -half_height && y1 <= half_height)
// 		*t1 = t1_inf;
// 	if (t2_inf > 0 && y2 >= -half_height && y2 <= half_height)
// 		*t2 = t2_inf;
// 	check_cylinder_caps(ray.origin, ray.dir, cylinder, t1, t2);
// }

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
	t_gch_calc	data;

	data.hit.t = t;
	data.hit.point = vec3_add(ray.origin, vec3_scale(ray.dir, t));
	data.to_center = vec3_sub(data.hit.point, cylinder.center);
	data.projection = vec3_dot(data.to_center, cylinder.axis);
	data.half_height = cylinder.half_height / 2.0;
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

t_hit	trace_ray_hit(t_ray ray, t_scene *scene)
{
	t_hit	closest_hit;
	int		i;
	double	t1;
	double	t2;

	ft_bzero(&closest_hit, sizeof(t_hit));
	closest_hit.t = DBL_MAX;
	closest_hit = hit_spheres(ray, scene->num_spheres, scene->spheres,
			closest_hit);
	closest_hit = hit_cylinders(ray, scene->num_cylinders, scene->cylinders,
			closest_hit);
	closest_hit = hit_planes(ray, scene->num_planes, scene->planes,
			closest_hit);
	return (closest_hit);
}

t_color	trace_ray(t_ray ray, t_scene *scene)
{
	t_hit	hit;
	t_vec3	view_direction;

	hit = trace_ray_hit(ray, scene);
	if (!hit.hit)
		return (scene->background);
	view_direction = vec3_normalize(vec3_sub(ray.origin, hit.point));
	return (calculate_lighting(hit, view_direction, scene));
}
