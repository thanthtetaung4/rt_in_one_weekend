# Sphere Ray Intersection

This document provides detailed information about ray-sphere intersection calculations in the ray tracer.

## 📐 Mathematical Foundation

### Sphere Definition
A sphere is defined by its center point C and radius r. The sphere equation is:
```
||P - C||² = r²
```

Where P is any point on the sphere surface.

### Ray Definition
A ray is defined by its origin O and direction D (normalized):
```
P(t) = O + tD
```

Where t ≥ 0 is the ray parameter.

### Intersection Derivation
To find the intersection between a ray and sphere, we substitute the ray equation into the sphere equation:

```
||P(t) - C||² = r²
||O + tD - C||² = r²
```

Let CO = O - C (vector from sphere center to ray origin), then:
```
||CO + tD||² = r²
```

Expanding the dot product:
```
(CO + tD) · (CO + tD) = r²
CO · CO + 2t(CO · D) + t²(D · D) = r²
```

This gives us a quadratic equation: `at² + bt + c = 0`, where:
- `a = D · D = 1` (since D is normalized)
- `b = 2(CO · D)`
- `c = CO · CO - r²`

### Quadratic Solution
The quadratic equation has solutions:
```
t = (-b ± √(b² - 4ac)) / (2a)
```

Since a = 1:
```
t = (-b ± √(b² - 4c)) / 2
```

The discriminant `Δ = b² - 4c` determines the number of intersections:
- `Δ < 0`: No intersection (ray misses sphere)
- `Δ = 0`: One intersection (ray tangent to sphere)
- `Δ > 0`: Two intersections (ray enters and exits sphere)

## 🔧 Implementation

### Function Signature
```c
void IntersectRaySphere(t_vec3 O, t_vec3 D, t_sphere sphere, double *t1, double *t2);
```

### Parameters
- `O`: Ray origin point
- `D`: Ray direction vector (must be normalized)
- `sphere`: Sphere object with center and radius
- `t1`: First intersection distance (output)
- `t2`: Second intersection distance (output)

### Implementation Code
```c
void IntersectRaySphere(t_vec3 O, t_vec3 D, t_sphere sphere, double *t1, double *t2) {
    t_vec3 CO = vec3_sub(O, sphere.center);
    double a = vec3_dot(D, D);           // Always 1 for normalized D
    double b = 2 * vec3_dot(CO, D);
    double c = vec3_dot(CO, CO) - sphere.radius * sphere.radius;
    double discriminant = b * b - 4 * a * c;

    if (discriminant < 0) {
        *t1 = DBL_MAX;
        *t2 = DBL_MAX;  // No intersection
        return;
    }

    *t1 = (-b + sqrt(discriminant)) / (2 * a);
    *t2 = (-b - sqrt(discriminant)) / (2 * a);
}
```

### Return Values
- `t1`: Distance to first intersection (farther point)
- `t2`: Distance to second intersection (closer point)
- Both set to `DBL_MAX` if no intersection

## 🎯 Normal Calculation

### Surface Normal
The surface normal at intersection point P is:
```
N = (P - C) / ||P - C|| = (P - C) / r
```

### Implementation
```c
t_vec3 get_sphere_normal(t_vec3 hit_point, t_sphere sphere) {
    return vec3_normalize(vec3_sub(hit_point, sphere.center));
}
```

## 📊 Usage Examples

### Basic Intersection Test
```c
t_sphere sphere = {
    .center = vec3_create(0, 0, 3),
    .radius = 1.0
};

t_vec3 ray_origin = vec3_create(0, 0, 0);
t_vec3 ray_direction = vec3_normalize(vec3_create(0, 0, 1));

double t1, t2;
IntersectRaySphere(ray_origin, ray_direction, sphere, &t1, &t2);

if (t1 != DBL_MAX) {
    printf("Ray intersects sphere at distances: %f and %f\n", t1, t2);

    // Calculate intersection points
    t_vec3 hit1 = vec3_add(ray_origin, vec3_scale(ray_direction, t1));
    t_vec3 hit2 = vec3_add(ray_origin, vec3_scale(ray_direction, t2));

    // Calculate normals
    t_vec3 normal1 = get_sphere_normal(hit1, sphere);
    t_vec3 normal2 = get_sphere_normal(hit2, sphere);
}
```

### Integration with Scene Structure
```c
// Using the scene structure
t_scene *scene = create_scene();
setup_regular_scene(scene);

// Test intersection with all spheres in scene
for (int i = 0; i < scene->num_spheres; i++) {
    double t1, t2;
    IntersectRaySphere(ray_origin, ray_direction, scene->spheres[i], &t1, &t2);

    if (t1 != DBL_MAX && t1 >= t_min && t1 <= t_max) {
        // Found closest sphere intersection
        t_vec3 hit_point = vec3_add(ray_origin, vec3_scale(ray_direction, t1));
        t_vec3 normal = get_sphere_normal(hit_point, scene->spheres[i]);

        // Apply lighting calculations
        t_color color = calculate_lighting(hit_point, normal, view_direction,
                                         scene->spheres[i].material, scene);
    }
}
```

## ⚡ Performance Considerations

### Optimization Tips
1. **Early termination**: Check if t1 < t_min or t2 > t_max
2. **Normalized vectors**: Ensure ray direction is normalized
3. **Discriminant check**: Quick rejection for missed rays
4. **Distance ordering**: t2 is always closer than t1

### Computational Complexity
- **Time**: O(1) per sphere
- **Space**: O(1) additional memory
- **Operations**: ~10 floating-point operations per intersection test

## 🧪 Testing and Validation

### Test Cases
```c
void test_sphere_intersection() {
    // Test 1: Ray through sphere center
    t_sphere sphere = {.center = {0, 0, 3}, .radius = 1.0};
    t_vec3 O = {0, 0, 0};
    t_vec3 D = {0, 0, 1};

    double t1, t2;
    IntersectRaySphere(O, D, sphere, &t1, &t2);

    assert(fabs(t1 - 4.0) < 1e-6);  // Exit point
    assert(fabs(t2 - 2.0) < 1e-6);  // Entry point

    // Test 2: Ray missing sphere
    t_vec3 D_miss = {1, 0, 0};
    IntersectRaySphere(O, D_miss, sphere, &t1, &t2);

    assert(t1 == DBL_MAX);
    assert(t2 == DBL_MAX);

    printf("Sphere intersection tests passed!\n");
}
```

### Edge Cases
1. **Ray origin inside sphere**: t1 > 0, t2 < 0
2. **Ray tangent to sphere**: t1 = t2
3. **Ray parallel to sphere**: No intersection
4. **Ray origin on sphere surface**: t1 = 0, t2 > 0

## 🔗 Related Functions

### Ray Tracing Integration
- `TraceRay()`: Basic sphere-only ray tracing
- `TraceRayWithLighting()`: Full lighting with spheres
- `get_sphere_hit()`: Get complete hit information

### Vector Operations
- `vec3_sub()`: Vector subtraction
- `vec3_dot()`: Dot product
- `vec3_normalize()`: Vector normalization

## 📚 References

- **Computer Graphics: Principles and Practice** - Foley, van Dam, Feiner, Hughes
- **Real-Time Rendering** - Akenine-Möller, Haines, Hoffman
- **Ray Tracing in One Weekend** - Peter Shirley

---

**Note**: This implementation provides accurate sphere-ray intersection calculations suitable for real-time ray tracing applications. The mathematical foundation ensures numerical stability and correct handling of edge cases.
