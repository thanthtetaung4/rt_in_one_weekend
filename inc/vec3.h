# ifndef VEC3_H
# define VEC3_H

typedef struct s_vec3
{
	double x;
	double y;
	double z;
} t_vec3;

t_vec3 vec3_create(double x, double y, double z);
t_vec3 vec3_add(t_vec3 a, t_vec3 b);
t_vec3 vec3_sub(t_vec3 a, t_vec3 b);
t_vec3 vec3_scale(t_vec3 v, double s);
t_vec3 vec3_div(t_vec3 v, double s);
double vec3_dot(t_vec3 a, t_vec3 b);
t_vec3 vec3_cross(t_vec3 a, t_vec3 b);
t_vec3 vec3_normalize(t_vec3 v);

# endif
