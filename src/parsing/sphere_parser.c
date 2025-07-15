/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_parser.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taung <taung@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 23:24:16 by taung             #+#    #+#             */
/*   Updated: 2025/07/15 14:03:43 by taung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int	parse_sphere(char *line, t_data *data)
{
	char		**split;
	t_sphere	sphere;

	split = ft_split(line, " \t\n");
	if (!split || !*split)
		return (0);
	if (!(ft_strslen(split) >= 4 && ft_strslen(split) <= 6)
		|| !parse_xyz(split[1], &sphere.center, 0) || !ft_atof_vali(split[2],
			&sphere.radius) || sphere.radius <= 0 || !parse_rgb(split[3],
			&sphere.material.color))
		return (free_strs(split), 0);
	sphere.radius /= 2;
	if (split[4])
	{
		if (!parse_material_i(split[4], split[5], &sphere.material))
			return (0);
	}
	else
		init_mat(&sphere.material);
	data->scene->spheres[data->scene->sp_i++] = sphere;
	free_strs(split);
	return (1);
}
