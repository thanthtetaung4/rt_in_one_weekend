#ifndef VEC3_H
# define VEC3_H

typedef struct
{
	double x, y, z;
}		vec3;

// Constructor
vec3	vec3_create(double x, double y, double z);

// Vector operations
vec3	vec3_neg(vec3 v);
vec3	vec3_add(vec3 a, vec3 b);
vec3	vec3_sub(vec3 a, vec3 b);
vec3	vec3_mul(vec3 a, vec3 b);
vec3	vec3_scale(vec3 v, double t);
vec3	vec3_div(vec3 v, double t);
double	vec3_dot(vec3 a, vec3 b);
vec3	vec3_cross(vec3 a, vec3 b);
double	vec3_length(vec3 v);
double	vec3_length_squared(vec3 v);
vec3	vec3_unit(vec3 v);
void	vec3_print(vec3 v);

#endif
