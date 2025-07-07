# Technical Documentation

This document provides detailed technical information about the ray tracing implementation, including mathematical foundations, algorithms, and implementation specifics.

## 📐 Mathematical Foundations

### Vector Mathematics

#### 3D Vector Operations
The ray tracer uses a complete 3D vector library for all geometric calculations:

```c
typedef struct s_vec3 {
    double x, y, z;
} t_vec3;
```

**Core Operations:**
- **Addition**: `vec3_add(a, b)` = (a.x + b.x, a.y + b.y, a.z + b.z)
- **Subtraction**: `vec3_sub(a, b)` = (a.x - b.x, a.y - b.y, a.z - b.z)
- **Scalar multiplication**: `vec3_scale(v, s)` = (v.x * s, v.y * s, v.z * s)
- **Dot product**: `vec3_dot(a, b)` = a.x * b.x + a.y * b.y + a.z * b.z
- **Cross product**: `vec3_cross(a, b)` = (a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x)
- **Normalization**: `vec3_normalize(v)` = v / ||v||

#### Vector Properties
- **Magnitude**: ||v|| = √(v.x² + v.y² + v.z²)
- **Unit vector**: Vector with magnitude 1
- **Orthogonal vectors**: Two vectors with dot product = 0

### Ray Representation

A ray is defined by an origin point and a direction vector:

```c
typedef struct s_ray {
    t_vec3 origin;      // Ray starting point
    t_vec3 direction;   // Normalized direction vector
} t_ray;
```

**Ray equation**: P(t) = origin + t * direction, where t ≥ 0

## 🎯 Ray-Object Intersections

The ray tracer supports three geometric primitives: spheres, cylinders, and planes. Each primitive has its own intersection algorithm and normal calculation method.

### Available Primitives

#### Sphere Intersection
- **File**: `SPHERE_INTERSECTION.md`
- **Algorithm**: Quadratic equation solution
- **Complexity**: O(1) per sphere
- **Features**: Complete mathematical derivation, implementation details, normal calculation, and usage examples

#### Cylinder Intersection
- **File**: `CYLINDER_INTERSECTION.md`
- **Algorithm**: Infinite cylinder + height constraints + end caps
- **Complexity**: O(1) per cylinder
- **Features**: Body and end cap intersections, comprehensive normal calculation, and edge case handling

#### Plane Intersection
- **File**: `PLANE_INTERSECTION.md`
- **Algorithm**: Direct plane equation solution
- **Complexity**: O(1) per plane
- **Features**: Infinite plane support, parallel ray handling, and numerical stability

### Common Intersection Interface

All intersection functions follow a consistent interface:

```c
// Sphere intersection
void IntersectRaySphere(t_vec3 O, t_vec3 D, t_sphere sphere, double *t1, double *t2);

// Cylinder intersection
void IntersectRayCylinder(t_vec3 O, t_vec3 D, t_cylinder cylinder, double *t1, double *t2);

// Plane intersection
void IntersectRayPlane(t_vec3 O, t_vec3 D, t_plane plane, double *t);
```

### Integration with Scene Structure

All intersection functions work seamlessly with the centralized scene management system:

```c
// Example: Testing all objects in a scene
t_scene *scene = create_scene();
setup_regular_scene(scene);

// Test spheres
for (int i = 0; i < scene->num_spheres; i++) {
    double t1, t2;
    IntersectRaySphere(ray_origin, ray_direction, scene->spheres[i], &t1, &t2);
    // Process intersection...
}

// Test cylinders
for (int i = 0; i < scene->num_cylinders; i++) {
    double t1, t2;
    IntersectRayCylinder(ray_origin, ray_direction, scene->cylinders[i], &t1, &t2);
    // Process intersection...
}

// Test planes
for (int i = 0; i < scene->num_planes; i++) {
    double t;
    IntersectRayPlane(ray_origin, ray_direction, scene->planes[i], &t);
    // Process intersection...
}
```

### Performance Characteristics

| Primitive | Time Complexity | Space Complexity | Typical Operations |
|-----------|----------------|------------------|-------------------|
| Sphere    | O(1)           | O(1)             | ~10 FP operations |
| Cylinder  | O(1)           | O(1)             | ~20-30 FP operations |
| Plane     | O(1)           | O(1)             | ~5 FP operations |

### Documentation Structure

Each primitive has its own comprehensive documentation file containing:
- **Mathematical foundation** and derivation
- **Implementation details** with complete code
- **Normal calculation** methods
- **Usage examples** and integration patterns
- **Performance considerations** and optimization tips
- **Testing strategies** and edge case handling
- **Related functions** and references

For detailed information about any specific primitive, refer to its dedicated documentation file.

## 🎬 Scene Management

### Scene Data Structure

The ray tracer uses a centralized scene management system that encapsulates all rendering data in a single structure:

```c
typedef struct s_scene {
    // Camera
    t_camera camera;

    // Scene objects
    t_sphere *spheres;
    int num_spheres;
    t_cylinder *cylinders;
    int num_cylinders;
    t_plane *planes;
    int num_planes;

    // Lighting
    t_ambient_light ambient;
    t_point_light *lights;
    int num_lights;

    // Background color
    t_color background;

    // Image dimensions
    int width;
    int height;
} t_scene;
```

### Scene Management Functions

#### Scene Creation and Cleanup
```c
// Create a new scene with default values
t_scene *create_scene(void);

// Free all scene memory
void free_scene(t_scene *scene);
```

#### Scene Setup Functions
```c
// Setup the regular demo scene
void setup_regular_scene(t_scene *scene);

// Setup the box scene with 4 black planes
void setup_box_scene(t_scene *scene);
```

### Benefits of Scene Structure

1. **Cleaner Function Signatures**: Functions no longer need long parameter lists
2. **Centralized Memory Management**: All scene data allocated and freed together
3. **Easier Scene Creation**: Predefined scene setups for different demos
4. **Better Organization**: All related data grouped together
5. **Extensibility**: Easy to add new scene properties or objects

### Updated Function Signatures

**Before (multiple parameters):**
```c
t_color TraceRayWithLighting(t_vec3 O, t_vec3 D, double t_min, double t_max,
                             t_sphere *spheres, int num_spheres,
                             t_cylinder *cylinders, int num_cylinders,
                             t_plane *planes, int num_planes,
                             t_ambient_light ambient,
                             t_point_light *lights, int num_lights,
                             t_color background);
```

**After (single scene parameter):**
```c
t_color TraceRayWithLighting(t_vec3 O, t_vec3 D, double t_min, double t_max, t_scene *scene);
```

## 💡 Lighting Model

### Phong Lighting Model

The lighting calculation combines three components:

#### 1. Ambient Lighting
Provides base illumination to prevent completely dark areas:
```
I_ambient = k_a × I_a
```
Where:
- k_a = material ambient coefficient
- I_a = ambient light intensity

#### 2. Diffuse Lighting (Lambertian Reflection)
Models matte surfaces that scatter light equally in all directions:
```
I_diffuse = k_d × I_l × max(0, N · L)
```
Where:
- k_d = material diffuse coefficient
- I_l = light intensity
- N = surface normal
- L = light direction

#### 3. Specular Lighting (Blinn-Phong)
Models shiny surfaces with specular highlights:
```
I_specular = k_s × I_l × max(0, N · H)^shininess
```
Where:
- k_s = material specular coefficient
- H = half-vector = normalize(V + L)
- V = view direction
- shininess = material shininess exponent

#### Implementation
```c
t_color calculate_lighting(t_vec3 hit_point, t_vec3 normal, t_vec3 view_direction,
                          t_material material, t_ambient_light ambient,
                          t_point_light *lights, int num_lights, ...) {
    t_color final_color = {0, 0, 0};

    // Ambient component
    t_color ambient_color = color_multiply(material.color, ambient.color);
    ambient_color = color_scale(ambient_color, material.ambient * ambient.intensity);
    final_color = color_add(final_color, ambient_color);

    // For each light source
    for (int i = 0; i < num_lights; i++) {
        t_point_light light = lights[i];
        t_vec3 light_direction = vec3_normalize(vec3_sub(light.position, hit_point));

        // Check shadows
        if (is_in_shadow(hit_point, light_direction, ...)) {
            continue;
        }

        // Diffuse component
        double diffuse_factor = vec3_dot(normal, light_direction);
        if (diffuse_factor > 0) {
            t_color diffuse_color = color_multiply(material.color, light.color);
            diffuse_color = color_scale(diffuse_color,
                material.diffuse * diffuse_factor * light.intensity);
            final_color = color_add(final_color, diffuse_color);
        }

        // Specular component (Blinn-Phong)
        t_vec3 half_vector = vec3_normalize(vec3_add(view_direction, light_direction));
        double specular_factor = vec3_dot(normal, half_vector);
        if (specular_factor > 0) {
            specular_factor = pow(specular_factor, material.shininess);
            t_color specular_color = color_multiply(material.color, light.color);
            specular_color = color_scale(specular_color,
                material.specular * specular_factor * light.intensity);
            final_color = color_add(final_color, specular_color);
        }
    }

    return color_clamp(final_color);
}
```

## 🎥 Camera System

### Perspective Camera

The camera is defined by:
- **Position**: Camera location in 3D space
- **Direction**: View direction (normalized)
- **Field of View**: Horizontal angle of view

#### View Plane Setup
```c
typedef struct s_camera_view {
    t_vec3 pixel00;        // Top-left pixel position
    t_vec3 pixel_delta_u;  // Horizontal pixel spacing
    t_vec3 pixel_delta_v;  // Vertical pixel spacing
} t_camera_view;
```

#### Camera Setup Algorithm
1. Calculate view plane dimensions based on FOV
2. Determine view plane orientation
3. Calculate pixel grid parameters
4. Set up ray generation parameters

```c
t_camera_view setup_camera(t_camera camera, int image_width, int image_height) {
    t_camera_view view;

    // Calculate view plane dimensions
    double viewport_height = 2.0 * tan(camera.fov / 2.0);
    double viewport_width = viewport_height * (image_width / (double)image_height);

    // Calculate view plane vectors
    t_vec3 viewport_u = vec3_scale(vec3_create(viewport_width, 0, 0), 1.0);
    t_vec3 viewport_v = vec3_scale(vec3_create(0, -viewport_height, 0), 1.0);

    // Calculate pixel deltas
    view.pixel_delta_u = vec3_scale(viewport_u, 1.0 / image_width);
    view.pixel_delta_v = vec3_scale(viewport_v, 1.0 / image_height);

    // Calculate top-left pixel position
    t_vec3 viewport_upper_left = vec3_sub(camera.P,
        vec3_scale(camera.D, 1.0));
    viewport_upper_left = vec3_sub(viewport_upper_left,
        vec3_scale(viewport_u, 0.5));
    viewport_upper_left = vec3_sub(viewport_upper_left,
        vec3_scale(viewport_v, 0.5));

    view.pixel00 = vec3_add(viewport_upper_left,
        vec3_scale(vec3_add(view.pixel_delta_u, view.pixel_delta_v), 0.5));

    return view;
}
```

## 🎨 Color System

### RGB Color Representation
Colors are represented as RGB triplets with values 0-255:

```c
typedef struct s_color {
    int r, g, b;
} t_color;
```

### Color Operations

#### Color Multiplication (Component-wise)
```c
t_color color_multiply(t_color a, t_color b) {
    return (t_color){
        (a.r * b.r) / 255,
        (a.g * b.g) / 255,
        (a.b * b.b) / 255
    };
}
```

#### Color Scaling
```c
t_color color_scale(t_color color, double factor) {
    return (t_color){
        (int)(color.r * factor),
        (int)(color.g * factor),
        (int)(color.b * factor)
    };
}
```

#### Color Addition
```c
t_color color_add(t_color a, t_color b) {
    return (t_color){
        a.r + b.r,
        a.g + b.g,
        a.b + b.b
    };
}
```

#### Color Clamping
```c
t_color color_clamp(t_color color) {
    return (t_color){
        (color.r > 255) ? 255 : (color.r < 0) ? 0 : color.r,
        (color.g > 255) ? 255 : (color.g < 0) ? 0 : color.g,
        (color.b > 255) ? 255 : (color.b < 0) ? 0 : color.b
    };
}
```

## 🌑 Shadow Casting

### Shadow Ray Algorithm
For each light source, cast a ray from the hit point toward the light:

1. **Shadow ray setup**: origin = hit_point, direction = light_direction
2. **Intersection testing**: Check all objects for intersection
3. **Distance comparison**: If intersection distance < light distance, point is in shadow
4. **Epsilon offset**: Use small offset to prevent self-shadowing

```c
int is_in_shadow(t_vec3 hit_point, t_vec3 light_direction, double light_distance, ...) {
    t_vec3 shadow_ray_origin = hit_point;
    t_vec3 shadow_ray_direction = light_direction;

    // Check all objects for intersection
    for (int i = 0; i < num_spheres; i++) {
        double t1, t2;
        IntersectRaySphere(shadow_ray_origin, shadow_ray_direction, spheres[i], &t1, &t2);
        if (t1 > 0.001 && t1 < light_distance) return 1;  // In shadow
        if (t2 > 0.001 && t2 < light_distance) return 1;  // In shadow
    }

    // Similar checks for cylinders and planes...

    return 0;  // Not in shadow
}
```

## ⚡ Performance Optimizations

### Early Termination
Stop intersection testing when the closest object is found:
```c
if (t1 >= t_min && t1 <= t_max && t1 < closest_t) {
    closest_t = t1;
    closest_object = &objects[i];
}
```

### Shadow Ray Optimization
- Use small epsilon (0.001) for shadow ray origins to prevent self-shadowing
- Early termination when any intersection is found
- Skip shadow testing for very distant lights

### Memory Management
- Use stack allocation for temporary calculations
- Minimize dynamic allocation during rendering
- Proper cleanup of scene objects

## 🔧 MLX Integration

### Window Management
```c
// Initialize MLX
mlx_ptr = mlx_init();
win_ptr = mlx_new_window(mlx_ptr, width, height, "Ray Tracer");

// Set up event hooks
mlx_key_hook(win_ptr, key_hook, NULL);
mlx_hook(win_ptr, 17, 0, close_hook, NULL);  // Close button event
```

### Pixel Drawing
```c
// Convert color to MLX format
int color_to_mlx(t_color color) {
    return (color.r << 16) | (color.g << 8) | color.b;
}

// Draw pixel
mlx_pixel_put(mlx_ptr, win_ptr, x, y, mlx_color);
```

### Event Handling
```c
int key_hook(int keycode, void *param) {
    if (keycode == 65307) {  // ESC key
        mlx_destroy_window(mlx_ptr, win_ptr);
        mlx_destroy_display(mlx_ptr);
        free(mlx_ptr);
        exit(0);
    }
    return 0;
}
```

## 📊 Algorithm Complexity

### Time Complexity
- **Ray-object intersection**: O(n) where n = number of objects
- **Shadow casting**: O(n × m) where m = number of lights
- **Overall rendering**: O(width × height × n × m)

### Space Complexity
- **Scene objects**: O(n) for object storage
- **Rendering**: O(1) per pixel (no frame buffer storage)
- **Temporary calculations**: O(1) stack space

## 🧪 Testing and Validation

### Mathematical Validation
- **Sphere intersection**: Verified against analytical solutions
- **Cylinder intersection**: Tested with known intersection points
- **Plane intersection**: Validated with geometric calculations
- **Lighting model**: Compared with reference implementations

### Visual Validation
- **Shadow accuracy**: Verified shadow positions and shapes
- **Material appearance**: Confirmed lighting model behavior
- **Color accuracy**: Tested color mixing and clamping
- **Geometric accuracy**: Validated object shapes and positions

## 🔍 Debugging Techniques

### Intersection Debugging
```c
// Add debug output for intersection testing
printf("Ray: origin(%.2f,%.2f,%.2f) dir(%.2f,%.2f,%.2f)\n",
       O.x, O.y, O.z, D.x, D.y, D.z);
printf("Sphere: center(%.2f,%.2f,%.2f) radius=%.2f\n",
       sphere.center.x, sphere.center.y, sphere.center.z, sphere.radius);
printf("Intersection: t1=%.4f t2=%.4f\n", t1, t2);
```

### Lighting Debugging
```c
// Debug lighting calculations
printf("Hit point: (%.2f,%.2f,%.2f)\n", hit_point.x, hit_point.y, hit_point.z);
printf("Normal: (%.2f,%.2f,%.2f)\n", normal.x, normal.y, normal.z);
printf("Light direction: (%.2f,%.2f,%.2f)\n", light_direction.x, light_direction.y, light_direction.z);
printf("Diffuse factor: %.4f\n", diffuse_factor);
```

### Color Debugging
```c
// Debug color values
printf("Material color: (%d,%d,%d)\n", material.color.r, material.color.g, material.color.b);
printf("Final color: (%d,%d,%d)\n", final_color.r, final_color.g, final_color.b);
```

## 🏗️ Build and Executables

By default, only the main ray tracer executable (`rt`) is built. To build the box scene (`rt_box`) or pipe scene (`rt_pipe`), uncomment the relevant lines in the Makefile and run:

```bash
make rt_box
make rt_pipe
```

This technical documentation provides the mathematical foundations and implementation details necessary for understanding and extending the ray tracer implementation.
