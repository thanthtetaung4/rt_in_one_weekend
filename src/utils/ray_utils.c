#include "../../inc/rt.h"

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

    return closest_sphere->color;
}
