/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_parser.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taung <taung@student.42singapore.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 23:24:16 by taung             #+#    #+#             */
/*   Updated: 2025/07/09 22:23:47 by taung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int parse_cylinder(char *line, t_data *data)
{
	char	**split;
	t_cylinder	cylinder;

	split = ft_split(line, " \t\n");
	if (!split || !*split)
	return (0);
	if (!(ft_strslen(split) >= 6 && ft_strslen(split) <= 8) || !parse_xyz(split[1], &cylinder.center, 0) ||
	!parse_xyz(split[2], &cylinder.axis, 0)||
	!ft_atof_vali(split[3], &cylinder.radius)||
		cylinder.radius <= 0 ||
		!ft_atof_vali(split[4], &cylinder.height)||
		cylinder.height <= 0 ||
		!parse_rgb(split[5], &cylinder.material.color))
		return (free_strs(split), 0);
	if (split[6])
		parse_material_i(split[6], split[7], &cylinder.material);
	else
		init_mat(&cylinder.material);
	free_strs(split);
	cylinder.radius /= 2;
	cylinder.axis = vec3_normalize(cylinder.axis);
	data->scene->cylinders[data->scene->cy_i++] = cylinder;
	return (1);
}
