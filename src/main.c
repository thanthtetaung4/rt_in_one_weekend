#include "../inc/rt.h"
#include <stdio.h>
#include <stdbool.h>

bool	hit_sphere(point3 center, double radius, ray r)
{
	vec3	oc;
	double	a;
	double	b;
	double	c;
	double	discriminant;

	oc = vec3_sub(ray_origin(r), center);
	a = vec3_dot(ray_direction(r), ray_direction(r));
	b = 2.0 * vec3_dot(oc, ray_direction(r));
	c = vec3_dot(oc, oc) - radius * radius;
	discriminant = b * b - 4 * a * c;
	return (discriminant >= 0);
}

color	ray_color(ray r)
{
	point3	sphere_center;
	double	sphere_radius;
	vec3	unit_direction;
	double	a;
	color	white;
	color	blue;
	color	c1;
	color	c2;

	sphere_center = vec3_create(0, 0, -1);
	sphere_radius = 0.5;
	if (hit_sphere(sphere_center, sphere_radius, r))
	{
		return (vec3_create(1.0, 0.0, 0.0)); // Red
	}
	unit_direction = vec3_unit(ray_direction(r));
	a = 0.5 * (unit_direction.y + 1.0);
	white = vec3_create(1.0, 1.0, 1.0);
	blue = vec3_create(0.5, 0.7, 1.0);
	c1 = vec3_scale(white, 1.0 - a);
	c2 = vec3_scale(blue, a);
	return (vec3_add(c1, c2));
}

int	main(void)
{
	double	aspect_ratio;
	int		image_width;
	int		image_height;
	double	focal_length;
	double	viewport_height;
	double	viewport_width;
	point3	camera_center;
	vec3	viewport_u;
	vec3	viewport_v;
	vec3	pixel_delta_u;
	vec3	pixel_delta_v;
	vec3	half_u;
	vec3	half_v;
	vec3	focus_vec;
	vec3	half_pixel_offset;
	vec3	pixel00_loc;
	vec3	offset_u;
	vec3	offset_v;
	vec3	pixel_center;
	vec3	ray_direction;
	ray		r;
	color	pixel_color;

	// Image
	aspect_ratio = 16.0 / 9.0;
	image_width = 400;
	image_height = (int)(image_width / aspect_ratio);
	if (image_height < 1)
		image_height = 1;
	// Camera parameters
	focal_length = 1.0;
	viewport_height = 2.0;
	viewport_width = viewport_height * ((double)image_width / image_height);
	camera_center = vec3_create(0, 0, 0);
	// Viewport vectors
	viewport_u = vec3_create(viewport_width, 0, 0);
	viewport_v = vec3_create(0, -viewport_height, 0);
	// Pixel delta vectors
	pixel_delta_u = vec3_div(viewport_u, (double)image_width);
	pixel_delta_v = vec3_div(viewport_v, (double)image_height);
	// Upper left corner of viewport
	half_u = vec3_scale(viewport_u, 0.5);
	half_v = vec3_scale(viewport_v, 0.5);
	focus_vec = vec3_create(0, 0, focal_length);
	// camera_center- focal_length in z
	vec3 viewport_upper_left = vec3_sub(vec3_sub(vec3_sub(camera_center,
															focus_vec),
													half_u),
										half_v);
	// Location of upper left pixel center (offset by half pixel)
	half_pixel_offset = vec3_scale(vec3_add(pixel_delta_u, pixel_delta_v), 0.5);
	pixel00_loc = vec3_add(viewport_upper_left, half_pixel_offset);
	// Write PPM header
	printf("P3\n%d %d\n255\n", image_width, image_height);
	for (int j = 0; j < image_height; j++)
	{
		fprintf(stderr, "\rScanlines remaining: %d ", image_height - j);
		for (int i = 0; i < image_width; i++)
		{
			// Calculate pixel center position
			offset_u = vec3_scale(pixel_delta_u, (double)i);
			offset_v = vec3_scale(pixel_delta_v, (double)j);
			pixel_center = vec3_add(pixel00_loc, vec3_add(offset_u, offset_v));
			ray_direction = vec3_sub(pixel_center, camera_center);
			r = ray_create(camera_center, ray_direction);
			pixel_color = ray_color(r);
			write_color(stdout, pixel_color);
		}
	}
	fprintf(stderr, "\rDone.                 \n");
	return (0);
}
