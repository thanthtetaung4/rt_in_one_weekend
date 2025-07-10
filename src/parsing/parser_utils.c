/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taung <taung@student.42singapore.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 12:37:25 by taung             #+#    #+#             */
/*   Updated: 2025/07/10 17:17:42 by taung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int	count_row(const char *path)
{
	int		fd;
	char	*res;
	int		i;

	i = 0;
	fd = open(path, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd("INVALID PATH\n", 2);
		return (0);
	}
	res = gnl(fd);
	if (!res)
		return (0);
	while (res)
	{
		free(res);
		res = NULL;
		i++;
		res = gnl(fd);
	}
	close(fd);
	free(res);
	return (i);
}

int	check_range(float value, float min, float max)
{
	if (value < min || value > max)
		return (0);
	return (1);
}

void	count_onl(char *filename, t_data *data)
{
	char	*line;
	int		fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (ft_putstr_fd("INVALID PATH\n", 2));
	line = gnl(fd);
	while(line)
	{
		if(line[0] == 'l')
			data->scene->num_lights++;
		if(line[0] == 'p' && line[1] && line[1] == 'l')
			data->scene->num_planes++;
		if(line[0] == 's' && line[1] && line[1] == 'p')
			data->scene->num_spheres++;
		if(line[0] == 'c' && line[1] && line[1] == 'y')
			data->scene->num_cylinders++;
		free(line);
		line = NULL;
		line = gnl(fd);
	}
	close(fd);
}
