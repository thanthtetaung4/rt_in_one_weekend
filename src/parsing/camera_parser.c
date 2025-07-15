/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_parser.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taung <taung@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 23:24:16 by taung             #+#    #+#             */
/*   Updated: 2025/07/15 15:19:29 by taung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int	parse_camera(char *line, t_camera *camera)
{
	char	**split;

	split = ft_split(line, " \t\n");
	if (!split || !*split)
		return (0);
	if (ft_strslen(split) != 4 || !parse_xyz(split[1], &camera->p, 0)
		|| !parse_xyz(split[2], &camera->d, 1) || !ft_atof_vali(split[3],
			&camera->fov) || !check_range(camera->fov, 0, 180))
		return (free_strs(split), 0);
	camera->fov = camera->fov * (PI / 180.0);
	return (free_strs(split), 1);
}
