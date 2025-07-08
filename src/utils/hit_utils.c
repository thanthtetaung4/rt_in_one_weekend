#include "rt.h"

t_hit	hit_spheres(t_ray ray, int num_spheres, t_sphere *spheres, t_hit closest_hit)
{
	int		i;
	double	t1;
	double	t2;

	i = 0;
	while (i < num_spheres)
	{
		IntersectRaySphere(ray, spheres[i], &t1, &t2);
		if (t1 >= ray.t_min && t1 <= ray.t_max && t1 < closest_hit.t)
			closest_hit = get_sphere_hit(ray, spheres[i], t1);
		if (t2 >= ray.t_min && t2 <= ray.t_max && t2 < closest_hit.t)
			closest_hit = get_sphere_hit(ray, spheres[i], t2);
		i++;
	}
	return (closest_hit);
}

t_hit	hit_cylinders(t_ray ray, int num_cylinders, t_cylinder *cylinders, t_hit closest_hit)
{
	int		i;
	double	t1;
	double	t2;

	i = 0;
	while (i < num_cylinders)
	{
		IntersectRayCylinder(ray, cylinders[i], &t1, &t2);
		if (t1 >= ray.t_min && t1 <= ray.t_max && t1 < closest_hit.t)
			closest_hit = get_cylinder_hit(ray, cylinders[i], t1);
		if (t2 >= ray.t_min && t2 <= ray.t_max && t2 < closest_hit.t)
			closest_hit = get_cylinder_hit(ray, cylinders[i], t2);
		i++;
	}
	return (closest_hit);
}

t_hit	hit_planes(t_ray ray, int num_planes, t_plane *planes, t_hit closest_hit)
{
	int		i;
	double	t1;
	double	t2;

	i = 0;
	while (i < num_planes)
	{
		IntersectRayPlane(ray, planes[i], &t1);
		if (t1 >= ray.t_min && t1 <= ray.t_max && t1 < closest_hit.t)
			closest_hit = get_plane_hit(ray, planes[i], t1);
		i++;
	}
	return (closest_hit);
}