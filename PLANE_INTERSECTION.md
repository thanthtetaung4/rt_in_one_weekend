# Plane Ray Intersection

This document provides detailed information about ray-plane intersection calculations in the ray tracer.

## 📐 Mathematical Foundation

### Plane Definition
A plane is defined by:
- **Point on plane**: P₀
- **Normal vector**: N (normalized)

The plane equation is:
```
N · (P - P₀) = 0
```

Where P is any point on the plane.

### Ray Definition
A ray is defined by its origin O and direction D (normalized):
```
P(t) = O + tD
```

Where t ≥ 0 is the ray parameter.

### Intersection Derivation
To find the intersection between a ray and plane, we substitute the ray equation into the plane equation:

```
N · (P(t) - P₀) = 0
N · (O + tD - P₀) = 0
N · (O - P₀) + t(N · D) = 0
```

Solving for t:
```
t = N · (P₀ - O) / (N · D)
```

### Intersection Conditions
- **N · D ≠ 0**: Ray intersects plane at a single point
- **N · D = 0**: Ray is parallel to plane (no intersection)
- **t < 0**: Intersection is behind ray origin

## 🔧 Implementation

### Function Signature
```c
void IntersectRayPlane(t_vec3 O, t_vec3 D, t_plane plane, double *t);
```

### Parameters
- `O`: Ray origin point
- `D`: Ray direction vector (must be normalized)
- `plane`: Plane object with point and normal
- `t`: Intersection distance (output)

### Implementation Code
```c
void IntersectRayPlane(t_vec3 O, t_vec3 D, t_plane plane, double *t) {
    double denom = vec3_dot(D, plane.normal);

    if (ft_fabs(denom) < 1e-6) {
        // Ray is parallel to plane
        *t = DBL_MAX;
        return;
    }

    t_vec3 to_plane = vec3_sub(plane.point, O);
    *t = vec3_dot(to_plane, plane.normal) / denom;

    if (*t < 0) {
        // Intersection is behind ray origin
        *t = DBL_MAX;
    }
}
```

### Return Values
- `t`: Distance to intersection point
- `DBL_MAX` if no intersection (parallel ray or behind origin)

## 🎯 Normal Calculation

### Surface Normal
The surface normal is simply the plane's normal vector:
```
N = plane.normal
```

### Implementation
```c
t_vec3 get_plane_normal(t_plane plane) {
    return plane.normal;  // Already normalized
}
```

## 📊 Usage Examples

### Basic Intersection Test
```c
t_plane plane = {
    .point = vec3_create(0, 0, 8),
    .normal = vec3_normalize(vec3_create(0, 0, -1))  // facing camera
};

t_vec3 ray_origin = vec3_create(0, 0, 0);
t_vec3 ray_direction = vec3_normalize(vec3_create(0, 0, 1));

double t;
IntersectRayPlane(ray_origin, ray_direction, plane, &t);

if (t != DBL_MAX) {
    printf("Ray intersects plane at distance: %f\n", t);

    // Calculate intersection point
    t_vec3 hit_point = vec3_add(ray_origin, vec3_scale(ray_direction, t));

    // Get normal (same for all points on plane)
    t_vec3 normal = get_plane_normal(plane);
}
```

### Integration with Scene Structure
```c
// Using the scene structure
t_scene *scene = create_scene();
setup_box_scene(scene);

// Test intersection with all planes in scene
for (int i = 0; i < scene->num_planes; i++) {
    double t;
    IntersectRayPlane(ray_origin, ray_direction, scene->planes[i], &t);

    if (t != DBL_MAX && t >= t_min && t <= t_max) {
        // Found closest plane intersection
        t_vec3 hit_point = vec3_add(ray_origin, vec3_scale(ray_direction, t));
        t_vec3 normal = get_plane_normal(scene->planes[i]);

        // Apply lighting calculations
        t_color color = calculate_lighting(hit_point, normal, view_direction,
                                         scene->planes[i].material, scene);
    }
}
```

### Creating Different Plane Orientations
```c
// Horizontal plane (floor/ceiling)
t_plane floor = {
    .point = vec3_create(0, -2, 0),
    .normal = vec3_normalize(vec3_create(0, 1, 0))  // pointing up
};

// Vertical plane (wall)
t_plane wall = {
    .point = vec3_create(5, 0, 0),
    .normal = vec3_normalize(vec3_create(-1, 0, 0))  // pointing left
};

// Angled plane
t_plane roof = {
    .point = vec3_create(0, 3, 0),
    .normal = vec3_normalize(vec3_create(0, -0.707, 0.707))  // 45-degree angle
};
```

## ⚡ Performance Considerations

### Optimization Tips
1. **Early parallel check**: Quick rejection for parallel rays
2. **Normalized vectors**: Ensure plane normal is normalized
3. **Epsilon comparison**: Use small epsilon for floating-point comparisons
4. **Infinite planes**: No bounds checking needed

### Computational Complexity
- **Time**: O(1) per plane
- **Space**: O(1) additional memory
- **Operations**: ~5 floating-point operations per intersection test

## 🧪 Testing and Validation

### Test Cases
```c
void test_plane_intersection() {
    // Test 1: Ray intersecting plane
    t_plane plane = {
        .point = {0, 0, 5},
        .normal = {0, 0, -1}
    };
    t_vec3 O = {0, 0, 0};
    t_vec3 D = {0, 0, 1};

    double t;
    IntersectRayPlane(O, D, plane, &t);

    assert(fabs(t - 5.0) < 1e-6);

    // Test 2: Ray parallel to plane
    t_vec3 D_parallel = {1, 0, 0};
    IntersectRayPlane(O, D_parallel, plane, &t);

    assert(t == DBL_MAX);

    // Test 3: Ray behind origin
    t_vec3 D_behind = {0, 0, -1};
    IntersectRayPlane(O, D_behind, plane, &t);

    assert(t == DBL_MAX);

    printf("Plane intersection tests passed!\n");
}
```

### Edge Cases
1. **Ray parallel to plane**: No intersection
2. **Ray origin on plane**: t = 0
3. **Ray pointing away from plane**: t < 0 (rejected)
4. **Ray exactly perpendicular**: t = distance to plane
5. **Numerical precision**: Use epsilon for floating-point comparisons

## 🔗 Related Functions

### Ray Tracing Integration
- `TraceRayWithPlanes()`: Basic plane ray tracing
- `TraceRayWithLighting()`: Full lighting with planes
- `get_plane_hit()`: Get complete hit information

### Vector Operations
- `vec3_sub()`: Vector subtraction
- `vec3_dot()`: Dot product
- `vec3_scale()`: Vector scaling
- `vec3_normalize()`: Vector normalization

## 📚 References

- **Computer Graphics: Principles and Practice** - Foley, van Dam, Feiner, Hughes
- **Real-Time Rendering** - Akenine-Möller, Haines, Hoffman
- **Mathematics for 3D Game Programming and Computer Graphics** - Lengyel

---

**Note**: This implementation provides accurate plane-ray intersection calculations for infinite planes. The algorithm is numerically stable and handles all edge cases including parallel rays and rays behind the origin.
