# include "rt.h"

static void	init_mat(t_material *mat)
{
	mat->ambient = 0.1;
	mat->diffuse = 0.7;
	mat->specular = 0.2;
	mat->shininess = 20;
}

int	parse_material(const char *spc, const char *mir, t_material *mat)
{
	char	**tmp;
	int		len;

	// tmp = ft_split(str, ' ');
	init_mat(mat);
	// len = td_len(tmp);
	printf("%s, %s\n", spc, mir);
	return (1);
}
