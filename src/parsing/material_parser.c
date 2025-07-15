/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   material_parser.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taung <taung@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 17:34:58 by taung             #+#    #+#             */
/*   Updated: 2025/07/15 15:54:27 by taung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	init_mat(t_material *mat)
{
	mat->ambient = 0.2;
	mat->diffuse = 0.7;
	mat->specular = 0.2;
	mat->shininess = 20;
}

static int	check_mat_properties(double diff, double spec, double amb,
		double shine)
{
	if (!check_range(diff, 0.0, 1.0) || !check_range(spec, 0.0, 1.0)
		|| !check_range(amb, 0.0, 1.0) || !check_range(shine, 0, 100))
		return (0);
	return (1);
}

int	parse_material_i(const char *spc, const char *mir, t_material *mat)
{
	char	**tmp;

	init_mat(mat);
	tmp = ft_split(spc, ":,");
	if (tmp)
	{
		if (ft_strslen(tmp) != 3 || !ft_atof_vali(tmp[1], &mat->specular)
			|| !ft_atof_vali(tmp[2], &mat->shininess))
			return (0);
		free_strs(tmp);
		tmp = NULL;
	}
	tmp = ft_split(mir, ":,");
	if (tmp)
	{
		if (ft_strslen(tmp) != 3 || !ft_atof_vali(tmp[1], &mat->ambient)
			|| !ft_atof_vali(tmp[2], &mat->diffuse))
			return (0);
		free_strs(tmp);
		tmp = NULL;
	}
	if (!check_mat_properties(mat->diffuse, mat->specular, mat->ambient,
			mat->shininess))
		return (print_error("Error:: Invalid material property\n"));
	return (1);
}
