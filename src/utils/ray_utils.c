/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoo <aoo@student.42singapore.sg>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 05:31:36 by aoo               #+#    #+#             */
/*   Updated: 2025/07/12 05:32:07 by aoo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	render_to_mlx_image(t_scene *scene, t_data *data)
{
	t_camera_view	view;
	t_ray			ray;
	t_vec3			pixel;
	int				xy[2];

	ray = init_ray(scene->camera.p, vec3_create(0, 0, 0), 1.0, DBL_MAX);
	view = setup_camera(scene->camera, scene);
	xy[1] = 0;
	while (xy[1] < scene->height)
	{
		xy[0] = 0;
		while (xy[0] < scene->width)
		{
			pixel = vec3_add(view.pixel00,
					vec3_add(vec3_scale(view.pixel_delta_u, xy[0]),
						vec3_scale(view.pixel_delta_v, scene->height - 1
							- xy[1])));
			ray.dir = vec3_normalize(vec3_sub(pixel, scene->camera.p));
			mlx_pixel_put(data->mlx, data->mlx_win, xy[0], xy[1],
				color_to_mlx(trace_ray(ray, scene)));
			xy[0]++;
		}
		xy[1]++;
	}
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
