#include "../../inc/rt.h"

// Hit record structure to store intersection information
typedef struct s_hit_record {
    double t;           // Intersection distance
    t_vec3 point;       // Hit point
    t_vec3 normal;      // Surface normal
    t_material material; // Material at hit point
    int hit;            // Whether we hit something
} t_hit_record;

void IntersectRaySphere(t_vec3 O, t_vec3 D, t_sphere sphere, double *t1, double *t2) {
    t_vec3 CO = vec3_sub(O, sphere.center);
    double a = vec3_dot(D, D);
    double b = 2 * vec3_dot(CO, D);
    double c = vec3_dot(CO, CO) - sphere.radius * sphere.radius;
    double discriminant = b * b - 4 * a * c;

    if (discriminant < 0) {
        *t1 = DBL_MAX;
        *t2 = DBL_MAX;
        return;
    }

    *t1 = (-b + sqrt(discriminant)) / (2 * a);
    *t2 = (-b - sqrt(discriminant)) / (2 * a);
}

void IntersectRayCylinder(t_vec3 O, t_vec3 D, t_cylinder cylinder, double *t1, double *t2) {
    // Vector from cylinder center to ray origin
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

t_color TraceRay(t_vec3 O, t_vec3 D, double t_min, double t_max,
                 t_sphere *spheres, int num_spheres, t_color background) {
    double closest_t = DBL_MAX;
    t_sphere *closest_sphere = NULL;

    for (int i = 0; i < num_spheres; i++) {
        double t1, t2;
        IntersectRaySphere(O, D, spheres[i], &t1, &t2);

        if (t1 >= t_min && t1 <= t_max && t1 < closest_t) {
            closest_t = t1;
            closest_sphere = &spheres[i];
        }
        if (t2 >= t_min && t2 <= t_max && t2 < closest_t) {
            closest_t = t2;
            closest_sphere = &spheres[i];
        }
    }

    if (closest_sphere == NULL)
        return background;

    return closest_sphere->material.color;
}

t_color TraceRayWithCylinders(t_vec3 O, t_vec3 D, double t_min, double t_max,
                              t_sphere *spheres, int num_spheres,
                              t_cylinder *cylinders, int num_cylinders,
                              t_color background) {
    double closest_t = DBL_MAX;
    t_color closest_color = background;

    // Check spheres
    for (int i = 0; i < num_spheres; i++) {
        double t1, t2;
        IntersectRaySphere(O, D, spheres[i], &t1, &t2);

        if (t1 >= t_min && t1 <= t_max && t1 < closest_t) {
            closest_t = t1;
            closest_color = spheres[i].material.color;
        }
        if (t2 >= t_min && t2 <= t_max && t2 < closest_t) {
            closest_t = t2;
            closest_color = spheres[i].material.color;
        }
    }

    // Check cylinders
    for (int i = 0; i < num_cylinders; i++) {
        double t1, t2;
        IntersectRayCylinder(O, D, cylinders[i], &t1, &t2);

        if (t1 >= t_min && t1 <= t_max && t1 < closest_t) {
            closest_t = t1;
            closest_color = cylinders[i].material.color;
        }
        if (t2 >= t_min && t2 <= t_max && t2 < closest_t) {
            closest_t = t2;
            closest_color = cylinders[i].material.color;
        }
    }

    return closest_color;
}

t_color TraceRayWithPlanes(t_vec3 O, t_vec3 D, double t_min, double t_max,
                           t_sphere *spheres, int num_spheres,
                           t_cylinder *cylinders, int num_cylinders,
                           t_plane *planes, int num_planes,
                           t_color background) {
    double closest_t = DBL_MAX;
    t_color closest_color = background;

    // Check spheres
    for (int i = 0; i < num_spheres; i++) {
        double t1, t2;
        IntersectRaySphere(O, D, spheres[i], &t1, &t2);

        if (t1 >= t_min && t1 <= t_max && t1 < closest_t) {
            closest_t = t1;
            closest_color = spheres[i].material.color;
        }
        if (t2 >= t_min && t2 <= t_max && t2 < closest_t) {
            closest_t = t2;
            closest_color = spheres[i].material.color;
        }
    }

    // Check cylinders
    for (int i = 0; i < num_cylinders; i++) {
        double t1, t2;
        IntersectRayCylinder(O, D, cylinders[i], &t1, &t2);

        if (t1 >= t_min && t1 <= t_max && t1 < closest_t) {
            closest_t = t1;
            closest_color = cylinders[i].material.color;
        }
        if (t2 >= t_min && t2 <= t_max && t2 < closest_t) {
            closest_t = t2;
            closest_color = cylinders[i].material.color;
        }
    }

    // Check planes
    for (int i = 0; i < num_planes; i++) {
        double t;
        IntersectRayPlane(O, D, planes[i], &t);

        if (t >= t_min && t <= t_max && t < closest_t) {
            closest_t = t;
            closest_color = planes[i].material.color;
        }
    }

    return closest_color;
}

// Helper function to get sphere hit information
t_hit_record get_sphere_hit(t_vec3 O, t_vec3 D, t_sphere sphere, double t) {
    t_hit_record hit;
    hit.t = t;
    hit.point = vec3_add(O, vec3_scale(D, t));
    hit.normal = vec3_normalize(vec3_sub(hit.point, sphere.center));
    hit.material = sphere.material;
    hit.hit = 1;
    return hit;
}

// Helper function to get cylinder hit information
t_hit_record get_cylinder_hit(t_vec3 O, t_vec3 D, t_cylinder cylinder, double t) {
    t_hit_record hit;
    hit.t = t;
    hit.point = vec3_add(O, vec3_scale(D, t));

    // Calculate normal based on where we hit the cylinder
    t_vec3 to_center = vec3_sub(hit.point, cylinder.center);
    double projection = vec3_dot(to_center, cylinder.axis);

    // Check if we hit the end caps
    double half_height = cylinder.height / 2.0;
    t_vec3 top_center = vec3_add(cylinder.center, vec3_scale(cylinder.axis, half_height));
    t_vec3 bottom_center = vec3_sub(cylinder.center, vec3_scale(cylinder.axis, half_height));

    if (ft_fabs(projection - half_height) < 0.001) {
        // Hit top cap
        hit.normal = cylinder.axis;
    } else if (ft_fabs(projection + half_height) < 0.001) {
        // Hit bottom cap
        hit.normal = vec3_scale(cylinder.axis, -1);
    } else {
        // Hit cylinder body
        t_vec3 normal = vec3_sub(to_center, vec3_scale(cylinder.axis, projection));
        hit.normal = vec3_normalize(normal);
    }

    hit.material = cylinder.material;
    hit.hit = 1;
    return hit;
}

// Helper function to get plane hit information
t_hit_record get_plane_hit(t_vec3 O, t_vec3 D, t_plane plane, double t) {
    t_hit_record hit;
    hit.t = t;
    hit.point = vec3_add(O, vec3_scale(D, t));
    hit.normal = plane.normal;
    hit.material = plane.material;
    hit.hit = 1;
    return hit;
}

// New trace function that returns hit information
t_hit_record TraceRayHit(t_vec3 O, t_vec3 D, double t_min, double t_max,
                         t_sphere *spheres, int num_spheres,
                         t_cylinder *cylinders, int num_cylinders,
                         t_plane *planes, int num_planes) {
    t_hit_record closest_hit = {DBL_MAX, {0, 0, 0}, {0, 0, 0}, {{0, 0, 0}, 0, 0, 0, 0}, 0};

    // Check spheres
    for (int i = 0; i < num_spheres; i++) {
        double t1, t2;
        IntersectRaySphere(O, D, spheres[i], &t1, &t2);

        if (t1 >= t_min && t1 <= t_max && t1 < closest_hit.t) {
            closest_hit = get_sphere_hit(O, D, spheres[i], t1);
        }
        if (t2 >= t_min && t2 <= t_max && t2 < closest_hit.t) {
            closest_hit = get_sphere_hit(O, D, spheres[i], t2);
        }
    }

    // Check cylinders
    for (int i = 0; i < num_cylinders; i++) {
        double t1, t2;
        IntersectRayCylinder(O, D, cylinders[i], &t1, &t2);

        if (t1 >= t_min && t1 <= t_max && t1 < closest_hit.t) {
            closest_hit = get_cylinder_hit(O, D, cylinders[i], t1);
        }
        if (t2 >= t_min && t2 <= t_max && t2 < closest_hit.t) {
            closest_hit = get_cylinder_hit(O, D, cylinders[i], t2);
        }
    }

    // Check planes
    for (int i = 0; i < num_planes; i++) {
        double t;
        IntersectRayPlane(O, D, planes[i], &t);

        if (t >= t_min && t <= t_max && t < closest_hit.t) {
            closest_hit = get_plane_hit(O, D, planes[i], t);
        }
    }

    return closest_hit;
}

// Trace function with lighting
t_color TraceRayWithLighting(t_vec3 O, t_vec3 D, double t_min, double t_max,
                             t_sphere *spheres, int num_spheres,
                             t_cylinder *cylinders, int num_cylinders,
                             t_plane *planes, int num_planes,
                             t_ambient_light ambient,
                             t_point_light *lights, int num_lights,
                             t_color background) {
    t_hit_record hit = TraceRayHit(O, D, t_min, t_max, spheres, num_spheres,
                                  cylinders, num_cylinders, planes, num_planes);

    if (!hit.hit) {
        return background;
    }

    // Calculate lighting
    t_vec3 view_direction = vec3_normalize(vec3_sub(O, hit.point));
    return calculate_lighting(hit.point, hit.normal, view_direction,
                             hit.material, ambient, lights, num_lights,
                             spheres, num_spheres, cylinders, num_cylinders, planes, num_planes);
}
