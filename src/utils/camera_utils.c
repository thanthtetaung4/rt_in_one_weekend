#include "../../inc/rt.h"

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
