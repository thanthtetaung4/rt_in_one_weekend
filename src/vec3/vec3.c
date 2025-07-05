#include "../../inc/rt.h"

t_vec3	vec3_create(double x, double y, double z)
{
	t_vec3	v;

	v.x = x;
	v.y = y;
	v.z = z;
	return (v);
}

t_vec3	vec3_neg(t_vec3 v)
{
	return (vec3_create(-v.x, -v.y, -v.z));
}

t_vec3	vec3_add(t_vec3 a, t_vec3 b)
{
	return (vec3_create(a.x + b.x, a.y + b.y, a.z + b.z));
}

t_vec3	vec3_sub(t_vec3 a, t_vec3 b)
{
	return (vec3_create(a.x - b.x, a.y - b.y, a.z - b.z));
}

t_vec3	vec3_mul(t_vec3 a, t_vec3 b)
{
	return (vec3_create(a.x * b.x, a.y * b.y, a.z * b.z));
}

t_vec3	vec3_scale(t_vec3 v, double t)
{
	return (vec3_create(v.x * t, v.y * t, v.z * t));
}

t_vec3	vec3_div(t_vec3 v, double t)
{
	return (vec3_scale(v, 1.0 / t));
}

double	vec3_dot(t_vec3 a, t_vec3 b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

t_vec3	vec3_cross(t_vec3 a, t_vec3 b)
{
	return (vec3_create(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y
			- a.y * b.x));
}

double	vec3_length(t_vec3 v)
{
	return (sqrt(vec3_length_squared(v)));
}

double	vec3_length_squared(t_vec3 v)
{
	return (v.x * v.x + v.y * v.y + v.z * v.z);
}

t_vec3	vec3_unit(t_vec3 v)
{
	return (vec3_div(v, vec3_length(v)));
}

void	vec3_print(t_vec3 v)
{
	printf("%f %f %f\n", v.x, v.y, v.z);
}
