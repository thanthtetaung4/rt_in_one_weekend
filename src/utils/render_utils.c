#include "../../inc/rt.h"

static void	render_pixel_row(FILE *f, t_camera_view view, t_scene *scene, int y,
		t_color (*trace_func)(t_vec3, t_vec3, double, double, t_scene *))
{
	int		x;
	t_vec3	pixel;
	t_vec3	ray_dir;
	t_color	color;

	x = 0;
	while (x < scene->width)
	{
		pixel = vec3_add(view.pixel00,
			vec3_add(vec3_scale(view.pixel_delta_u, x),
				vec3_scale(view.pixel_delta_v, scene->height - 1 - y)));
		ray_dir = vec3_normalize(vec3_sub(pixel, scene->camera.P));
		color = trace_func(scene->camera.P, ray_dir, 1.0, DBL_MAX, scene);
		fprintf(f, "%d %d %d ", color.r, color.g, color.b);
		x++;
	}
	fprintf(f, "\n");
}

static void	render_scene_internal(FILE *f, t_scene *scene,
		t_color (*trace_func)(t_vec3, t_vec3, double, double, t_scene *))
{
	t_camera_view	view;
	int				y;

	view = setup_camera(scene->camera, scene->width, scene->height);
	fprintf(f, "P3\n%d %d\n255\n", scene->width, scene->height);
	y = 0;
	while (y < scene->height)
	{
		render_pixel_row(f, view, scene, y, trace_func);
		y++;
	}
}

void	render_scene(FILE *f, t_scene *scene)
{
	render_scene_internal(f, scene, TraceRay);
}

void	render_scene_with_cylinders(FILE *f, t_scene *scene)
{
	render_scene_internal(f, scene, TraceRayWithCylinders);
}

void	render_scene_with_planes(FILE *f, t_scene *scene)
{
	render_scene_internal(f, scene, TraceRayWithPlanes);
}

void	render_scene_with_lighting(FILE *f, t_scene *scene)
{
	render_scene_internal(f, scene, TraceRayWithLighting);
}
