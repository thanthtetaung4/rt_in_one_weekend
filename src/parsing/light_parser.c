/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taung <taung@student.42singapore.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 23:24:16 by taung             #+#    #+#             */
/*   Updated: 2025/07/10 14:51:49 by taung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int parse_light(char *line, t_data *data)
{
	char			**split;
	t_point_light	light;

	split = ft_split(line, " \t\n");
	if (!split || !*split)
		return (0);
	if (ft_strslen(split) != 4 || !parse_xyz(split[1], &light.position, 0) ||
	!ft_atof_vali(split[2], &light.intensity) ||
	!check_range(light.intensity, 0.0, 1.0) ||
	!parse_rgb(split[3], &light.color))
		return (free_strs(split), 0);
	data->scene->lights[data->scene->l_i] = light;
	data->scene->l_i++;
	return (free_strs(split), 1);
}
