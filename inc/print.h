# ifndef PRINT_H
# define PRINT_H

# include "rt.h"

void	print_xyz(t_vec3 origin);
void	print_rgb(t_color color);
int		print_2d_array(char **arr);
int	print_data(t_data data);
void	print_pl(t_plane *planes, int num_planes);
void	print_sp(t_sphere *spheres, int sp_count);
void	print_cy(t_cylinder *cylinders, int num_cylinders);
void	print_l(t_point_light *lights, int num_lights);


#endif
