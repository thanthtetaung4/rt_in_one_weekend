# ifndef RT_H
# define RT_H

# include <math.h>
# include <stdio.h>
# include <float.h>
# include <stdlib.h>
# include "vec3.h"
# include "color.h"
# include "ray.h"
# include "ft_math.h"

# define PI 3.14159265358979323846

// ======================= Color =======================
typedef struct s_color {
    int r, g, b;
} t_color;

// ======================= Sphere =======================
typedef struct s_sphere {
    t_vec3 center;
    double radius;
    t_color color;
} t_sphere;

// ======================= Camera =======================
typedef struct s_camera {
    t_vec3 P;     // Position
    t_vec3 D;     // Direction (normalized)
    double fov;   // Horizontal field of view in radians
} t_camera;

typedef struct s_camera_view {
    t_vec3 pixel00;
    t_vec3 pixel_delta_u;
    t_vec3 pixel_delta_v;
} t_camera_view;

// ======================= Function Declarations =======================

// Ray tracing functions
void IntersectRaySphere(t_vec3 O, t_vec3 D, t_sphere sphere, double *t1, double *t2);
t_color TraceRay(t_vec3 O, t_vec3 D, double t_min, double t_max,
                 t_sphere *spheres, int num_spheres, t_color background);

// Camera functions
t_camera_view setup_camera(t_camera camera, int image_width, int image_height);

// Render functions
void render_scene(FILE *f, t_camera camera, t_sphere *spheres, int num_spheres,
                  int width, int height);

# endif
