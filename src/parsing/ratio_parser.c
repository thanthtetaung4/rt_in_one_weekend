/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ratio_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taung <taung@student.42singapore.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 17:35:21 by taung             #+#    #+#             */
/*   Updated: 2025/07/10 17:35:23 by taung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int	parse_ratio(char *line, t_scene *scene)
{
	char	**split;

	split = ft_split(line, " \t\n");
	if (!split || !*split)
		return (0);
	if (ft_strslen(split) != 3 || !ft_atoi_vali(split[1], &scene->width)
		|| !ft_atoi_vali(split[2], &scene->height))
		return (0);
	return (free_strs(split), 1);
}
