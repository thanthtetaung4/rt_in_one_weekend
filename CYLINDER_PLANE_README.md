# Cylinder and Plane Ray Tracing

This document explains how to use the new cylinder and plane ray tracing functions added to the ray tracer.

## New Object Types

### Cylinder
```c
typedef struct s_cylinder {
    t_vec3 center;      // Center point of the cylinder
    t_vec3 axis;        // Normalized direction vector (cylinder orientation)
    double radius;      // Radius of the cylinder
    double height;      // Height of the cylinder
    t_color color;      // Color of the cylinder
} t_cylinder;
```

### Plane
```c
typedef struct s_plane {
    t_vec3 point;       // A point on the plane
    t_vec3 normal;      // Normalized normal vector
    t_color color;      // Color of the plane
} t_plane;
```

## Ray Intersection Functions

### Cylinder Intersection
```c
void IntersectRayCylinder(t_vec3 O, t_vec3 D, t_cylinder cylinder, double *t1, double *t2);
```
- `O`: Ray origin
- `D`: Ray direction (normalized)
- `cylinder`: Cylinder object
- `t1`, `t2`: Intersection distances (set to DBL_MAX if no intersection)

The cylinder intersection handles:
- Infinite cylinder body intersection
- Height constraints (finite cylinder)
- End cap intersections (top and bottom)

### Plane Intersection
```c
void IntersectRayPlane(t_vec3 O, t_vec3 D, t_plane plane, double *t);
```
- `O`: Ray origin
- `D`: Ray direction (normalized)
- `plane`: Plane object
- `t`: Intersection distance (set to DBL_MAX if no intersection)

## Rendering Functions

### Render with Cylinders
```c
void render_scene_with_cylinders(FILE *f, t_camera camera,
                                t_sphere *spheres, int num_spheres,
                                t_cylinder *cylinders, int num_cylinders,
                                int width, int height);
```

### Render with Planes
```c
void render_scene_with_planes(FILE *f, t_camera camera,
                             t_sphere *spheres, int num_spheres,
                             t_cylinder *cylinders, int num_cylinders,
                             t_plane *planes, int num_planes,
                             int width, int height);
```

## Example Usage

```c
// Create a vertical cylinder
t_cylinder cylinder = {
    .center = {0, 0, 5},
    .axis = vec3_normalize(vec3_create(0, 1, 0)), // vertical
    .radius = 0.5,
    .height = 2.0,
    .color = {255, 0, 255} // magenta
};

// Create a horizontal plane
t_plane plane = {
    .point = {0, 0, 8},
    .normal = vec3_normalize(vec3_create(0, 0, -1)), // facing camera
    .color = {0, 255, 255} // cyan
};

// Render scene with all object types
render_scene_with_planes(f, camera, spheres, num_spheres,
                        &cylinder, 1, &plane, 1, width, height);
```

## Implementation Details

### Cylinder Intersection Algorithm
1. **Body intersection**: Uses quadratic equation for infinite cylinder
2. **Height constraints**: Projects intersection points onto cylinder axis
3. **End caps**: Checks intersection with circular end caps

### Plane Intersection Algorithm
1. **Ray-plane intersection**: Uses parametric line-plane intersection
2. **Parallel check**: Handles rays parallel to plane
3. **Behind check**: Ensures intersection is in front of ray origin

## Notes
- All vectors (axis, normal) should be normalized
- The cylinder height is centered around the center point
- Planes are infinite in extent
- The ray tracer finds the closest intersection among all objects
