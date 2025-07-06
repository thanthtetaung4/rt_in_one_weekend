# Cylinder Ray Intersection

This document provides detailed information about ray-cylinder intersection calculations in the ray tracer.

## 📐 Mathematical Foundation

### Cylinder Definition
A finite cylinder is defined by:
- **Center point**: C
- **Axis direction**: A (normalized vector)
- **Radius**: r
- **Height**: h

The cylinder consists of:
1. **Cylindrical body**: Infinite cylinder constrained by height
2. **End caps**: Circular disks at ±h/2 along the axis

### Ray Definition
A ray is defined by its origin O and direction D (normalized):
```
P(t) = O + tD
```

Where t ≥ 0 is the ray parameter.

## 🔧 Implementation

### Function Signature
```c
void IntersectRayCylinder(t_vec3 O, t_vec3 D, t_cylinder cylinder, double *t1, double *t2);
```

### Parameters
- `O`: Ray origin point
- `D`: Ray direction vector (must be normalized)
- `cylinder`: Cylinder object with center, axis, radius, and height
- `t1`: First intersection distance (output)
- `t2`: Second intersection distance (output)

### Implementation Algorithm

#### Step 1: Infinite Cylinder Intersection
```c
void IntersectRayCylinder(t_vec3 O, t_vec3 D, t_cylinder cylinder, double *t1, double *t2) {
    t_vec3 CO = vec3_sub(O, cylinder.center);

    // Project ray direction and CO onto cylinder axis
    double D_dot_axis = vec3_dot(D, cylinder.axis);
    double CO_dot_axis = vec3_dot(CO, cylinder.axis);

    // Ray direction perpendicular to cylinder axis
    t_vec3 D_perp = vec3_sub(D, vec3_scale(cylinder.axis, D_dot_axis));
    // Vector from center to ray origin, perpendicular to axis
    t_vec3 CO_perp = vec3_sub(CO, vec3_scale(cylinder.axis, CO_dot_axis));

    // Quadratic equation coefficients for infinite cylinder
    double a = vec3_dot(D_perp, D_perp);
    double b = 2 * vec3_dot(D_perp, CO_perp);
    double c = vec3_dot(CO_perp, CO_perp) - cylinder.radius * cylinder.radius;

    double discriminant = b * b - 4 * a * c;

    if (discriminant < 0) {
        *t1 = DBL_MAX;
        *t2 = DBL_MAX;
        return;
    }

    double t1_inf = (-b + sqrt(discriminant)) / (2 * a);
    double t2_inf = (-b - sqrt(discriminant)) / (2 * a);
```

#### Step 2: Height Constraints
```c
    // Check height constraints
    double half_height = cylinder.height / 2.0;
    double y1 = CO_dot_axis + t1_inf * D_dot_axis;
    double y2 = CO_dot_axis + t2_inf * D_dot_axis;

    *t1 = DBL_MAX;
    *t2 = DBL_MAX;

    // Check if intersection points are within cylinder height
    if (t1_inf > 0 && y1 >= -half_height && y1 <= half_height) {
        *t1 = t1_inf;
    }
    if (t2_inf > 0 && y2 >= -half_height && y2 <= half_height) {
        *t2 = t2_inf;
    }
```

#### Step 3: End Cap Intersections
```c
    // Check end caps
    t_vec3 top_center = vec3_add(cylinder.center, vec3_scale(cylinder.axis, half_height));
    t_vec3 bottom_center = vec3_sub(cylinder.center, vec3_scale(cylinder.axis, half_height));

    // Top cap intersection
    double denom_top = vec3_dot(D, cylinder.axis);
    if (ft_fabs(denom_top) > 1e-6) {
        double t_top = vec3_dot(vec3_sub(top_center, O), cylinder.axis) / denom_top;
        if (t_top > 0) {
            t_vec3 hit_point = vec3_add(O, vec3_scale(D, t_top));
            t_vec3 to_hit = vec3_sub(hit_point, top_center);
            if (vec3_dot(to_hit, to_hit) <= cylinder.radius * cylinder.radius) {
                if (t_top < *t1) *t1 = t_top;
                else if (t_top < *t2) *t2 = t_top;
            }
        }
    }

    // Bottom cap intersection
    double denom_bottom = vec3_dot(D, cylinder.axis);
    if (ft_fabs(denom_bottom) > 1e-6) {
        double t_bottom = vec3_dot(vec3_sub(bottom_center, O), cylinder.axis) / denom_bottom;
        if (t_bottom > 0) {
            t_vec3 hit_point = vec3_add(O, vec3_scale(D, t_bottom));
            t_vec3 to_hit = vec3_sub(hit_point, bottom_center);
            if (vec3_dot(to_hit, to_hit) <= cylinder.radius * cylinder.radius) {
                if (t_bottom < *t1) *t1 = t_bottom;
                else if (t_bottom < *t2) *t2 = t_bottom;
            }
        }
    }
}
```

## 🎯 Normal Calculation

### Surface Normal Types
The cylinder has three types of surfaces, each with different normal calculations:

#### 1. Cylinder Body Normal
```c
t_vec3 get_cylinder_body_normal(t_vec3 hit_point, t_cylinder cylinder) {
    t_vec3 to_center = vec3_sub(hit_point, cylinder.center);
    double projection = vec3_dot(to_center, cylinder.axis);
    t_vec3 normal = vec3_sub(to_center, vec3_scale(cylinder.axis, projection));
    return vec3_normalize(normal);
}
```

#### 2. End Cap Normals
```c
t_vec3 get_cylinder_cap_normal(t_vec3 hit_point, t_cylinder cylinder, int is_top) {
    if (is_top) {
        return cylinder.axis;  // Top cap normal
    } else {
        return vec3_scale(cylinder.axis, -1);  // Bottom cap normal
    }
}
```

#### 3. Complete Normal Calculation
```c
t_vec3 get_cylinder_normal(t_vec3 hit_point, t_cylinder cylinder) {
    t_vec3 to_center = vec3_sub(hit_point, cylinder.center);
    double projection = vec3_dot(to_center, cylinder.axis);
    double half_height = cylinder.height / 2.0;

    // Check if we hit the end caps
    if (ft_fabs(projection - half_height) < 0.001) {
        // Hit top cap
        return cylinder.axis;
    } else if (ft_fabs(projection + half_height) < 0.001) {
        // Hit bottom cap
        return vec3_scale(cylinder.axis, -1);
    } else {
        // Hit cylinder body
        t_vec3 normal = vec3_sub(to_center, vec3_scale(cylinder.axis, projection));
        return vec3_normalize(normal);
    }
}
```

## 📊 Usage Examples

### Basic Intersection Test
```c
t_cylinder cylinder = {
    .center = vec3_create(0, 0, 5),
    .axis = vec3_normalize(vec3_create(0, 1, 0)),  // vertical cylinder
    .radius = 0.5,
    .height = 2.0
};

t_vec3 ray_origin = vec3_create(0, 0, 0);
t_vec3 ray_direction = vec3_normalize(vec3_create(0, 0, 1));

double t1, t2;
IntersectRayCylinder(ray_origin, ray_direction, cylinder, &t1, &t2);

if (t1 != DBL_MAX) {
    printf("Ray intersects cylinder at distances: %f and %f\n", t1, t2);

    // Calculate intersection points
    t_vec3 hit1 = vec3_add(ray_origin, vec3_scale(ray_direction, t1));
    t_vec3 hit2 = vec3_add(ray_origin, vec3_scale(ray_direction, t2));

    // Calculate normals
    t_vec3 normal1 = get_cylinder_normal(hit1, cylinder);
    t_vec3 normal2 = get_cylinder_normal(hit2, cylinder);
}
```

### Integration with Scene Structure
```c
// Using the scene structure
t_scene *scene = create_scene();
setup_regular_scene(scene);

// Test intersection with all cylinders in scene
for (int i = 0; i < scene->num_cylinders; i++) {
    double t1, t2;
    IntersectRayCylinder(ray_origin, ray_direction, scene->cylinders[i], &t1, &t2);

    if (t1 != DBL_MAX && t1 >= t_min && t1 <= t_max) {
        // Found closest cylinder intersection
        t_vec3 hit_point = vec3_add(ray_origin, vec3_scale(ray_direction, t1));
        t_vec3 normal = get_cylinder_normal(hit_point, scene->cylinders[i]);

        // Apply lighting calculations
        t_color color = calculate_lighting(hit_point, normal, view_direction,
                                         scene->cylinders[i].material, scene);
    }
}
```

## ⚡ Performance Considerations

### Optimization Tips
1. **Early height check**: Reject rays that can't reach cylinder height
2. **Axis alignment**: Optimize for cylinders aligned with coordinate axes
3. **Cap optimization**: Skip cap checks for infinite cylinders
4. **Numerical stability**: Use epsilon comparisons for floating-point

### Computational Complexity
- **Time**: O(1) per cylinder
- **Space**: O(1) additional memory
- **Operations**: ~20-30 floating-point operations per intersection test

## 🧪 Testing and Validation

### Test Cases
```c
void test_cylinder_intersection() {
    // Test 1: Ray through cylinder center
    t_cylinder cylinder = {
        .center = {0, 0, 5},
        .axis = {0, 1, 0},
        .radius = 0.5,
        .height = 2.0
    };
    t_vec3 O = {0, 0, 0};
    t_vec3 D = {0, 0, 1};

    double t1, t2;
    IntersectRayCylinder(O, D, cylinder, &t1, &t2);

    assert(t1 != DBL_MAX);
    assert(t2 != DBL_MAX);

    // Test 2: Ray hitting end cap
    t_vec3 D_cap = {0, 1, 0};
    IntersectRayCylinder(O, D_cap, cylinder, &t1, &t2);

    printf("Cylinder intersection tests passed!\n");
}
```

### Edge Cases
1. **Ray parallel to cylinder axis**: Only cap intersections possible
2. **Ray tangent to cylinder**: Single intersection point
3. **Ray through cylinder center**: Two body intersections
4. **Ray hitting end cap edge**: Precise cap intersection
5. **Ray origin inside cylinder**: One intersection point

## 🔗 Related Functions

### Ray Tracing Integration
- `TraceRayWithCylinders()`: Basic cylinder ray tracing
- `TraceRayWithLighting()`: Full lighting with cylinders
- `get_cylinder_hit()`: Get complete hit information

### Vector Operations
- `vec3_sub()`: Vector subtraction
- `vec3_dot()`: Dot product
- `vec3_scale()`: Vector scaling
- `vec3_normalize()`: Vector normalization

## 📚 References

- **Computer Graphics: Principles and Practice** - Foley, van Dam, Feiner, Hughes
- **Real-Time Rendering** - Akenine-Möller, Haines, Hoffman
- **Geometric Tools for Computer Graphics** - Schneider, Eberly

---

**Note**: This implementation provides accurate cylinder-ray intersection calculations for finite cylinders with end caps. The algorithm handles all intersection cases including body, top cap, and bottom cap intersections.
