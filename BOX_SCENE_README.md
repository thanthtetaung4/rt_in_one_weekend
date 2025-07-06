# Box Scene

This document describes the box scene that contains 4 black planes forming a box with 3 spheres and 2 cylinders inside.

## Scene Description

The box scene creates a closed environment with:
- **4 Black Planes**: Forming the walls of a box (left, right, top, bottom)
- **3 Spheres**: Red, blue, and green spheres with different materials
- **2 Cylinders**: Yellow cylinders (one vertical, one horizontal)
- **2 Point Lights**: Illuminating the scene from different angles

## Scene Layout

### Box Dimensions
- **Width**: 6 units (-3 to +3 on X-axis)
- **Height**: 6 units (-3 to +3 on Y-axis)
- **Depth**: Open (no front/back walls)

### Objects Inside the Box

#### Spheres
1. **Red Sphere**: Center at (0, 0, 2), radius 0.8
2. **Blue Sphere**: Center at (-1.5, 0, 1), radius 0.6
3. **Green Sphere**: Center at (1.5, 0, 1), radius 0.6

#### Cylinders
1. **Vertical Cylinder**: Center at (0, -0.5, 0), radius 0.4, height 1.5
2. **Horizontal Cylinder**: Center at (0, 0.5, 0), radius 0.3, height 2.0

#### Planes (Box Walls)
1. **Left Wall**: At X = -3, facing right
2. **Right Wall**: At X = +3, facing left
3. **Top Wall**: At Y = +3, facing down
4. **Bottom Wall**: At Y = -3, facing up

### Lighting
- **Ambient Light**: 20% intensity, white color
- **Light 1**: Position (0, 2, -2), 100% intensity, white
- **Light 2**: Position (2, 0, 2), 80% intensity, warm color

### Camera
- **Position**: (0, 0, -4) - outside the box
- **Direction**: Looking into the box (0, 0, 1)
- **Field of View**: 60 degrees

## Materials

### Object Materials
- **Red Sphere**: Shiny material with moderate specular reflection
- **Blue Sphere**: Very shiny material with high specular reflection
- **Green Sphere**: Matte material with low specular reflection
- **Yellow Cylinders**: Medium shiny material
- **Black Walls**: Very dark gray with low reflectivity

## Usage

### Compilation
```bash
make clean && make
```

### Running the Scene
```bash
./rt_box
```

### Running Both Scenes
```bash
./run_scenes.sh
```

## Files Generated

- **box_scene.ppm**: The rendered box scene image
- **image.ppm**: The original scene (when running both)

## Visual Features

### Lighting Effects
- **Shadows**: Objects cast shadows on the black walls
- **Highlights**: Specular reflections on shiny surfaces
- **Ambient Illumination**: Prevents completely dark areas

### Material Differences
- **Red Sphere**: Medium shininess, visible highlights
- **Blue Sphere**: High shininess, sharp highlights
- **Green Sphere**: Low shininess, matte appearance
- **Yellow Cylinders**: Medium shininess, visible highlights
- **Black Walls**: Very dark, minimal reflection

### Scene Composition
- **Depth**: Objects are positioned at different depths for 3D effect
- **Contrast**: Colored objects against black walls
- **Lighting**: Strategic light placement for dramatic shadows

## Technical Details

### Memory Management
The scene uses centralized memory management through the `t_scene` structure:
- Scene is created with `create_scene()`
- Objects are allocated in `setup_box_scene()`
- Memory is freed in `free_scene()` with proper cleanup
- All scene data is managed in a single structure for easier maintenance

### Rendering Process
1. Camera ray generation for each pixel
2. Ray-object intersection testing
3. Lighting calculation with shadows
4. Material property application
5. Color output to PPM file

### Performance Considerations
- Shadow casting adds computational cost
- Multiple light sources increase rendering time
- Box walls provide good shadow reference surfaces
