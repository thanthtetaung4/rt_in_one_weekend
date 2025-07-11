/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_parser.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoo <aoo@student.42singapore.sg>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 23:24:16 by taung             #+#    #+#             */
/*   Updated: 2025/07/12 04:17:37 by aoo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int	parse_cylinder(char *line, t_data *data)
{
	char		**split;
	t_cylinder	cylinder;

	split = ft_split(line, " \t\n");
	if (!split || !*split)
		return (0);
	if (!(ft_strslen(split) >= 6 && ft_strslen(split) <= 8)
		|| !parse_xyz(split[1], &cylinder.center, 0) || !parse_xyz(split[2],
			&cylinder.axis, 0) || !ft_atof_vali(split[3], &cylinder.radius)
		|| cylinder.radius <= 0 || !ft_atof_vali(split[4],
			&cylinder.half_height) || cylinder.half_height <= 0
		|| !parse_rgb(split[5], &cylinder.material.color))
		return (free_strs(split), 0);
	if (split[6])
	{
		if (!parse_material_i(split[6], split[7], &cylinder.material))
			return (0);
	}
	else
		init_mat(&cylinder.material);
	cylinder.radius /= 2.0;
	cylinder.axis = vec3_normalize(cylinder.axis);
	cylinder.half_height /= 2.0;
	data->scene->cylinders[data->scene->cy_i++] = cylinder;
	return (free_strs(split), 1);
}
