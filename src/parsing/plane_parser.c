/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taung <taung@student.42singapore.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 23:24:16 by taung             #+#    #+#             */
/*   Updated: 2025/07/10 17:08:10 by taung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int parse_plane(char *line, t_data *data)
{
	char	**split;
	t_plane	plane;

	split = ft_split(line, " \t\n");
	if (!split || !*split)
		return (0);
	if (!(ft_strslen(split) >= 4 && ft_strslen(split) <= 6) || !parse_xyz(split[1], &plane.point, 0) ||
		!parse_xyz(split[2], &plane.normal, 1) ||
		!parse_rgb(split[3], &plane.material.color))
		return (free_strs(split), 0);
	if (split[4])
	{
		if (!parse_material_i(split[4], split[5], &plane.material))
			return (0);
	}
	else
		init_mat(&plane.material);
	data->scene->planes[data->scene->pl_i++] = plane;
	free_strs(split);
	return (1);
}
