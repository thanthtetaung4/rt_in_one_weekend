#ifndef RAY_H
#define RAY_H

#include "point3.h"

typedef struct {
    point3 orig;
    vec3 dir;
} ray;

// Constructor
ray ray_create(point3 origin, vec3 direction);

// Getters
point3 ray_origin(ray r);
vec3 ray_direction(ray r);

// Compute a point along the ray at parameter t
point3 ray_at(ray r, double t);

#endif
