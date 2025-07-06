# User Guide

This guide explains how to use the ray tracer, create custom scenes, and customize the rendering parameters.

## 🚀 Getting Started

### Prerequisites
- Linux system with X11 support
- GCC compiler
- Git (for cloning dependencies)

### Installation
```bash
# Clone the repository
git clone <repository-url>
cd rt_in_one_weekend

# Build the project
make

# Verify installation
ls -la rt rt_box
```

### Running the Demos
```bash
# Run the main scene (spheres with lighting)
./rt

# Run the box scene (complex scene with multiple objects)
./rt_box

# Run both scenes sequentially
./run_scenes.sh
```

## 🎮 Controls

### Application Controls
- **ESC key**: Exit the application
- **Window close button**: Close the window and exit
- **Real-time display**: View rendering progress in real-time

### What You'll See
- **Main Scene**: 4 colored spheres with 2 point lights and ambient lighting
- **Box Scene**: Complex scene with spheres, cylinders, planes, and multiple lights
- **Interactive window**: Real-time rendering display using MLX

## 🎨 Creating Custom Scenes

### Scene Structure
A scene consists of:
- **Camera**: View position and orientation
- **Objects**: Spheres, cylinders, and planes
- **Lights**: Ambient and point lights
- **Materials**: Surface properties for objects
- **Background**: Scene background color
- **Dimensions**: Image width and height

The ray tracer uses a centralized scene management system where all scene data is stored in a single `t_scene` structure for easier management and cleaner function calls.

### Basic Scene Setup

#### 1. Camera Configuration
```c
t_camera camera = {
    .P = vec3_create(0, 0, -5),    // Camera position
    .D = vec3_create(0, 0, 1),     // View direction (normalized)
    .fov = PI / 4                  // Field of view (45 degrees)
};
```

#### 2. Material Definition
```c
// Create a shiny red material
t_material red_material = {
    .color = {255, 0, 0},          // Red color
    .ambient = 0.2,                // Low ambient reflection
    .diffuse = 0.7,                // High diffuse reflection
    .specular = 0.3,               // Moderate specular reflection
    .shininess = 50                // Medium shininess
};

// Create a matte blue material
t_material blue_material = {
    .color = {0, 0, 255},          // Blue color
    .ambient = 0.2,                // Low ambient reflection
    .diffuse = 0.8,                // High diffuse for matte look
    .specular = 0.1,               // Low specular for matte look
    .shininess = 10                // Low shininess
};
```

#### 3. Object Creation

**Spheres:**
```c
t_sphere sphere = {
    .center = vec3_create(0, 0, 3),    // Center position
    .radius = 1.0,                     // Radius
    .material = red_material           // Material properties
};
```

**Cylinders:**
```c
t_cylinder cylinder = {
    .center = vec3_create(2, 0, 2),    // Center position
    .axis = vec3_normalize(vec3_create(0, 1, 0)), // Vertical axis
    .radius = 0.5,                     // Radius
    .height = 2.0,                     // Height
    .material = blue_material          // Material properties
};
```

**Planes:**
```c
t_plane plane = {
    .point = vec3_create(0, -2, 0),    // Point on plane
    .normal = vec3_normalize(vec3_create(0, 1, 0)), // Upward normal
    .material = green_material         // Material properties
};
```

#### 4. Lighting Setup

**Ambient Light:**
```c
t_ambient_light ambient = {
    .intensity = 0.3,                  // Ambient intensity (0.0-1.0)
    .color = {255, 255, 255}          // White ambient light
};
```

**Point Lights:**
```c
t_point_light lights[] = {
    {
        .position = vec3_create(2, 3, -2),  // Light position
        .intensity = 1.0,                   // Light intensity
        .color = {255, 255, 255}           // White light
    },
    {
        .position = vec3_create(-2, 2, 2),  // Second light position
        .intensity = 0.8,                   // Lower intensity
        .color = {255, 200, 200}           // Warm light color
    }
};
```

### Complete Scene Example

```c
#include "../inc/rt.h"
#include "../mlx/mlx.h"

int main() {
    // Initialize MLX
    void *mlx_ptr = mlx_init();
    void *win_ptr = mlx_new_window(mlx_ptr, 800, 600, "Custom Scene");

    // Create and setup scene
    t_scene *scene = create_scene();
    if (!scene) {
        printf("Error: Failed to create scene\n");
        return 1;
    }

    // Setup camera
    scene->camera = (t_camera){
        .P = vec3_create(0, 0, -5),
        .D = vec3_create(0, 0, 1),
        .fov = PI / 4
    };

    // Define materials
    t_material red_material = {
        .color = {255, 0, 0},
        .ambient = 0.2,
        .diffuse = 0.7,
        .specular = 0.3,
        .shininess = 50
    };

    t_material blue_material = {
        .color = {0, 0, 255},
        .ambient = 0.2,
        .diffuse = 0.8,
        .specular = 0.1,
        .shininess = 10
    };

    // Setup spheres
    scene->num_spheres = 2;
    scene->spheres = malloc(scene->num_spheres * sizeof(t_sphere));
    scene->spheres[0] = (t_sphere){
        .center = vec3_create(0, 0, 3),
        .radius = 1.0,
        .material = red_material
    };
    scene->spheres[1] = (t_sphere){
        .center = vec3_create(2, 0, 2),
        .radius = 0.8,
        .material = blue_material
    };

    // Setup lighting
    scene->ambient = (t_ambient_light){
        .intensity = 0.3,
        .color = {255, 255, 255}
    };

    t_point_light lights[] = {
        {
            .position = vec3_create(2, 3, -2),
            .intensity = 1.0,
            .color = {255, 255, 255}
        }
    };

    // Render scene
    render_scene_with_lighting(win_ptr, camera, spheres, 2,
                              NULL, 0, NULL, 0,
                              ambient, lights, 1,
                              800, 600);

    // Event loop
    mlx_loop(mlx_ptr);
    return 0;
}
```

## 🎨 Material Presets

### Matte Materials
```c
// Soft matte surface
t_material matte = {
    .ambient = 0.2,
    .diffuse = 0.8,
    .specular = 0.1,
    .shininess = 10
};

// Rough surface
t_material rough = {
    .ambient = 0.3,
    .diffuse = 0.9,
    .specular = 0.05,
    .shininess = 5
};
```

### Shiny Materials
```c
// Glossy surface
t_material glossy = {
    .ambient = 0.1,
    .diffuse = 0.6,
    .specular = 0.8,
    .shininess = 100
};

// Metallic surface
t_material metallic = {
    .ambient = 0.1,
    .diffuse = 0.4,
    .specular = 0.9,
    .shininess = 200
};
```

### Plastic Materials
```c
// Plastic surface
t_material plastic = {
    .ambient = 0.2,
    .diffuse = 0.7,
    .specular = 0.5,
    .shininess = 80
};
```

## 💡 Lighting Tips

### Ambient Lighting
- **Low ambient (0.1-0.3)**: Creates dramatic shadows
- **High ambient (0.4-0.6)**: Provides even illumination
- **Color ambient**: Creates mood lighting

### Point Light Positioning
- **Above objects**: Creates natural top-down lighting
- **Side lighting**: Highlights surface details
- **Multiple lights**: Reduces harsh shadows
- **Colored lights**: Creates artistic effects

### Light Intensity
- **Primary light**: 1.0 intensity
- **Fill light**: 0.3-0.7 intensity
- **Rim light**: 0.5-0.8 intensity

## 🎯 Scene Composition Tips

### Object Placement
- **Vary depths**: Place objects at different Z positions
- **Rule of thirds**: Use compositional guidelines
- **Size variation**: Mix different object sizes
- **Color harmony**: Use complementary or analogous colors

### Camera Positioning
- **Eye level**: Position camera at typical viewing height
- **Slight angle**: Add visual interest with camera tilt
- **Distance**: Balance between detail and scene overview
- **FOV adjustment**: Wide FOV for expansive scenes, narrow for detail

### Lighting Setup
- **Three-point lighting**: Key, fill, and rim lights
- **Shadow play**: Use shadows for depth and drama
- **Color temperature**: Mix warm and cool lights
- **Intensity balance**: Avoid overexposed or underexposed areas

## 🔧 Customization Options

### Image Resolution
```c
// Change window size in main.c
int img_width = 1024, img_height = 768;  // Higher resolution
int img_width = 400, img_height = 300;   // Lower resolution for speed
```

### Rendering Quality
- **Higher resolution**: More detail, slower rendering
- **Lower resolution**: Faster rendering, less detail
- **Real-time vs. file output**: Choose based on needs

### Performance Tuning
```c
// Reduce scene complexity for better performance
int num_spheres = 2;      // Fewer objects
int num_lights = 1;       // Fewer lights
double shadow_epsilon = 0.01;  // Adjust shadow precision
```

## 🐛 Troubleshooting

### Common Issues

#### Compilation Errors
```bash
# Missing X11 libraries
sudo apt-get install libx11-dev libxext-dev

# MLX not found
make clean && make  # Rebuild after installing dependencies
```

#### Display Issues
```bash
# X11 server not running
echo $DISPLAY  # Should show :0 or similar
startx         # Start X server if needed
```

#### Performance Problems
- Reduce image resolution
- Decrease number of objects
- Use fewer light sources
- Simplify materials

#### Visual Artifacts
- **Self-shadowing**: Adjust shadow epsilon value
- **Color overflow**: Check color clamping
- **Missing objects**: Verify object positions and sizes
- **Incorrect shadows**: Check light positions and intensities

### Debug Output
Add debug prints to understand scene behavior:
```c
// Debug object positions
printf("Sphere center: (%.2f, %.2f, %.2f)\n",
       sphere.center.x, sphere.center.y, sphere.center.z);

// Debug lighting
printf("Light position: (%.2f, %.2f, %.2f)\n",
       light.position.x, light.position.y, light.position.z);

// Debug camera
printf("Camera position: (%.2f, %.2f, %.2f)\n",
       camera.P.x, camera.P.y, camera.P.z);
```

## 📚 Advanced Usage

### Creating Complex Scenes
1. **Plan the composition**: Sketch or visualize the scene
2. **Start simple**: Begin with basic objects and lighting
3. **Add complexity**: Gradually add more objects and lights
4. **Test and refine**: Iterate on materials and positioning
5. **Optimize**: Balance quality and performance

### Material Experimentation
- **Mix materials**: Combine different surface types
- **Color theory**: Use color wheels for harmonious palettes
- **Lighting effects**: Experiment with different light setups
- **Shadow studies**: Use shadows for dramatic effect

### Scene Animation
While the current version doesn't support animation, you can:
- **Multiple renders**: Create sequences of static images
- **Parameter variation**: Change camera, objects, or lighting
- **Storyboarding**: Plan scene progression
- **Post-processing**: Combine renders for effects

## 🎓 Learning Resources

### Computer Graphics Concepts
- **Ray tracing fundamentals**: Understanding ray-object intersections
- **Lighting models**: Phong, Blinn-Phong, and other models
- **Material properties**: How surfaces interact with light
- **Camera models**: Perspective projection and view setup

### Programming Skills
- **C programming**: Memory management and optimization
- **Mathematics**: Vector operations and geometric calculations
- **Graphics programming**: MLX library usage
- **Algorithm design**: Efficient rendering techniques

### Further Reading
- "Ray Tracing in One Weekend" by Peter Shirley
- "Real-Time Rendering" by Akenine-Möller et al.
- "Computer Graphics: Principles and Practice" by Foley et al.
- Online tutorials and documentation for MLX

This user guide provides comprehensive information for using and customizing the ray tracer. Experiment with different parameters and scene setups to explore the full capabilities of the system.
