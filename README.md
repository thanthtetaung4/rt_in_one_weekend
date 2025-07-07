# Ray Tracer in One Weekend

A complete ray tracing and rendering engine implemented in C using the MiniLibX (MLX) graphics library. This project demonstrates fundamental computer graphics concepts including ray-object intersections, lighting models, materials, and real-time rendering.

## 🎯 Project Overview

This ray tracer implements a complete 3D rendering pipeline capable of rendering:
- **Spheres** with realistic lighting and materials
- **Cylinders** with proper intersection calculations
- **Planes** for creating walls and surfaces
- **Multiple light sources** with shadow casting
- **Material system** with ambient, diffuse, and specular reflection
- **Real-time rendering** using MLX graphics library

## 🏗️ Architecture

### Core Components

```
rt_in_one_weekend/
├── inc/                    # Header files
│   ├── rt.h               # Main ray tracer structures and declarations
│   ├── vec3.h             # 3D vector operations
│   ├── ray.h              # Ray structure
│   ├── color.h            # Color utilities
│   └── ft_math.h          # Math utilities
├── src/                   # Source code
│   ├── main.c             # Main application with MLX integration
│   ├── main_box.c         # Box scene demo
│   ├── utils/             # Utility functions
│   │   ├── camera_utils.c # Camera setup and view calculations
│   │   ├── color_utils.c  # Color manipulation
│   │   ├── lighting_utils.c # Lighting calculations and shadows
│   │   ├── math_utils.c   # Mathematical operations
│   │   ├── ray_utils.c    # Ray-object intersections
│   │   ├── render_utils.c # Rendering pipeline
│   │   └── scene_utils.c  # Scene management and setup
│   └── vec3/              # Vector operations implementation
│       └── vec3.c
├── libft/                 # Custom C library functions
├── mlx/                   # MiniLibX graphics library
└── Makefile               # Build configuration
```

## 🚀 Quick Start

### Prerequisites

- **Linux** with X11 development libraries
- **GCC** compiler
- **Git** for cloning dependencies

### Installation

1. **Clone the repository:**
   ```bash
   git clone <repository-url>
   cd rt_in_one_weekend
   ```

2. **Build the project:**
   ```bash
   make
   ```

3. **Run the demos:**
   ```bash
   # Run the main scene
   ./rt

   # Run the box scene
   ./rt_box

   # Run both scenes
   ./run_scenes.sh
   ```

## 🎨 Features

### Geometric Primitives

#### Spheres
- **Intersection**: Quadratic equation solving for ray-sphere intersection
- **Normal calculation**: Surface normal at intersection points
- **Materials**: Full material system support

#### Cylinders
- **Infinite cylinder**: Ray-cylinder intersection with quadratic equations
- **Height constraints**: Finite cylinder with end caps
- **End cap intersection**: Proper handling of cylinder caps
- **Normal calculation**: Correct surface normals for body and caps

#### Planes
- **Ray-plane intersection**: Simple linear equation solving
- **Infinite planes**: No size constraints
- **Normal vectors**: Consistent surface orientation

### Lighting System

#### Ambient Lighting
- **Global illumination**: Base lighting for all surfaces
- **Configurable intensity**: 0.0 to 1.0 range
- **Color support**: RGB ambient light colors

#### Point Lights
- **Position-based**: Lights at specific 3D coordinates
- **Intensity control**: Adjustable light strength
- **Color support**: RGB light colors
- **Multiple lights**: Support for multiple light sources

#### Shadow Casting
- **Hard shadows**: Binary shadow/light determination
- **Shadow rays**: Ray casting from hit points to lights
- **Object occlusion**: All primitive types cast shadows

### Material System

#### Material Properties
```c
typedef struct s_material {
    t_color color;     // Base color (RGB)
    double ambient;    // Ambient reflection coefficient
    double diffuse;    // Diffuse reflection coefficient
    double specular;   // Specular reflection coefficient
    double shininess;  // Shininess exponent
} t_material;
```

#### Lighting Model
- **Phong lighting model**: Industry-standard lighting calculation
- **Ambient component**: Base surface illumination
- **Diffuse component**: Lambertian reflection
- **Specular component**: Blinn-Phong specular highlights
- **Color clamping**: Prevents color overflow

### Scene Management

#### Scene Data Structure
The ray tracer uses a comprehensive scene structure that encapsulates all rendering data:

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

#### Scene Management Functions
```c
// Create and manage scenes
t_scene *create_scene(void);
void free_scene(t_scene *scene);
void setup_regular_scene(t_scene *scene);
void setup_box_scene(t_scene *scene);
void setup_pipe_scene(t_scene *scene);
```

### Camera System

#### Camera Properties
```c
typedef struct s_camera {
    t_vec3 P;     // Position in 3D space
    t_vec3 D;     // View direction (normalized)
    double fov;   // Field of view in radians
} t_camera;
```

#### View Setup
- **Pixel grid calculation**: Camera view plane setup
- **Ray generation**: Primary rays for each pixel
- **Perspective projection**: Realistic camera perspective

## 🔧 Technical Implementation

### Ray Tracing Pipeline

1. **Camera Setup**
   ```c
   t_camera_view view = setup_camera(camera, width, height);
   ```

2. **Ray Generation**
   ```c
   t_vec3 ray_dir = vec3_normalize(vec3_sub(pixel, camera.P));
   ```

3. **Intersection Testing**
   ```c
   t_color color = TraceRayWithLighting(origin, direction, t_min, t_max, scene);
   ```

4. **Lighting Calculation**
   ```c
   t_color final_color = calculate_lighting(hit_point, normal, view_direction,
                                           material, scene);
   ```

### Vector Operations

The project includes a complete 3D vector library:

```c
// Vector creation and basic operations
t_vec3 vec3_create(double x, double y, double z);
t_vec3 vec3_add(t_vec3 a, t_vec3 b);
t_vec3 vec3_sub(t_vec3 a, t_vec3 b);
t_vec3 vec3_scale(t_vec3 v, double s);
t_vec3 vec3_normalize(t_vec3 v);

// Vector products
double vec3_dot(t_vec3 a, t_vec3 b);
t_vec3 vec3_cross(t_vec3 a, t_vec3 b);
```

### Color System

RGB color representation with utility functions:

```c
// Color operations
t_color color_multiply(t_color a, t_color b);
t_color color_scale(t_color color, double factor);
t_color color_add(t_color a, t_color b);
t_color color_clamp(t_color color);
```

## 🎮 Interactive Features

### MLX Integration

- **Real-time rendering**: Live display using MLX graphics library
- **Window management**: Proper window creation and event handling
- **Event system**: Keyboard and window close event handling
- **Pixel manipulation**: Direct pixel drawing to window

### Controls

- **ESC key**: Exit the application
- **Window close button**: Proper cleanup and exit
- **Real-time display**: Immediate visual feedback

## 📊 Performance Considerations

### Optimization Strategies

1. **Early termination**: Stop intersection testing when closest object is found
2. **Shadow ray optimization**: Use small epsilon for shadow ray origins
3. **Material caching**: Pre-compute material properties where possible
4. **Efficient math**: Use optimized mathematical operations

### Memory Management

- **Centralized scene management**: All scene data managed through `t_scene` structure
- **Dynamic allocation**: Proper memory allocation for scene objects
- **Cleanup functions**: Memory deallocation to prevent leaks
- **Stack usage**: Local variables for temporary calculations

## 🧪 Testing and Validation

### Scene Validation

The project includes multiple test scenes:

1. **Main Scene**: Basic sphere and lighting demonstration
2. **Box Scene**: Complex scene with multiple primitives and lighting
3. **Pipe Scene**: Immersive scene with camera inside infinite cylinder
4. **Custom Scenes**: Easy scene creation and modification

### Visual Verification

- **Shadow accuracy**: Proper shadow casting and positioning
- **Material appearance**: Correct lighting model implementation
- **Geometric accuracy**: Proper intersection calculations
- **Color accuracy**: Correct color mixing and clamping

## 📚 Additional Documentation

- **[Lighting System](LIGHTING_README.md)**: Detailed lighting model documentation
- **[Box Scene](BOX_SCENE_README.md)**: Box scene setup and configuration
- **[Pipe Scene](PIPE_SCENE_README.md)**: Pipe scene with camera inside infinite cylinder
- **[Cylinder and Plane](CYLINDER_PLANE_README.md)**: Geometric primitive documentation

### Ray-Object Intersection Documentation

Each geometric primitive has its own detailed documentation:

- **[Sphere Intersection](SPHERE_INTERSECTION.md)**: Complete sphere ray intersection guide
- **[Cylinder Intersection](CYLINDER_INTERSECTION.md)**: Comprehensive cylinder intersection documentation
- **[Plane Intersection](PLANE_INTERSECTION.md)**: Plane intersection implementation details

## 🔍 Troubleshooting

### Common Issues

1. **MLX not found**: Ensure X11 development libraries are installed
2. **Compilation errors**: Check GCC version and library dependencies
3. **Display issues**: Verify X11 server is running
4. **Performance problems**: Reduce scene complexity or image resolution

### Debugging

- **Intersection testing**: Add debug output for ray-object intersections
- **Lighting calculations**: Verify material properties and light positions
- **Color values**: Check for color clamping and overflow

## 🤝 Contributing

### Code Style

- **C99 standard**: Use C99 features and syntax
- **Consistent naming**: Follow established naming conventions
- **Header guards**: Proper include guards in header files
- **Documentation**: Comment complex algorithms and functions

### Adding Features

1. **New primitives**: Implement intersection functions and normal calculations
2. **Advanced materials**: Add reflection, refraction, or texture support
3. **Optimization**: Improve rendering performance
4. **UI enhancements**: Add interactive controls and real-time editing

## 📄 License

This project is licensed under the terms specified in the LICENSE file.

## 🙏 Acknowledgments

- **Peter Shirley**: "Ray Tracing in One Weekend" book series
- **42 Paris**: MiniLibX graphics library
- **Computer Graphics Community**: Lighting models and algorithms

---

**Note**: This ray tracer is designed for educational purposes and demonstrates fundamental computer graphics concepts. For production use, consider more advanced features like acceleration structures, advanced materials, and optimization techniques.
