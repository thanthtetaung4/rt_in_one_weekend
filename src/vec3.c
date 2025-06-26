#include <math.h>
#include <stdio.h>
#include "../inc/vec3.h"

vec3 vec3_create(double x, double y, double z) {
    vec3 v = {x, y, z};
    return v;
}

vec3 vec3_neg(vec3 v) {
    return vec3_create(-v.x, -v.y, -v.z);
}

vec3 vec3_add(vec3 a, vec3 b) {
    return vec3_create(a.x + b.x, a.y + b.y, a.z + b.z);
}

vec3 vec3_sub(vec3 a, vec3 b) {
    return vec3_create(a.x - b.x, a.y - b.y, a.z - b.z);
}

vec3 vec3_mul(vec3 a, vec3 b) {
    return vec3_create(a.x * b.x, a.y * b.y, a.z * b.z);
}

vec3 vec3_scale(vec3 v, double t) {
    return vec3_create(v.x * t, v.y * t, v.z * t);
}

vec3 vec3_div(vec3 v, double t) {
    return vec3_scale(v, 1.0 / t);
}

double vec3_dot(vec3 a, vec3 b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

vec3 vec3_cross(vec3 a, vec3 b) {
    return vec3_create(
        a.y * b.z - a.z * b.y,
        a.z * b.x - a.x * b.z,
        a.x * b.y - a.y * b.x
    );
}

double vec3_length(vec3 v) {
    return sqrt(vec3_length_squared(v));
}

double vec3_length_squared(vec3 v) {
    return v.x * v.x + v.y * v.y + v.z * v.z;
}

vec3 vec3_unit(vec3 v) {
    return vec3_div(v, vec3_length(v));
}

void vec3_print(vec3 v) {
    printf("%f %f %f\n", v.x, v.y, v.z);
}
