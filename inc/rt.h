/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taung <taung@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 03:32:03 by taung             #+#    #+#             */
/*   Updated: 2025/07/15 14:00:17 by taung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H

# include "gnl.h"
# include "libft.h"
# include "vec3.h"
# include <float.h>
# include <math.h>
# include <mlx.h>
# include <stdio.h>

# define WIDTH 800
# define HEIGHT 600
# define PI 3.14159265358979323846

// ======================= Color =======================
typedef struct s_color
{
	int				r;
	int				g;
	int				b;
}					t_color;

// ======================= Material =======================
typedef struct s_material
{
	t_color			color;
	double			ambient;
	double			diffuse;
	double			specular;
	double			shininess;
}					t_material;

typedef struct s_hit
{
	double			t;
	t_vec3			point;
	t_vec3			normal;
	t_material		material;
	int				hit;
}					t_hit;

// ======================= Sphere =======================
typedef struct s_sphere
{
	t_vec3			center;
	double			radius;
	t_material		material;
}					t_sphere;

// ======================= Cylinder =======================
typedef struct s_cylinder
{
	t_vec3			center;
	t_vec3			axis;
	double			radius;
	double			half_height;
	t_material		material;
}					t_cylinder;

// ======================= Plane =======================
typedef struct s_plane
{
	t_vec3			point;
	t_vec3			normal;
	t_material		material;
}					t_plane;

// ======================= Ray =======================
typedef struct s_ray
{
	t_vec3			origin;
	t_vec3			dir;
	double			t_min;
	double			t_max;
}					t_ray;

// ======================= Lighting =======================
typedef struct s_ambient_light
{
	double			intensity;
	t_color			color;
}					t_ambient_light;

typedef struct s_point_light
{
	t_vec3			position;
	double			intensity;
	t_color			color;
}					t_point_light;

// ======================= Camera =======================
typedef struct s_camera
{
	t_vec3			p;
	t_vec3			d;
	double			fov;
	t_vec3			dir_forward;
	t_vec3			dir_right;
	t_vec3			dir_up;
	t_vec3			foc_point;
}					t_camera;

typedef struct s_camera_view
{
	double			width;
	double			height;
	t_vec3			upper_left;
	t_vec3			pixel00;
	t_vec3			pixel_delta_u;
	t_vec3			pixel_delta_v;
}					t_camera_view;

// ======================= Scene Data Structure =======================
typedef struct s_scene
{
	// Camera
	t_camera		camera;

	// Scene objects
	t_sphere		*spheres;
	int				num_spheres;
	t_cylinder		*cylinders;
	int				num_cylinders;
	t_plane			*planes;
	int				num_planes;

	// Iterators
	int				sp_i;
	int				pl_i;
	int				l_i;
	int				cy_i;

	// Lighting
	t_ambient_light	ambient;
	t_point_light	*lights;
	int				num_lights;

	// Background color
	t_color			background;

	// Image dimensions
	int				width;
	int				height;
}					t_scene;

typedef struct s_data
{
	void			*mlx;
	void			*mlx_win;
	t_scene			*scene;

}					t_data;

typedef struct s_gch_calc
{
	t_hit			hit;
	t_vec3			to_center;
	double			projection;
	double			half_height;
	t_vec3			top_center;
	t_vec3			bottom_center;
	t_vec3			normal;
}					t_gch_calc;

typedef struct s_quadratic
{
	double			a;
	double			b;
	double			c;
	double			discriminant;
	double			t1;
	double			t2;
	t_vec3			co;
}					t_quadratic;

// ======================= Function Declarations =======================

// Mlx control functions
int					key_hook(int keycode, void *param);
int					close_hook(t_data *data);
int					color_to_mlx(t_color color);

// Scene management functions
int					create_scene(char *file_name, t_data *data);
void				free_scene(t_scene *scene);

// Ray tracing functions
void				render_to_mlx_image(t_scene *scene, t_data *data);
t_ray				init_ray(t_vec3 origin, t_vec3 dir, double t_min,
						double t_max);
void				intersect_sphere(t_ray ray, t_sphere sphere, double *t1,
						double *t2);
t_hit				hit_spheres(t_ray ray, int num_spheres, t_sphere *spheres,
						t_hit closest_hit);

void				intersect_cylinder(t_ray ray, t_cylinder cylinder,
						double *t1, double *t2);
t_hit				hit_cylinders(t_ray ray, int num_cylinders,
						t_cylinder *cylinders, t_hit closest_hit);

void				intersect_plane(t_ray ray, t_plane plane, double *t);
t_hit				hit_planes(t_ray ray, int num_planes, t_plane *planes,
						t_hit closest_hit);

t_color				trace_ray(t_ray ray, t_scene *scene);

// Lighting functions
int					check_light_positions(const t_scene *scene,
						t_point_light light);
t_color				calculate_lighting(t_hit hit, t_vec3 view_direction,
						t_scene *scene);
t_color				color_multiply(t_color a, t_color b);
t_color				color_scale(t_color color, double factor);
t_color				color_add(t_color a, t_color b);
t_color				color_clamp(t_color color);
int					is_in_shadow(t_vec3 hit_point, t_vec3 light_direction,
						double light_distance, t_scene *scene);
int					is_light_on_plane(t_point_light light, t_plane plane);

// Camera functions
t_camera_view		setup_camera(t_camera camera, t_scene *scene);
int					check_c_pos(const t_scene *scene, t_camera camera,
						t_point_light light);

// Render functions
void				render_scene(FILE *f, t_scene *scene);
void				render_scene_with_cylinders(FILE *f, t_scene *scene);
void				render_scene_with_planes(FILE *f, t_scene *scene);
void				render_scene_with_lighting(FILE *f, t_scene *scene);

int					parse_rt_file(const char *filename, t_scene *scene);

// Error
int					print_error(char *msg);

// Utils
double				degrees_to_radians(double degrees);
double				ft_fabs(double x);

// Print functions
void				print_xyz(t_vec3 origin);
void				print_rgb(t_color color);
int					print_2d_array(char **arr);
int					print_data(t_data data);
void				print_pl(t_plane *planes, int num_planes);
void				print_sp(t_sphere *spheres, int sp_count);
void				print_cy(t_cylinder *cylinders, int num_cylinders);
void				print_pl(t_plane *planes, int num_planes);
void				print_sp(t_sphere *spheres, int sp_count);
void				print_cy(t_cylinder *cylinders, int num_cylinders);
void				print_l(t_point_light *lights, int num_lights);
void				print_mat(t_material mat);

// Parsing functions
int					parse_ambient(char *line, t_ambient_light *ambient);
int					parse_camera(char *line, t_camera *camera);
int					parse_light(char *line, t_data *data);
int					parse_sphere(char *line, t_data *data);
int					parse_plane(char *line, t_data *data);
int					parse_cylinder(char *line, t_data *data);
int					parse_rgb(char *line, t_color *color);
int					parse_xyz(char *line, t_vec3 *vec, int is_vector);
int					parse_material_i(const char *spc, const char *mir,
						t_material *mat);
int					parser(char *filename, t_data *data);
void				count_onl(char *filename, t_data *data);
int					check_range(float value, float min, float max);
int					check_dir(t_vec3 d, float min, float max);
int					parse_ratio(char *line, t_scene *scene);
void				init_mat(t_material *mat);
int					alloc_sp(t_data *data);
int					alloc_l(t_data *data);
int					alloc_cy(t_data *data);
int					alloc_pl(t_data *data);
int					init_scene(char *filename, t_data *data);
int					check_objs(char *filename);

// Free
void				free_data(t_data *data);
#endif
