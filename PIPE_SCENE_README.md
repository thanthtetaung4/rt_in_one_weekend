# Pipe Scene

This document describes the pipe scene where the camera is positioned inside an infinite cylinder (pipe) with small floating objects, creating the illusion of looking through a long pipe.

## Scene Description

The pipe scene creates an immersive experience where:
- **Camera**: Positioned at the center of a large cylinder, looking forward
- **Infinite Pipe**: Large cylinder extending along the Z-axis with gray material
- **Floating Objects**: Small colored spheres and cylinders floating inside the pipe
- **Multiple Lights**: Strategic lighting to illuminate the pipe interior

## Scene Layout

### Pipe Configuration
- **Center**: (0, 0, 0) - Camera is positioned here
- **Axis**: Extends along Z-axis (0, 0, 1)
- **Radius**: 5.0 units (large enough to contain objects)
- **Height**: 100.0 units (very tall to simulate infinite pipe)
- **Material**: Gray with moderate reflectivity

### Camera Setup
- **Position**: (-2.5, 0, 0) - Off-center to the left side of the pipe
- **Direction**: (0, 0, 1) - Looking forward along the pipe
- **Field of View**: 60 degrees (PI/3 radians) - Wider view to see more of the pipe

### Objects Inside the Pipe

#### Spheres (5 total)
1. **Red Sphere**: Center at (1.5, 1.0, 3), radius 0.4
2. **Blue Sphere**: Center at (-1.2, 0.8, 5), radius 0.3
3. **Green Sphere**: Center at (0.8, -1.5, 7), radius 0.5
4. **Yellow Sphere**: Center at (-0.5, -0.8, 9), radius 0.2
5. **Purple Sphere**: Center at (2.0, -0.3, 11), radius 0.35

#### Small Cylinders (2 total)
1. **Yellow Cylinder**: Center at (0.5, 1.8, 4), horizontal, radius 0.2, height 0.8
2. **Purple Cylinder**: Center at (-1.8, -0.5, 6), vertical, radius 0.15, height 0.6

### Lighting Setup
- **Ambient Light**: 40% intensity, white color (higher for pipe interior)
- **Light 1**: Position (-2.5, 0, -2), 100% intensity, white (behind camera)
- **Light 2**: Position (2, 2, 8), 80% intensity, white (ahead and to the right side)
- **Light 3**: Position (-2, -2, 12), 60% intensity, warm color (further ahead)
- **Light 4**: Position (2.5, 0, 5), 70% intensity, white (on the opposite wall)

## Materials

### Pipe Material
- **Color**: Light Gray (150, 150, 150) - Better visibility
- **Ambient**: 0.4 (higher ambient reflection for better wall visibility)
- **Diffuse**: 0.6 (higher diffuse reflection)
- **Specular**: 0.3 (moderate specular reflection)
- **Shininess**: 30 (moderate shininess)

### Object Materials
- **Red Sphere**: Shiny material with moderate specular reflection
- **Blue Sphere**: Very shiny material with high specular reflection
- **Green Sphere**: Matte material with low specular reflection
- **Yellow Sphere**: Medium shiny material
- **Purple Sphere**: Medium shiny material
- **Yellow Cylinder**: Medium shiny material
- **Purple Cylinder**: Medium shiny material

## Usage

### Compilation
```bash
make clean && make
# By default, only the main ray tracer (./rt) is built.
# To build the pipe scene executable, uncomment the relevant line in the Makefile and run:
make rt_pipe
```

### Running the Scene
```bash
./rt_pipe
```

### Running All Scenes
```bash
./run_scenes.sh
```

## Files Generated

- **rt_pipe**: The pipe scene executable
- **Real-time display**: Interactive window showing the pipe scene

## Visual Features

### Pipe Interior Effect
- **Visible Walls**: Camera positioned off-center to clearly see the cylinder walls
- **Curved Perspective**: The cylinder walls create a curved tunnel perspective
- **Depth Perception**: Objects at different distances create depth
- **Wide View**: 60-degree field of view shows more of the pipe interior

### Lighting Effects
- **Multiple Light Sources**: Creates varied illumination patterns
- **Shadows**: Objects cast shadows on the pipe walls
- **Highlights**: Specular reflections on shiny surfaces
- **Ambient Illumination**: Prevents completely dark areas

### Object Placement
- **Strategic Positioning**: Objects placed to avoid pipe walls
- **Varied Sizes**: Different object sizes for visual interest
- **Color Variety**: Multiple colors for visual appeal
- **Depth Distribution**: Objects at various distances

## Technical Details

### Memory Management
The scene uses centralized memory management through the `t_scene` structure:
- Scene is created with `create_scene()`
- Objects are allocated in `setup_pipe_scene()`
- Memory is freed in `free_scene()` with proper cleanup
- All scene data is managed in a single structure for easier maintenance

### Rendering Process
1. Camera ray generation for each pixel
2. Ray-object intersection testing (spheres, cylinders)
3. Lighting calculation with shadows
4. Material property application
5. Color output to MLX window

### Performance Considerations
- Large cylinder requires efficient intersection testing
- Multiple light sources increase rendering time
- Shadow casting adds computational cost
- Pipe walls provide good shadow reference surfaces

## Scene Characteristics

### Immersive Experience
- **First-person perspective**: Camera positioned to see the pipe walls clearly
- **Tunnel effect**: Off-center position creates realistic tunnel perspective
- **Visible boundaries**: Clear view of the cylinder walls enhances immersion
- **Floating objects**: Objects appear to float in space within the pipe

### Visual Composition
- **Curved perspective**: Cylinder walls create unique curved perspective
- **Depth cues**: Objects at different distances provide depth information
- **Lighting drama**: Multiple lights cre te interesting shadow patterns
- **Color contrast**: Colored objects against gray pipe walls

### Technical Implementation
- **Infinite cylinder**: Large height simulates infinite pipe
- **Proper lighting**: Multiple lights ensure good illumination
- **Material variety**: Different materials for visual interest
- **Efficient rendering**: Optimized for real-time display
