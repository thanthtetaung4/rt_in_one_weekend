#include "../../inc/rt.h"

t_color color_multiply(t_color a, t_color b) {
    t_color result;
    result.r = (a.r * b.r) / 255;
    result.g = (a.g * b.g) / 255;
    result.b = (a.b * b.b) / 255;
    return result;
}

t_color color_scale(t_color color, double factor) {
    t_color result;
    result.r = (int)(color.r * factor);
    result.g = (int)(color.g * factor);
    result.b = (int)(color.b * factor);
    return result;
}

t_color color_add(t_color a, t_color b) {
    t_color result;
    result.r = a.r + b.r;
    result.g = a.g + b.g;
    result.b = a.b + b.b;
    return result;
}

t_color color_clamp(t_color color) {
    t_color result;
    result.r = (color.r > 255) ? 255 : (color.r < 0) ? 0 : color.r;
    result.g = (color.g > 255) ? 255 : (color.g < 0) ? 0 : color.g;
    result.b = (color.b > 255) ? 255 : (color.b < 0) ? 0 : color.b;
    return result;
}

// Check if a point is in shadow by casting a ray to the light
int is_in_shadow(t_vec3 hit_point, t_vec3 light_direction, double light_distance,
                 t_sphere *spheres, int num_spheres,
                 t_cylinder *cylinders, int num_cylinders,
                 t_plane *planes, int num_planes) {
    t_vec3 shadow_ray_origin = hit_point;
    t_vec3 shadow_ray_direction = light_direction;

    // Check spheres
    for (int i = 0; i < num_spheres; i++) {
        double t1, t2;
        IntersectRaySphere(shadow_ray_origin, shadow_ray_direction, spheres[i], &t1, &t2);
        if (t1 > 0.001 && t1 < light_distance) return 1; // In shadow
        if (t2 > 0.001 && t2 < light_distance) return 1; // In shadow
    }

    // Check cylinders
    for (int i = 0; i < num_cylinders; i++) {
        double t1, t2;
        IntersectRayCylinder(shadow_ray_origin, shadow_ray_direction, cylinders[i], &t1, &t2);
        if (t1 > 0.001 && t1 < light_distance) return 1; // In shadow
        if (t2 > 0.001 && t2 < light_distance) return 1; // In shadow
    }

    // Check planes
    for (int i = 0; i < num_planes; i++) {
        double t;
        IntersectRayPlane(shadow_ray_origin, shadow_ray_direction, planes[i], &t);
        if (t > 0.001 && t < light_distance) return 1; // In shadow
    }

    return 0; // Not in shadow
}

t_color calculate_lighting(t_vec3 hit_point, t_vec3 normal, t_vec3 view_direction,
                          t_material material, t_ambient_light ambient,
                          t_point_light *lights, int num_lights,
                          t_sphere *spheres, int num_spheres,
                          t_cylinder *cylinders, int num_cylinders,
                          t_plane *planes, int num_planes) {
    t_color final_color = {0, 0, 0};

    // Ambient lighting
    t_color ambient_color = color_multiply(material.color, ambient.color);
    ambient_color = color_scale(ambient_color, material.ambient * ambient.intensity);
    final_color = color_add(final_color, ambient_color);

    // Point lights
    for (int i = 0; i < num_lights; i++) {
        t_point_light light = lights[i];

        // Calculate light direction and distance
        t_vec3 light_direction = vec3_sub(light.position, hit_point);
        double light_distance = sqrt(vec3_dot(light_direction, light_direction));
        light_direction = vec3_normalize(light_direction);

        // Check if point is in shadow
        if (is_in_shadow(hit_point, light_direction, light_distance,
                        spheres, num_spheres, cylinders, num_cylinders, planes, num_planes)) {
            continue; // Skip this light if in shadow
        }

        // Diffuse lighting
        double diffuse_factor = vec3_dot(normal, light_direction);
        if (diffuse_factor > 0) {
            t_color diffuse_color = color_multiply(material.color, light.color);
            diffuse_color = color_scale(diffuse_color, material.diffuse * diffuse_factor * light.intensity);
            final_color = color_add(final_color, diffuse_color);
        }

        // Specular lighting (Blinn-Phong model)
        t_vec3 half_vector = vec3_normalize(vec3_add(view_direction, light_direction));
        double specular_factor = vec3_dot(normal, half_vector);
        if (specular_factor > 0) {
            specular_factor = pow(specular_factor, material.shininess);
            t_color specular_color = color_multiply(material.color, light.color);
            specular_color = color_scale(specular_color, material.specular * specular_factor * light.intensity);
            final_color = color_add(final_color, specular_color);
        }
    }

    return color_clamp(final_color);
}
