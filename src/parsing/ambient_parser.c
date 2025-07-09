/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ambient_parser.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taung <taung@student.42singapore.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 23:24:16 by taung             #+#    #+#             */
/*   Updated: 2025/07/09 20:13:40 by taung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int	parse_ambient(char *line, t_ambient_light *ambient)
{
	char	**split;

	split = ft_split(line, " \t\n");
	if (!split || !*split)
		return (0);
	if (ft_strslen(split) != 3 || !ft_atof_vali(split[1], &ambient->intensity) ||
		!check_range(ambient->intensity, 0.0, 1.0))
		return (free_strs(split), 0);
	if (!parse_rgb(split[2], &ambient->color))
		return (free_strs(split), 0);
	// ambient->color.r /= 255.0f;
	// ambient->color.g /= 255.0f;
	// ambient->color.b /= 255.0f;
	free_strs(split);
	return (1);
}
