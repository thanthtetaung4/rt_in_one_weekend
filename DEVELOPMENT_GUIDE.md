# Development Guide

This guide is for developers who want to understand, modify, or extend the ray tracer codebase.

## 🏗️ Codebase Architecture

### Project Structure
```
rt_in_one_weekend/
├── inc/                    # Header files and interfaces
│   ├── rt.h               # Main structures and function declarations
│   ├── vec3.h             # Vector operations interface
│   ├── ray.h              # Ray structure definition
│   ├── color.h            # Color utilities interface
│   └── ft_math.h          # Math utilities interface
├── src/                   # Source code implementation
│   ├── main.c             # Main application entry point
│   ├── main_box.c         # Box scene demo application
│   ├── utils/             # Utility function implementations
│   │   ├── camera_utils.c # Camera setup and view calculations
│   │   ├── color_utils.c  # Color manipulation functions
│   │   ├── lighting_utils.c # Lighting calculations and shadows
│   │   ├── math_utils.c   # Mathematical operations
│   │   ├── ray_utils.c    # Ray-object intersection algorithms
│   │   ├── render_utils.c # Rendering pipeline functions
│   │   └── scene_utils.c  # Scene management and setup functions
│   └── vec3/              # Vector operations implementation
│       └── vec3.c
├── libft/                 # Custom C library functions
├── mlx/                   # MiniLibX graphics library
└── Makefile               # Build configuration
```

### Design Patterns

#### 1. Separation of Concerns
- **Headers**: Interface definitions and structure declarations
- **Implementation**: Algorithm implementations in separate files
- **Utilities**: Reusable functions organized by functionality
- **Main**: Application logic and scene setup

#### 2. Data Structures
```c
// Scene management (centralized)
typedef struct s_scene {
    t_camera camera;
    t_sphere *spheres;
    int num_spheres;
    t_cylinder *cylinders;
    int num_cylinders;
    t_plane *planes;
    int num_planes;
    t_ambient_light ambient;
    t_point_light *lights;
    int num_lights;
    t_color background;
    int width;
    int height;
} t_scene;

// Geometric primitives
typedef struct s_sphere { ... } t_sphere;
typedef struct s_cylinder { ... } t_cylinder;
typedef struct s_plane { ... } t_plane;

// Lighting components
typedef struct s_ambient_light { ... } t_ambient_light;
typedef struct s_point_light { ... } t_point_light;

// Material system
typedef struct s_material { ... } t_material;

// Camera system
typedef struct s_camera { ... } t_camera;
typedef struct s_camera_view { ... } t_camera_view;
```

#### 3. Function Organization
- **Intersection functions**: Ray-object intersection calculations
- **Lighting functions**: Material and lighting model implementations
- **Utility functions**: Vector operations, color manipulation, math utilities
- **Rendering functions**: High-level rendering pipeline

## 🔧 Development Setup

### Prerequisites
```bash
# Install development dependencies
sudo apt-get update
sudo apt-get install build-essential git
sudo apt-get install libx11-dev libxext-dev

# Verify GCC version
gcc --version  # Should be 7.0 or higher
```

### Build System
The project uses a custom Makefile with the following targets:

```bash
# Build all executables
make

# Build specific executable
make rt        # Main ray tracer
make rt_box    # Box scene demo

# Clean build artifacts
make clean     # Remove object files
make fclean    # Remove all build artifacts

# Rebuild everything
make re        # Clean and rebuild
```

### Development Workflow
1. **Clone and setup**: `git clone <repo> && cd rt_in_one_weekend`
2. **Build**: `make`
3. **Test**: `./rt` and `./rt_box`
4. **Modify**: Edit source files
5. **Rebuild**: `make re`
6. **Test changes**: Run executables

## 📝 Coding Standards

### C Style Guidelines
```c
// Function naming: PascalCase for public functions
void IntersectRaySphere(t_vec3 O, t_vec3 D, t_sphere sphere, double *t1, double *t2);

// Variable naming: snake_case
t_vec3 ray_origin;
double intersection_distance;

// Struct naming: t_ prefix for types
typedef struct s_material {
    t_color color;
    double ambient;
    double diffuse;
    double specular;
    double shininess;
} t_material;

// Constants: UPPER_CASE
#define PI 3.14159265358979323846
#define MAX_OBJECTS 100
```

### Code Organization
```c
// Header file structure
#ifndef HEADER_NAME_H
#define HEADER_NAME_H

// Includes
#include <stdio.h>
#include <stdlib.h>

// Type definitions
typedef struct s_example {
    // ...
} t_example;

// Function declarations
void function_name(t_example *param);

#endif
```

### Documentation
```c
/**
 * Calculates the intersection of a ray with a sphere
 *
 * @param O Ray origin point
 * @param D Ray direction vector (normalized)
 * @param sphere Sphere to test against
 * @param t1 First intersection distance (output)
 * @param t2 Second intersection distance (output)
 *
 * @return void
 *
 * @note Returns DBL_MAX for t1 and t2 if no intersection
 */
void IntersectRaySphere(t_vec3 O, t_vec3 D, t_sphere sphere, double *t1, double *t2);
```

## 🚀 Adding New Features

### Adding a New Geometric Primitive

#### 1. Define the Structure
```c
// In inc/rt.h
typedef struct s_cube {
    t_vec3 center;
    t_vec3 size;        // Width, height, depth
    t_material material;
} t_cube;
```

#### 2. Implement Intersection Function
```c
// In src/utils/ray_utils.c
void IntersectRayCube(t_vec3 O, t_vec3 D, t_cube cube, double *t1, double *t2) {
    // Implement ray-cube intersection algorithm
    // Calculate intersection with cube faces
    // Return closest and farthest intersection points
}
```

#### 3. Add to Ray Tracing Pipeline
```c
// Modify TraceRayWithLighting function
t_color TraceRayWithLighting(t_vec3 O, t_vec3 D, double t_min, double t_max,
                             t_sphere *spheres, int num_spheres,
                             t_cylinder *cylinders, int num_cylinders,
                             t_plane *planes, int num_planes,
                             t_cube *cubes, int num_cubes,  // Add cubes
                             t_ambient_light ambient,
                             t_point_light *lights, int num_lights,
                             t_color background) {
    // Add cube intersection testing
    for (int i = 0; i < num_cubes; i++) {
        double t1, t2;
        IntersectRayCube(O, D, cubes[i], &t1, &t2);
        // Handle intersection results
    }
}
```

#### 4. Update Build System
```c
# In Makefile, add new source files
SRCS += $(UTILS)/cube_utils.c
```

### Adding New Material Properties

#### 1. Extend Material Structure
```c
typedef struct s_material {
    t_color color;
    double ambient;
    double diffuse;
    double specular;
    double shininess;
    double reflectivity;    // New property
    double transparency;    // New property
    double refractive_index; // New property
} t_material;
```

#### 2. Implement New Lighting Effects
```c
// In src/utils/lighting_utils.c
t_color calculate_reflection(t_vec3 hit_point, t_vec3 normal, t_vec3 view_direction,
                            t_material material, ...) {
    // Implement reflection calculation
}

t_color calculate_refraction(t_vec3 hit_point, t_vec3 normal, t_vec3 view_direction,
                            t_material material, ...) {
    // Implement refraction calculation
}
```

#### 3. Update Lighting Function
```c
t_color calculate_lighting(...) {
    t_color final_color = {0, 0, 0};

    // Existing lighting calculations...

    // Add reflection
    if (material.reflectivity > 0) {
        t_color reflection = calculate_reflection(...);
        final_color = color_add(final_color,
            color_scale(reflection, material.reflectivity));
    }

    // Add refraction
    if (material.transparency > 0) {
        t_color refraction = calculate_refraction(...);
        final_color = color_add(final_color,
            color_scale(refraction, material.transparency));
    }

    return color_clamp(final_color);
}
```

### Adding New Light Types

#### 1. Define Light Structure
```c
typedef struct s_directional_light {
    t_vec3 direction;    // Normalized direction
    double intensity;
    t_color color;
} t_directional_light;

typedef struct s_spot_light {
    t_vec3 position;
    t_vec3 direction;    // Normalized direction
    double intensity;
    t_color color;
    double angle;        // Spotlight angle in radians
} t_spot_light;
```

#### 2. Implement Light Calculations
```c
// In src/utils/lighting_utils.c
t_color calculate_directional_lighting(t_vec3 hit_point, t_vec3 normal,
                                      t_directional_light light, ...) {
    // Calculate lighting from directional light
}

t_color calculate_spot_lighting(t_vec3 hit_point, t_vec3 normal,
                               t_spot_light light, ...) {
    // Calculate lighting from spotlight
}
```

## 🧪 Testing and Debugging

### Unit Testing
Create test functions for individual components:

```c
// In test_utils.c
void test_vector_operations() {
    t_vec3 a = vec3_create(1, 2, 3);
    t_vec3 b = vec3_create(4, 5, 6);
    t_vec3 sum = vec3_add(a, b);

    assert(sum.x == 5);
    assert(sum.y == 7);
    assert(sum.z == 9);
    printf("Vector addition test passed\n");
}

void test_sphere_intersection() {
    t_sphere sphere = {
        .center = vec3_create(0, 0, 3),
        .radius = 1.0
    };

    t_vec3 ray_origin = vec3_create(0, 0, 0);
    t_vec3 ray_direction = vec3_create(0, 0, 1);

    double t1, t2;
    IntersectRaySphere(ray_origin, ray_direction, sphere, &t1, &t2);

    assert(t1 == 2.0);  // Expected intersection distance
    assert(t2 == 4.0);  // Expected second intersection
    printf("Sphere intersection test passed\n");
}
```

### Integration Testing
Test complete rendering pipeline:

```c
void test_simple_scene() {
    // Setup minimal scene
    t_camera camera = {
        .P = vec3_create(0, 0, -5),
        .D = vec3_create(0, 0, 1),
        .fov = PI / 4
    };

    t_sphere sphere = {
        .center = vec3_create(0, 0, 3),
        .radius = 1.0,
        .material = {.color = {255, 0, 0}, .ambient = 0.2, .diffuse = 0.8, .specular = 0.1, .shininess = 10}
    };

    t_ambient_light ambient = {
        .intensity = 0.3,
        .color = {255, 255, 255}
    };

    // Render and verify output
    // This would require setting up a test image buffer
}
```

### Debugging Techniques

#### 1. Debug Output
```c
#define DEBUG 1

#if DEBUG
#define DEBUG_PRINT(fmt, ...) printf("[DEBUG] " fmt "\n", ##__VA_ARGS__)
#else
#define DEBUG_PRINT(fmt, ...) do {} while(0)
#endif

// Usage
DEBUG_PRINT("Ray origin: (%.2f, %.2f, %.2f)", O.x, O.y, O.z);
DEBUG_PRINT("Intersection found at t=%.4f", t1);
```

#### 2. Visual Debugging
```c
// Add debug colors for different objects
t_color debug_color = {255, 255, 0};  // Yellow for debugging
if (debug_mode) {
    return debug_color;
}
```

#### 3. Performance Profiling
```c
#include <time.h>

clock_t start = clock();
// ... code to profile ...
clock_t end = clock();
double cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
printf("Function took %.4f seconds\n", cpu_time_used);
```

## 🔍 Code Analysis

### Static Analysis
```bash
# Install static analysis tools
sudo apt-get install cppcheck valgrind

# Run static analysis
cppcheck --enable=all src/

# Run memory analysis
valgrind --leak-check=full --show-leak-kinds=all ./rt
```

### Code Coverage
```bash
# Install coverage tools
sudo apt-get install gcov lcov

# Compile with coverage
make CFLAGS="-fprofile-arcs -ftest-coverage"

# Run tests and generate coverage report
./rt
gcov src/utils/ray_utils.c
lcov --capture --directory . --output-file coverage.info
genhtml coverage.info --output-directory coverage_report
```

## 📚 Best Practices

### Memory Management
```c
// Always check allocation
t_sphere *spheres = malloc(num_spheres * sizeof(t_sphere));
if (!spheres) {
    fprintf(stderr, "Memory allocation failed\n");
    exit(1);
}

// Free allocated memory
free(spheres);
spheres = NULL;  // Prevent use-after-free
```

### Error Handling
```c
// Return error codes instead of void
int setup_camera(t_camera *camera, int width, int height) {
    if (!camera || width <= 0 || height <= 0) {
        return -1;  // Invalid parameters
    }

    if (camera->fov <= 0 || camera->fov >= PI) {
        return -2;  // Invalid FOV
    }

    // Setup camera...
    return 0;  // Success
}
```

### Performance Optimization
```c
// Use const for read-only parameters
void IntersectRaySphere(const t_vec3 O, const t_vec3 D,
                       const t_sphere sphere, double *t1, double *t2);

// Avoid repeated calculations
double radius_squared = sphere.radius * sphere.radius;  // Cache this value

// Use early termination
if (discriminant < 0) {
    *t1 = *t2 = DBL_MAX;
    return;  // Early exit
}
```

### Code Documentation
```c
/**
 * @file ray_utils.c
 * @brief Ray-object intersection algorithms
 * @author Your Name
 * @date 2024
 *
 * This file contains implementations of ray intersection algorithms
 * for various geometric primitives including spheres, cylinders, and planes.
 */

/**
 * @brief Calculates ray-sphere intersection using quadratic equation
 *
 * This function implements the standard ray-sphere intersection algorithm
 * by solving the quadratic equation derived from the sphere equation
 * and ray parametric equation.
 *
 * @param[in] O Ray origin point
 * @param[in] D Ray direction vector (must be normalized)
 * @param[in] sphere Sphere to test against
 * @param[out] t1 First intersection distance (closer)
 * @param[out] t2 Second intersection distance (farther)
 *
 * @return void
 *
 * @note If no intersection exists, both t1 and t2 are set to DBL_MAX
 * @note The ray direction vector D must be normalized for correct results
 *
 * @see IntersectRayCylinder, IntersectRayPlane
 */
void IntersectRaySphere(const t_vec3 O, const t_vec3 D,
                       const t_sphere sphere, double *t1, double *t2);
```

## 🚀 Advanced Development

### Multi-threading
```c
#include <pthread.h>

// Thread-safe rendering
typedef struct s_render_thread_data {
    int start_y, end_y;
    t_camera camera;
    t_sphere *spheres;
    int num_spheres;
    // ... other scene data
} t_render_thread_data;

void *render_thread(void *arg) {
    t_render_thread_data *data = (t_render_thread_data *)arg;

    for (int y = data->start_y; y < data->end_y; y++) {
        for (int x = 0; x < width; x++) {
            // Render pixel (x, y)
        }
    }

    return NULL;
}
```

### GPU Acceleration
Consider using OpenCL or CUDA for parallel ray tracing:

```c
// OpenCL kernel for ray-sphere intersection
__kernel void ray_sphere_intersect(
    __global const float3 *ray_origins,
    __global const float3 *ray_directions,
    __global const float3 *sphere_centers,
    __global const float *sphere_radii,
    __global float *intersection_distances
) {
    int id = get_global_id(0);
    // Implement GPU ray-sphere intersection
}
```

### Scene File Format
Implement a scene description language:

```c
// Example scene file format
camera {
    position: 0, 0, -5
    direction: 0, 0, 1
    fov: 45
}

sphere {
    center: 0, 0, 3
    radius: 1.0
    material: red_material
}

material red_material {
    color: 255, 0, 0
    ambient: 0.2
    diffuse: 0.7
    specular: 0.3
    shininess: 50
}
```

This development guide provides comprehensive information for extending and maintaining the ray tracer codebase. Follow these guidelines to ensure code quality, maintainability, and performance.
