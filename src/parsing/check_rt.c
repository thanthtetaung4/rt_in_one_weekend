/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_rt.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taung <taung@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 19:24:19 by taung             #+#    #+#             */
/*   Updated: 2025/07/15 15:55:10 by taung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	count_obj(char *filename, int *ambient_count, int *light_count,
		int *camera_count)
{
	char	*line;
	int		fd;

	fd = open(filename, O_RDONLY);
	line = gnl(fd);
	while (line)
	{
		if (line[0] == 'A')
			(*ambient_count)++;
		else if (line[0] == 'L')
			(*light_count)++;
		else if (line[0] == 'C')
			(*camera_count)++;
		free(line);
		line = gnl(fd);
	}
}

int	check_objs(char *filename)
{
	int	ambient_count;
	int	light_count;
	int	camera_count;

	ambient_count = 0;
	light_count = 0;
	camera_count = 0;
	count_obj(filename, &ambient_count, &light_count, &camera_count);
	if (ambient_count != 1)
		return (print_error("Error:: A != 1\n"));
	if (light_count < 1)
		return (print_error("Error:: L < 1\n"));
	if (camera_count != 1)
		return (print_error("Error:: C != 1\n"));
	return (1);
}
