#include "../../inc/rt.h"

t_color	color_multiply(t_color a, t_color b)
{
	t_color	result;

	result.r = (a.r * b.r) / 255;
	result.g = (a.g * b.g) / 255;
	result.b = (a.b * b.b) / 255;
	return (result);
}

t_color	color_scale(t_color color, double factor)
{
	t_color	result;

	result.r = (int)(color.r * factor);
	result.g = (int)(color.g * factor);
	result.b = (int)(color.b * factor);
	return (result);
}

t_color	color_add(t_color a, t_color b)
{
	t_color	result;

	result.r = a.r + b.r;
	result.g = a.g + b.g;
	result.b = a.b + b.b;
	return (result);
}

t_color	color_clamp(t_color color)
{
	t_color	result;

	result.r = (color.r > 255) ? 255 : (color.r < 0) ? 0 : color.r;
	result.g = (color.g > 255) ? 255 : (color.g < 0) ? 0 : color.g;
	result.b = (color.b > 255) ? 255 : (color.b < 0) ? 0 : color.b;
	return (result);
}

static int	check_sphere_shadows(t_ray shadow_ray,
		double light_distance, t_scene *scene)
{
	int		i;
	double	t1;
	double	t2;

	i = 0;
	while (i < scene->num_spheres)
	{
		IntersectRaySphere(shadow_ray, scene->spheres[i], &t1, &t2);
		if (t1 > 0.001 && t1 < light_distance)
			return (1);
		if (t2 > 0.001 && t2 < light_distance)
			return (1);
		i++;
	}
	return (0);
}

static int	check_cylinder_shadows(t_ray shadow_ray, double light_distance, t_scene *scene)
{
	int		i;
	double	t1;
	double	t2;

	i = 0;
	while (i < scene->num_cylinders)
	{
		IntersectRayCylinder(shadow_ray, scene->cylinders[i], &t1, &t2);
		if (t1 > 0.001 && t1 < light_distance)
			return (1);
		if (t2 > 0.001 && t2 < light_distance)
			return (1);
		i++;
	}
	return (0);
}

static int	check_plane_shadows(t_ray shadow_ray,
		double light_distance, t_scene *scene)
{
	int		i;
	double	t;

	i = 0;
	while (i < scene->num_planes)
	{
		IntersectRayPlane(shadow_ray, scene->planes[i], &t);
		if (t > 0.001 && t < light_distance)
			return (1);
		i++;
	}
	return (0);
}

int	is_in_shadow(t_vec3 hit_point, t_vec3 light_direction, double light_distance, t_scene *scene)
{
	t_ray	shadow_ray;

	ft_bzero(&shadow_ray, sizeof(t_ray));
	shadow_ray.origin = hit_point;
	shadow_ray.dir = light_direction;
	if (check_sphere_shadows(shadow_ray, light_distance, scene))
		return (1);
	if (check_cylinder_shadows(shadow_ray, light_distance, scene))
		return (1);
	if (check_plane_shadows(shadow_ray, light_distance, scene))
		return (1);
	return (0);
}

static void	calculate_ambient_lighting(t_color *final_color, t_material material, t_scene *scene)
{
	t_color	ambient_color;

	ambient_color = color_multiply(material.color, scene->ambient.color);
	ambient_color = color_scale(ambient_color, material.ambient * scene->ambient.intensity);
	*final_color = color_add(*final_color, ambient_color);
}

static void	calculate_point_lighting(t_color *final_color, t_vec3 hit_point, t_vec3 normal,
		t_vec3 view_direction, t_material material, t_scene *scene)
{
	int			i;
	t_point_light	light;
	t_vec3		light_direction;
	double		light_distance;
	double		diffuse_factor;
	t_color		diffuse_color;
	t_vec3		half_vector;
	double		specular_factor;
	t_color		specular_color;

	i = 0;
	while (i < scene->num_lights)
	{
		light = scene->lights[i];
		light_direction = vec3_sub(light.position, hit_point);
		light_distance = sqrt(vec3_dot(light_direction, light_direction));
		light_direction = vec3_normalize(light_direction);
		if (is_in_shadow(hit_point, light_direction, light_distance, scene))
		{
			i++;
			continue ;
		}
		diffuse_factor = vec3_dot(normal, light_direction);
		if (diffuse_factor > 0)
		{
			diffuse_color = color_multiply(material.color, light.color);
			diffuse_color = color_scale(diffuse_color, material.diffuse * diffuse_factor * light.intensity);
			*final_color = color_add(*final_color, diffuse_color);
		}
		half_vector = vec3_normalize(vec3_add(view_direction, light_direction));
		specular_factor = vec3_dot(normal, half_vector);
		if (specular_factor > 0)
		{
			specular_factor = pow(specular_factor, material.shininess);
			specular_color = color_multiply(material.color, light.color);
			specular_color = color_scale(specular_color, material.specular * specular_factor * light.intensity);
			*final_color = color_add(*final_color, specular_color);
		}
		i++;
	}
}

t_color	calculate_lighting(t_vec3 hit_point, t_vec3 normal, t_vec3 view_direction,
		t_material material, t_scene *scene)
{
	t_color	final_color;

	final_color = (t_color){0, 0, 0};
	calculate_ambient_lighting(&final_color, material, scene);
	calculate_point_lighting(&final_color, hit_point, normal, view_direction, material, scene);
	return (color_clamp(final_color));
}
