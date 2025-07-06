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

// ======================= Material =======================
typedef struct s_material {
    t_color color;     // Base color
    double ambient;    // Ambient reflection coefficient (0.0 to 1.0)
    double diffuse;    // Diffuse reflection coefficient (0.0 to 1.0)
    double specular;   // Specular reflection coefficient (0.0 to 1.0)
    double shininess;  // Shininess exponent for specular highlights
} t_material;

// ======================= Sphere =======================
typedef struct s_sphere {
    t_vec3 center;
    double radius;
    t_material material;
} t_sphere;

// ======================= Cylinder =======================
typedef struct s_cylinder {
    t_vec3 center;
    t_vec3 axis;      // Normalized direction vector
    double radius;
    double height;
    t_material material;
} t_cylinder;

// ======================= Plane =======================
typedef struct s_plane {
    t_vec3 point;     // A point on the plane
    t_vec3 normal;    // Normalized normal vector
    t_material material;
} t_plane;

// ======================= Lighting =======================
typedef struct s_ambient_light {
    double intensity;  // Ambient light intensity (0.0 to 1.0)
    t_color color;     // Ambient light color
} t_ambient_light;

typedef struct s_point_light {
    t_vec3 position;   // Light position in 3D space
    double intensity;  // Light intensity
    t_color color;     // Light color
} t_point_light;

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
void IntersectRayCylinder(t_vec3 O, t_vec3 D, t_cylinder cylinder, double *t1, double *t2);
void IntersectRayPlane(t_vec3 O, t_vec3 D, t_plane plane, double *t);
t_color TraceRay(t_vec3 O, t_vec3 D, double t_min, double t_max,
                 t_sphere *spheres, int num_spheres, t_color background);
t_color TraceRayWithCylinders(t_vec3 O, t_vec3 D, double t_min, double t_max,
                              t_sphere *spheres, int num_spheres,
                              t_cylinder *cylinders, int num_cylinders,
                              t_color background);
t_color TraceRayWithPlanes(t_vec3 O, t_vec3 D, double t_min, double t_max,
                           t_sphere *spheres, int num_spheres,
                           t_cylinder *cylinders, int num_cylinders,
                           t_plane *planes, int num_planes,
                           t_color background);
t_color TraceRayWithLighting(t_vec3 O, t_vec3 D, double t_min, double t_max,
                             t_sphere *spheres, int num_spheres,
                             t_cylinder *cylinders, int num_cylinders,
                             t_plane *planes, int num_planes,
                             t_ambient_light ambient,
                             t_point_light *lights, int num_lights,
                             t_color background);

// Lighting functions
t_color calculate_lighting(t_vec3 hit_point, t_vec3 normal, t_vec3 view_direction,
                          t_material material, t_ambient_light ambient,
                          t_point_light *lights, int num_lights,
                          t_sphere *spheres, int num_spheres,
                          t_cylinder *cylinders, int num_cylinders,
                          t_plane *planes, int num_planes);
t_color color_multiply(t_color a, t_color b);
t_color color_scale(t_color color, double factor);
t_color color_add(t_color a, t_color b);
t_color color_clamp(t_color color);

// Camera functions
t_camera_view setup_camera(t_camera camera, int image_width, int image_height);

// Render functions
void render_scene(FILE *f, t_camera camera, t_sphere *spheres, int num_spheres,
                  int width, int height);
void render_scene_with_cylinders(FILE *f, t_camera camera,
                                t_sphere *spheres, int num_spheres,
                                t_cylinder *cylinders, int num_cylinders,
                                int width, int height);
void render_scene_with_planes(FILE *f, t_camera camera,
                             t_sphere *spheres, int num_spheres,
                             t_cylinder *cylinders, int num_cylinders,
                             t_plane *planes, int num_planes,
                             int width, int height);
void render_scene_with_lighting(FILE *f, t_camera camera,
                               t_sphere *spheres, int num_spheres,
                               t_cylinder *cylinders, int num_cylinders,
                               t_plane *planes, int num_planes,
                               t_ambient_light ambient,
                               t_point_light *lights, int num_lights,
                               int width, int height);

// Scene setup functions
void setup_box_scene(t_sphere **spheres, int *num_spheres,
                     t_cylinder **cylinders, int num_cylinders,
                     t_plane **planes, int *num_planes,
                     t_ambient_light *ambient,
                     t_point_light **lights, int *num_lights);
void free_scene(t_sphere *spheres, t_cylinder *cylinders,
                t_plane *planes, t_point_light *lights);

# endif
