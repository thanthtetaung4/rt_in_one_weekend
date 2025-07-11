/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taung <taung@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 17:48:24 by taung             #+#    #+#             */
/*   Updated: 2025/07/11 14:17:36 by taung            ###   ########.fr       */
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

static void	calculate_diffuse_lighting(t_color *final_color, t_hit hit,
		t_point_light light)
{
	t_vec3	light_direction;
	double	light_distance;
	double	diffuse_factor;
	t_color	diffuse_color;

	light_direction = vec3_sub(light.position, hit.point);
	light_distance = sqrt(vec3_dot(light_direction, light_direction));
	light_direction = vec3_normalize(light_direction);
	diffuse_factor = vec3_dot(hit.normal, light_direction);
	if (diffuse_factor > 0)
	{
		diffuse_color = color_multiply(hit.material.color, light.color);
		diffuse_color = color_scale(diffuse_color, hit.material.diffuse
				* diffuse_factor * light.intensity);
		*final_color = color_add(*final_color, diffuse_color);
	}
}

static void	calculate_specular_lighting(t_color *final_color, t_hit hit,
		t_vec3 *arr, t_point_light light)
{
	t_vec3	half_vector;
	double	specular_factor;
	t_color	specular_color;

	half_vector = vec3_normalize(vec3_add(arr[1], arr[0]));
	specular_factor = vec3_dot(hit.normal, half_vector);
	if (specular_factor > 0)
	{
		specular_factor = pow(specular_factor, hit.material.shininess);
		specular_color = color_multiply(hit.material.color, light.color);
		specular_color = color_scale(specular_color, hit.material.specular
				* specular_factor * light.intensity);
		*final_color = color_add(*final_color, specular_color);
	}
}

static void	calculate_point_lighting(t_color *final_color, t_hit hit,
		t_vec3 view_direction, t_scene *scene)
{
	int				i;
	t_point_light	light;
	t_vec3			light_direction;
	double			light_distance;
	t_vec3			arr[2];

	i = 0;
	while (i < scene->num_lights)
	{
		light = scene->lights[i];
		light_direction = vec3_sub(light.position, hit.point);
		light_distance = sqrt(vec3_dot(light_direction, light_direction));
		light_direction = vec3_normalize(light_direction);
		if (!is_in_shadow(hit.point, light_direction, light_distance, scene))
		{
			calculate_diffuse_lighting(final_color, hit, light);
			arr[0] = light_direction;
			arr[1] = view_direction;
			calculate_specular_lighting(final_color, hit, arr, light);
		}
		i++;
	}
}

t_color	calculate_lighting(t_hit hit, t_vec3 view_direction, t_scene *scene)
{
	t_color	final_color;

	final_color = (t_color){0, 0, 0};
	calculate_ambient_lighting(&final_color, hit.material, scene);
	calculate_point_lighting(&final_color, hit, view_direction, scene);
	return (color_clamp(final_color));
}
