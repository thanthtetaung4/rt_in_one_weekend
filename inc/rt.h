/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoo <aoo@student.42singapore.sg>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 03:32:03 by taung             #+#    #+#             */
/*   Updated: 2025/07/09 07:12:34 by aoo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H

# include "gnl.h"
# include "color.h"
# include "ft_math.h"
# include "ray.h"
# include "vec3.h"
# include <float.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <mlx.h>

# define PI 3.14159265358979323846

// ======================= Color =======================
typedef struct s_color
{
	int r, g, b;
}					t_color;

// ======================= Material =======================
typedef struct s_material
{
	t_color color;    // Base color
	double ambient;   // Ambient reflection coefficient (0.0 to 1.0)
	double diffuse;   // Diffuse reflection coefficient (0.0 to 1.0)
	double specular;  // Specular reflection coefficient (0.0 to 1.0)
	double shininess; // Shininess exponent for specular highlights
}					t_material;

typedef struct s_hit
{
	double		t;
	t_vec3		point;
	t_vec3		normal;
	t_material	material;
	int			hit;
}	t_hit;

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
	t_vec3 axis; // Normalized direction vector
	double			radius;
	double			height;
	t_material		material;
}					t_cylinder;

// ======================= Plane =======================
typedef struct s_plane
{
	t_vec3 point;  // A point on the plane
	t_vec3 normal; // Normalized normal vector
	t_material		material;
}					t_plane;

// ======================= Lighting =======================
typedef struct s_ambient_light
{
	double intensity; // Ambient light intensity (0.0 to 1.0)
	t_color color;    // Ambient light color
}					t_ambient_light;

typedef struct s_point_light
{
	t_vec3 position;  // Light position in 3D space
	double intensity; // Light intensity
	t_color color;    // Light color
}					t_point_light;

// ======================= Camera =======================
typedef struct s_camera
{
	t_vec3	P;   // Position
	t_vec3	D;   // Direction (normalized)
	double	fov; // Horizontal field of view in radians
	t_vec3	dir_forward;
	t_vec3	dir_right;
	t_vec3	dir_up;
	t_vec3	foc_point;
}					t_camera;

typedef struct s_camera_view
{
	double			width;
	double			height;
	t_vec3			upper_left;
	t_vec3			pixel00;
	t_vec3			pixel_delta_u;
	t_vec3			pixel_delta_v;
}	t_camera_view;

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

typedef struct  s_data
{
	void	*mlx;
	void	*mlx_win;
	t_scene	*scene;

}   t_data;


// ======================= Function Declarations =======================

// Scene management functions
t_scene				*create_scene(void);
void				free_scene(t_scene *scene);

// Ray tracing functions
void	IntersectRaySphere(t_ray ray, t_sphere sphere, double *t1, double *t2);
t_hit	get_sphere_hit(t_ray ray, t_sphere sphere, double t);
t_hit	hit_spheres(t_ray ray, int num_spheres, t_sphere *spheres, t_hit closest_hit);

void	IntersectRayCylinder(t_ray ray,t_cylinder cylinder, double *t1, double *t2);
t_hit	get_cylinder_hit(t_ray ray, t_cylinder cylinder, double t);
t_hit	hit_cylinders(t_ray ray, int num_cylinders, t_cylinder *cylinders, t_hit closest_hit);

void				IntersectRayPlane(t_ray ray, t_plane plane,
						double *t);
t_hit	get_plane_hit(t_ray ray, t_plane plane, double t);
t_hit	hit_planes(t_ray ray, int num_planes, t_plane *planes, t_hit closest_hit);


t_color				TraceRay(t_ray ray, t_scene *scene);

// Lighting functions
t_color				calculate_lighting(t_vec3 hit_point, t_vec3 normal,
						t_vec3 view_direction, t_material material,
						t_scene *scene);
t_color				color_multiply(t_color a, t_color b);
t_color				color_scale(t_color color, double factor);
t_color				color_add(t_color a, t_color b);
t_color				color_clamp(t_color color);

// Camera functions
t_camera_view		setup_camera(t_camera camera, t_scene *scene);

// Render functions
void				render_scene(FILE *f, t_scene *scene);
void				render_scene_with_cylinders(FILE *f, t_scene *scene);
void				render_scene_with_planes(FILE *f, t_scene *scene);
void				render_scene_with_lighting(FILE *f, t_scene *scene);

int					parse_rt_file(const char *filename, t_scene *scene);

// Error
int					print_error(char *msg);

#endif
