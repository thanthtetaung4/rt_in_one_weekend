#ifndef PARSING_H
# define PARSING_H

# include "rt.h"

int	parse_ambient(char *line, t_ambient_light *ambient);
int	parse_camera(char *line, t_camera *camera);
int	parse_light(char *line, t_data *data);
int	parse_sphere(char *line, t_data *data);
int	parse_plane(char *line, t_data *data);
int	parse_cylinder(char *line, t_data *data);
int	parse_rgb(char *line, t_color *color);
int	parse_xyz(char *line, t_vec3 *vec, int is_vector);
int	parse_material(const char *spc, const char *mir, t_material *mat);
int	parser(char *filename, t_data *data);
void	count_onl(char *filename, t_data *data);
int	check_range(float value, float min, float max);
int	parse_ratio(char *line, t_scene *scene);

#endif
