#include "../../inc/rt.h"
t_camera_view	setup_camera(t_camera camera, t_scene *scene)
{
	t_camera_view	view;
	t_vec3			world_up;
	t_vec3			horizontal;
	t_vec3			vertical;

	camera.dir_forward = vec3_normalize(camera.d);
	if (fabs(camera.dir_forward.y) == 1.0)
		world_up = vec3_create(0, 0, 1);
	else
		world_up = vec3_create(0, 1, 0);
	camera.dir_right = vec3_normalize(vec3_cross(world_up, camera.dir_forward));
	camera.dir_up = vec3_cross(camera.dir_forward, camera.dir_right);
	view.width = 2.0 * tan(camera.fov / 2.0);
	view.height = view.width / ((double)scene->width / scene->height);
	horizontal = vec3_scale(camera.dir_right, view.width);
	vertical = vec3_scale(camera.dir_up, view.height);
	camera.foc_point = vec3_add(camera.p, camera.dir_forward);
	view.upper_left = vec3_sub(vec3_sub(camera.foc_point,
				vec3_scale(horizontal, 0.5)),
			vec3_scale(vertical, 0.5));
	view.pixel_delta_u = vec3_div(horizontal, scene->width);
	view.pixel_delta_v = vec3_div(vertical, scene->height);
	view.pixel00 = vec3_add(view.upper_left, vec3_scale(
				vec3_add(view.pixel_delta_u, view.pixel_delta_v), 0.5));
	return (view);
}
