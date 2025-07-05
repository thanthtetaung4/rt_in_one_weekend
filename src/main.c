#include <stdio.h>
#include <math.h>
#include <float.h>
#include <stdlib.h>

# define PI 3.14159265358979323846

// ======================= Vector Operations =======================
typedef struct s_vec3 {
    double x, y, z;
} t_vec3;

t_vec3 vec3_create(double x, double y, double z) {
    return (t_vec3){x, y, z};
}

t_vec3 vec3_add(t_vec3 a, t_vec3 b) {
    return vec3_create(a.x + b.x, a.y + b.y, a.z + b.z);
}

t_vec3 vec3_sub(t_vec3 a, t_vec3 b) {
    return vec3_create(a.x - b.x, a.y - b.y, a.z - b.z);
}

t_vec3 vec3_scale(t_vec3 v, double s) {
    return vec3_create(v.x * s, v.y * s, v.z * s);
}

t_vec3 vec3_div(t_vec3 v, double s) {
    return vec3_create(v.x / s, v.y / s, v.z / s);
}

double vec3_dot(t_vec3 a, t_vec3 b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

t_vec3 vec3_cross(t_vec3 a, t_vec3 b) {
    return vec3_create(
        a.y * b.z - a.z * b.y,
        a.z * b.x - a.x * b.z,
        a.x * b.y - a.y * b.x
    );
}

t_vec3 vec3_normalize(t_vec3 v) {
    double len = sqrt(vec3_dot(v, v));
    return vec3_div(v, len);
}

// ======================= Camera and Scene =======================
typedef struct s_color {
    int r, g, b;
} t_color;

typedef struct s_sphere {
    t_vec3 center;
    double radius;
    t_color color;
} t_sphere;

typedef struct s_camera {
    t_vec3 P;     // Position
    t_vec3 D;     // Direction (normalized)
    double fov;   // Horizontal field of view in radians
} t_camera;

typedef struct s_camera_view {
    t_vec3 pixel00;
    t_vec3 pixel_delta_u;
    t_vec3 pixel_delta_v;
} t_camera_view;

// ======================= Ray Functions =======================
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

// ======================= Camera Setup =======================
t_camera_view setup_camera(t_camera camera, int image_width, int image_height) {
    t_camera_view view;

    t_vec3 forward = vec3_normalize(camera.D);
    t_vec3 world_up = (fabs(forward.y) == 1.0) ? vec3_create(0, 0, 1) : vec3_create(0, 1, 0);
    t_vec3 right = vec3_normalize(vec3_cross(world_up, forward));
    t_vec3 up = vec3_cross(forward, right);

    double aspect_ratio = (double)image_width / image_height;
    double viewport_width = 2.0 * tan(camera.fov / 2.0);
    double viewport_height = viewport_width / aspect_ratio;

    t_vec3 horizontal = vec3_scale(right, viewport_width);
    t_vec3 vertical = vec3_scale(up, viewport_height);

    t_vec3 focal_point = vec3_add(camera.P, forward);
    t_vec3 upper_left = vec3_sub(vec3_sub(focal_point,
                             vec3_scale(horizontal, 0.5)),
                             vec3_scale(vertical, 0.5));

    t_vec3 pixel_delta_u = vec3_div(horizontal, image_width);
    t_vec3 pixel_delta_v = vec3_div(vertical, image_height);
    t_vec3 pixel00 = vec3_add(upper_left, vec3_scale(vec3_add(pixel_delta_u, pixel_delta_v), 0.5));

    view.pixel00 = pixel00;
    view.pixel_delta_u = pixel_delta_u;
    view.pixel_delta_v = pixel_delta_v;

    return view;
}

// ======================= Render Scene =======================
void render_scene(FILE *f, t_camera camera, t_sphere *spheres, int num_spheres,
                  int width, int height) {
    t_color background = {0, 0, 0};
    t_camera_view view = setup_camera(camera, width, height);

    fprintf(f, "P3\n%d %d\n255\n", width, height);

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
			t_vec3 pixel = vec3_add(view.pixel00,
                vec3_add(vec3_scale(view.pixel_delta_u, x),
                         vec3_scale(view.pixel_delta_v, height - 1 - y)));
            t_vec3 ray_dir = vec3_normalize(vec3_sub(pixel, camera.P));
            t_color color = TraceRay(camera.P, ray_dir, 1.0, DBL_MAX,
                                     spheres, num_spheres, background);
            fprintf(f, "%d %d %d ", color.r, color.g, color.b);
        }
        fprintf(f, "\n");
    }
}

// ======================= Main =======================
int main() {
    int width = 800, height = 600;
    t_camera camera = {
        .P = vec3_create(0, 0, -1),
        .D = vec3_create(0, 0, 1),
        .fov = PI / 4 // 60 degrees in radians
    };

    t_sphere scene[] = {
        { .center = {0, -1, 3}, .radius = 1, .color = {255, 0, 0} },
        { .center = {2, 2, 4},  .radius = 1, .color = {0, 0, 255} },
        { .center = {-2, 3, 4}, .radius = 1, .color = {0, 255, 0} },
        { .center = {0, -5001, 0}, .radius = 5000, .color = {255, 255, 0} } // ground
    };

    FILE *f = fopen("image.ppm", "w");
    if (!f) {
        perror("Cannot open output file");
        return 1;
    }

    render_scene(f, camera, scene, 4, width, height);
    fclose(f);
    printf("Rendered image.ppm\n");
    return 0;
}
