# Lighting System

This document explains the lighting system implemented in the ray tracer, including ambient light, point lights, materials, and shadow casting.

## Lighting Components

### Ambient Light
```c
typedef struct s_ambient_light {
    double intensity;  // Ambient light intensity (0.0 to 1.0)
    t_color color;     // Ambient light color
} t_ambient_light;
```

Ambient light provides base illumination to all surfaces, simulating indirect lighting from the environment.

### Point Light
```c
typedef struct s_point_light {
    t_vec3 position;   // Light position in 3D space
    double intensity;  // Light intensity
    t_color color;     // Light color
} t_point_light;
```

Point lights emit light from a specific position in 3D space, creating directional lighting and shadows.

## Material System

### Material Properties
```c
typedef struct s_material {
    t_color color;     // Base color
    double ambient;    // Ambient reflection coefficient (0.0 to 1.0)
    double diffuse;    // Diffuse reflection coefficient (0.0 to 1.0)
    double specular;   // Specular reflection coefficient (0.0 to 1.0)
    double shininess;  // Shininess exponent for specular highlights
} t_material;
```

Materials define how surfaces interact with light:
- **color**: The base color of the material
- **ambient**: How much ambient light the surface reflects
- **diffuse**: How much diffuse light the surface reflects (matte appearance)
- **specular**: How much specular light the surface reflects (shiny appearance)
- **shininess**: Controls the size of specular highlights (higher = smaller, sharper highlights)

## Lighting Model

The lighting calculation uses the **Phong lighting model** with three components:

### 1. Ambient Lighting
```
ambient_color = material_color × ambient_light_color × material.ambient × ambient.intensity
```

### 2. Diffuse Lighting
```
diffuse_factor = dot(normal, light_direction)
diffuse_color = material_color × light_color × material.diffuse × diffuse_factor × light.intensity
```

### 3. Specular Lighting (Blinn-Phong)
```
half_vector = normalize(view_direction + light_direction)
specular_factor = dot(normal, half_vector) ^ material.shininess
specular_color = material_color × light_color × material.specular × specular_factor × light.intensity
```

## Shadow Casting

The ray tracer implements **hard shadows** by casting shadow rays from hit points to light sources:

1. For each point light, cast a ray from the hit point toward the light
2. Check if any object intersects this shadow ray before reaching the light
3. If an intersection is found, the point is in shadow for that light
4. Only ambient lighting contributes to shadowed areas

## Example Usage

### Setting up Materials
```c
// Create a shiny red material
t_material red_material = {
    .color = {255, 0, 0},
    .ambient = 0.2,    // Low ambient reflection
    .diffuse = 0.7,    // High diffuse reflection
    .specular = 0.3,   // Moderate specular reflection
    .shininess = 50    // Medium shininess
};

// Create a matte blue material
t_material blue_material = {
    .color = {0, 0, 255},
    .ambient = 0.2,
    .diffuse = 0.8,    // High diffuse for matte look
    .specular = 0.1,   // Low specular for matte look
    .shininess = 10    // Low shininess
};
```

### Setting up Lighting
```c
// Ambient light
t_ambient_light ambient = {
    .intensity = 0.3,
    .color = {255, 255, 255} // white ambient
};

// Point lights
t_point_light lights[] = {
    {
        .position = {2, 3, -2},
        .intensity = 1.0,
        .color = {255, 255, 255} // white light
    },
    {
        .position = {-2, 2, 2},
        .intensity = 0.8,
        .color = {255, 200, 200} // warm light
    }
};
```

### Rendering with Lighting
```c
// Create and setup scene
t_scene *scene = create_scene();
setup_regular_scene(scene);  // or setup_box_scene(scene)

// Render with lighting
render_scene_with_lighting(f, scene);

// Clean up
free_scene(scene);
```

## Material Presets

### Matte Material
```c
t_material matte = {
    .ambient = 0.2,
    .diffuse = 0.8,
    .specular = 0.1,
    .shininess = 10
};
```

### Shiny Material
```c
t_material shiny = {
    .ambient = 0.1,
    .diffuse = 0.6,
    .specular = 0.8,
    .shininess = 100
};
```

### Metallic Material
```c
t_material metallic = {
    .ambient = 0.1,
    .diffuse = 0.4,
    .specular = 0.9,
    .shininess = 200
};
```

## Performance Notes

- Shadow casting adds significant computational cost
- Each light source requires additional ray intersection tests
- Consider reducing the number of lights for better performance
- Ambient light provides base illumination without shadow calculations

## Tips for Good Lighting

1. **Use ambient light** to prevent completely dark areas
2. **Position lights strategically** to highlight important features
3. **Experiment with material properties** to achieve desired surface appearances
4. **Use multiple lights** for more complex lighting scenarios
5. **Balance light intensities** to avoid overexposed or underexposed areas
