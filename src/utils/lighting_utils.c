/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taung <taung@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 17:48:24 by taung             #+#    #+#             */
/*   Updated: 2025/07/10 18:16:02 by taung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/rt.h"

static void	calculate_ambient_lighting(t_color *final_color,
		t_material material, t_scene *scene)
{
	t_color	ambient_color;

	ambient_color = color_multiply(material.color, scene->ambient.color);
	ambient_color = color_scale(ambient_color, material.ambient
			* scene->ambient.intensity);
	*final_color = color_add(*final_color, ambient_color);
}

static void	calculate_diffuse_lighting(t_color *final_color, t_vec3 hit_point,
		t_vec3 normal, t_point_light light, t_material material)
{
	t_vec3	light_direction;
	double	light_distance;
	double	diffuse_factor;
	t_color	diffuse_color;

	light_direction = vec3_sub(light.position, hit_point);
	light_distance = sqrt(vec3_dot(light_direction, light_direction));
	light_direction = vec3_normalize(light_direction);
	diffuse_factor = vec3_dot(normal, light_direction);
	if (diffuse_factor > 0)
	{
		diffuse_color = color_multiply(material.color, light.color);
		diffuse_color = color_scale(diffuse_color, material.diffuse
				* diffuse_factor * light.intensity);
		*final_color = color_add(*final_color, diffuse_color);
	}
}

static void	calculate_specular_lighting(t_color *final_color, t_vec3 normal,
		t_vec3 view_direction, t_vec3 light_direction, t_point_light light,
		t_material material)
{
	t_vec3	half_vector;
	double	specular_factor;
	t_color	specular_color;

	half_vector = vec3_normalize(vec3_add(view_direction, light_direction));
	specular_factor = vec3_dot(normal, half_vector);
	if (specular_factor > 0)
	{
		specular_factor = pow(specular_factor, material.shininess);
		specular_color = color_multiply(material.color, light.color);
		specular_color = color_scale(specular_color, material.specular
				* specular_factor * light.intensity);
		*final_color = color_add(*final_color, specular_color);
	}
}

static void	calculate_point_lighting(t_color *final_color, t_vec3 hit_point,
		t_vec3 normal, t_vec3 view_direction, t_material material,
		t_scene *scene)
{
	int				i;
	t_point_light	light;
	t_vec3			light_direction;
	double			light_distance;

	i = 0;
	while (i < scene->num_lights)
	{
		light = scene->lights[i];
		light_direction = vec3_sub(light.position, hit_point);
		light_distance = sqrt(vec3_dot(light_direction, light_direction));
		light_direction = vec3_normalize(light_direction);
		if (!is_in_shadow(hit_point, light_direction, light_distance, scene))
		{
			calculate_diffuse_lighting(final_color, hit_point, normal, light,
				material);
			calculate_specular_lighting(final_color, normal, view_direction,
				light_direction, light, material);
		}
		i++;
	}
}

t_color	calculate_lighting(t_vec3 hit_point, t_vec3 normal,
		t_vec3 view_direction, t_material material, t_scene *scene)
{
	t_color	final_color;

	final_color = (t_color){0, 0, 0};
	calculate_ambient_lighting(&final_color, material, scene);
	calculate_point_lighting(&final_color, hit_point, normal, view_direction,
		material, scene);
	return (color_clamp(final_color));
}
