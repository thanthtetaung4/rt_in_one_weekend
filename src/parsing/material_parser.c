# include "rt.h"

static void	init_mat(t_material *mat)
{
	mat->ambient = 0.2;
	mat->diffuse = 0.7;
	mat->specular = 0.2;
	mat->shininess = 20;
}

int	parse_material(const char *spc, const char *mir, t_material *mat)
{
	char	**tmp;
	char	**tmp2;
	int		len;

	init_mat(mat);
	tmp = ft_split(spc, ":,");
	if (tmp)
	{
		print_2d_array(tmp);
		if (ft_strslen(tmp) != 3 || !ft_atof_vali(tmp[1], &mat->specular) || !ft_atof_vali(tmp[2], &mat->shininess))
			return (0);
		free_strs(tmp);
		tmp = NULL;
	}
	tmp = ft_split(mir, ":,");
	if (tmp)
	{
		print_2d_array(tmp);
		if (ft_strslen(tmp) != 3 || !ft_atof_vali(tmp[1], &mat->ambient) || !ft_atof_vali(tmp[2], &mat->diffuse))
			return (0);
		free_strs(tmp);
		tmp = NULL;
	}
	return (1);
}
