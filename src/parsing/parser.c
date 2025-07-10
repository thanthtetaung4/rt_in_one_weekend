/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taung <taung@student.42singapore.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 12:31:33 by taung             #+#    #+#             */
/*   Updated: 2025/07/10 17:13:25 by taung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int	alloc_sp(t_data *data)
{
	data->scene->spheres = (t_sphere *)ft_calloc(data->scene->num_spheres,
			sizeof(t_sphere));
	if (!data->scene->spheres)
		return (0);
	return (1);
}

int	alloc_l(t_data *data)
{
	data->scene->lights = (t_point_light *)ft_calloc(data->scene->num_lights,
			sizeof(t_point_light));
	if (!data->scene->lights)
		return (0);
	return (1);
}

int	alloc_cy(t_data *data)
{
	data->scene->cylinders = (t_cylinder *)ft_calloc(data->scene->num_cylinders,
			sizeof(t_cylinder));
	if (!data->scene->cylinders)
		return (0);
	return (1);
}

int	alloc_pl(t_data *data)
{
	data->scene->planes = (t_plane *)ft_calloc(data->scene->num_planes,
			sizeof(t_plane));
	if (!data->scene->planes)
		return (0);
	return (1);
}

int	init_scene(char *filename, t_data *data)
{
	count_onl(filename, data);
	if (data->scene->num_lights > 0)
		if (!alloc_l(data))
			return (0);
	if (data->scene->num_spheres > 0)
		if (!alloc_sp(data))
			return (0);
	if (data->scene->num_planes > 0)
		if (!alloc_pl(data))
			return (0);
	if (data->scene->num_cylinders > 0)
		if (!alloc_cy(data))
			return (0);
	return (1);
}

int	parse_rgb(char *str, t_color *color)
{
	char	**rgb;

	rgb = ft_split(str, ",");
	if (ft_strslen(rgb) != 3)
		return (free_strs(rgb), 0);
	if (!ft_atoi_vali(rgb[0], &color->r) || !check_range(color->r, 0, 255)
		|| !ft_atoi_vali(rgb[1], &color->g) || !check_range(color->g, 0, 255)
		|| !ft_atoi_vali(rgb[2], &color->b) || !check_range(color->b, 0, 255))
	{
		free_strs(rgb);
		return (0);
	}
	free_strs(rgb);
	return (1);
}

int	parse_xyz(char *str, t_vec3 *vec3, int vector)
{
	char	**xyz;

	xyz = ft_split(str, ",");
	if (ft_strslen(xyz) != 3 || !xyz)
		return (free_strs(xyz), 0);
	if (!ft_atof_vali(xyz[0], &vec3->x) || !ft_atof_vali(xyz[1], &vec3->y)
		|| !ft_atof_vali(xyz[2], &vec3->z))
	{
		if (vector)
		{
			if (!check_range(vec3->x, -1, 1) || !check_range(vec3->y, -1, 1)
				|| !check_range(vec3->z, -1, 1))
			{
				free_strs(xyz);
				return (0);
			}
			return (free_strs(xyz), 0);
		}
		free_strs(xyz);
		return (0);
	}
	free_strs(xyz);
	return (1);
}

int	world_parser(char *res, t_data *data)
{
	char	**split;

	split = ft_split(res, " \t\n");
	if (ft_strcmp(split[0], "A") == 0)
	{
		if (!parse_ambient(res, &data->scene->ambient))
			return (free_strs(split), print_error("Error: Invalid ambient!\n"));
	}
	else if (ft_strcmp(split[0], "c") == 0)
	{
		if (!parse_camera(res, &data->scene->camera))
			return (free_strs(split), print_error("Error: Invalid camera!\n"));
	}
	else if (ft_strcmp(split[0], "l") == 0)
	{
		if (!parse_light(res, data))
			return (free_strs(split), print_error("Error: Invalid light!\n"));
	}
	else if (ft_strcmp(split[0], "r") == 0)
	{
		if (!parse_ratio(res, data->scene))
			return (free_strs(split), print_error("Error: Invalid ratio!\n"));
	}
	return (free_strs(split), 1);
}

int	object_parser(char *res, t_data *data)
{
	char	**split;

	split = ft_split(res, " \t\n");
	if (ft_strcmp(split[0], "sp") == 0)
	{
		if (!parse_sphere(res, data))
			return (free_strs(split), print_error("Error: Invalid sphere!\n"));
	}
	else if (ft_strcmp(split[0], "pl") == 0)
	{
		if (!parse_plane(res, data))
			return (free_strs(split), print_error("Error: Invalid plane!\n"));
	}
	else if (ft_strcmp(split[0], "cy") == 0)
	{
		if (!parse_cylinder(res, data))
			return (free_strs(split),
				print_error("Error: Invalid cylinder!\n"));
	}
	free_strs(split);
	return (1);
}

int	parser(char *filename, t_data *data)
{
	int		fd;
	char	*res;
	int		i;

	i = 0;
	init_scene(filename, data);
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (print_error("Error: Invalid path!\n"));
	res = gnl(fd);
	while (res)
	{
		if (*res != '\n' && (!world_parser(res, data) || !object_parser(res,
					data)))
		{
			free(res);
			return (close(fd) || 0);
		}
		free(res);
		res = gnl(fd);
		i++;
	}
	free(res);
	return (!close(fd) && 1);
}
