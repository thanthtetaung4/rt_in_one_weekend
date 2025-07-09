#include "rt.h"
#include <string.h>

t_scene	*create_scene(void)
{
	t_scene	*scene;

	scene = malloc(sizeof(t_scene));
	if (!scene)
	{
		printf("Error: Failed to allocate scene\n");
		return (NULL);
	}
	scene->spheres = NULL;
	scene->num_spheres = 0;
	scene->cylinders = NULL;
	scene->num_cylinders = 0;
	scene->planes = NULL;
	scene->num_planes = 0;
	scene->lights = NULL;
	scene->num_lights = 0;
	scene->background = (t_color){0, 0, 0};
	scene->width = 800;
	scene->height = 600;
	return (scene);
}

void	free_scene(t_scene *scene)
{
	if (!scene)
		return ;
	if (scene->spheres)
	{
		free(scene->spheres);
		scene->spheres = NULL;
	}
	if (scene->cylinders)
	{
		free(scene->cylinders);
		scene->cylinders = NULL;
	}
	if (scene->planes)
	{
		free(scene->planes);
		scene->planes = NULL;
	}
	if (scene->lights)
	{
		free(scene->lights);
		scene->lights = NULL;
	}
	free(scene);
}

// static t_color parse_color(const char *str) {
// 	t_color color = {0, 0, 0};
// 	sscanf(str, "%d,%d,%d", &color.r, &color.g, &color.b);
// 	return color;
// }

// static t_vec3 parse_vec3(const char *str) {
// 	t_vec3 v = {0, 0, 0};
// 	sscanf(str, "%lf,%lf,%lf", &v.x, &v.y, &v.z);
// 	return v;
// }

// static void parse_material(const char *str, t_material *mat) {
// 	mat->ambient = 0.1;
// 	mat->diffuse = 0.7;
// 	mat->specular = 0.2;
// 	mat->shininess = 20;
// 	const char *spc = strstr(str, "spc:");
// 	if (spc) {
// 		sscanf(spc + 4, "%lf,%lf", &mat->specular, &mat->shininess);
// 	}
// 	const char *mir = strstr(str, "mir:");
// 	if (mir) {
// 		sscanf(mir + 4, "%lf", &mat->ambient);
// 	}
// }

// int parse_rt_file(const char *filename, t_scene *scene) {
// 	FILE *f = fopen(filename, "r");
// 	if (!f) {
// 		printf("Error: Could not open %s\n", filename);
// 		return 0;
// 	}
// 	char line[256];
// 	int sphere_cap = 16, plane_cap = 16, light_cap = 8, cylinder_cap = 16;
// 	scene->spheres = malloc(sphere_cap * sizeof(t_sphere));
// 	scene->planes = malloc(plane_cap * sizeof(t_plane));
// 	scene->lights = malloc(light_cap * sizeof(t_point_light));
// 	scene->cylinders = malloc(cylinder_cap * sizeof(t_cylinder));
// 	scene->num_spheres = 0;
// 	scene->num_planes = 0;
// 	scene->num_lights = 0;
// 	scene->num_cylinders = 0;
// 	while (fgets(line, sizeof(line), f)) {
// 		char *p = line;
// 		while (*p == ' ' || *p == '\t') p++;
// 		if (*p == '\0' || *p == '\n' || *p == '#') continue;
// 		if (strncmp(p, "R", 1) == 0) {
// 			int w, h;
// 			sscanf(p + 1, "%d %d", &w, &h);
// 			scene->width = w;
// 			scene->height = h;
// 		} else if (strncmp(p, "A", 1) == 0) {
// 			double intensity; char colorstr[32];
// 			sscanf(p + 1, "%lf %31s", &intensity, colorstr);
// 			scene->ambient.intensity = intensity;
// 			scene->ambient.color = parse_color(colorstr);
// 		} else if (strncmp(p, "C", 1) == 0) {
// 			char pos[32], dir[32]; double fov;
// 			sscanf(p + 1, "%31s %31s %lf", pos, dir, &fov);
// 			scene->camera.P = parse_vec3(pos);
// 			scene->camera.D = parse_vec3(dir);
// 			scene->camera.fov = fov * (PI / 180.0);
// 		} else if (strncmp(p, "L", 1) == 0) {
// 			char pos[32], colorstr[32]; double intensity;
// 			sscanf(p + 1, "%31s %lf %31s", pos, &intensity, colorstr);
// 			if (scene->num_lights >= light_cap) {
// 				light_cap *= 2;
// 				scene->lights = realloc(scene->lights, light_cap * sizeof(t_point_light));
// 			}
// 			scene->lights[scene->num_lights].position = parse_vec3(pos);
// 			scene->lights[scene->num_lights].intensity = intensity;
// 			scene->lights[scene->num_lights].color = parse_color(colorstr);
// 			scene->num_lights++;
// 		} else if (strncmp(p, "pl", 2) == 0) {
// 			char point[32], normal[32], colorstr[32], matstr[64];
// 			int n = sscanf(p + 2, "%31s %31s %31s %63[^\n]", point, normal, colorstr, matstr);
// 			if (scene->num_planes >= plane_cap) {
// 				plane_cap *= 2;
// 				scene->planes = realloc(scene->planes, plane_cap * sizeof(t_plane));
// 			}
// 			scene->planes[scene->num_planes].point = parse_vec3(point);
// 			scene->planes[scene->num_planes].normal = parse_vec3(normal);
// 			scene->planes[scene->num_planes].material.color = parse_color(colorstr);
// 			parse_material(matstr, &scene->planes[scene->num_planes].material);
// 			scene->num_planes++;
// 		} else if (strncmp(p, "sp", 2) == 0) {
// 			char center[32], colorstr[32], matstr[64];
// 			double radius;
// 			int n = sscanf(p + 2, "%31s %lf %31s %63[^\n]", center, &radius, colorstr, matstr);
// 			if (scene->num_spheres >= sphere_cap) {
// 				sphere_cap *= 2;
// 				scene->spheres = realloc(scene->spheres, sphere_cap * sizeof(t_sphere));
// 			}
// 			scene->spheres[scene->num_spheres].center = parse_vec3(center);
// 			scene->spheres[scene->num_spheres].radius = radius;
// 			scene->spheres[scene->num_spheres].material.color = parse_color(colorstr);
// 			parse_material(matstr, &scene->spheres[scene->num_spheres].material);
// 			scene->num_spheres++;
// 		} else if (strncmp(p, "cy", 2) == 0) {
// 			char center[32], axis[32], colorstr[32], matstr[64];
// 			double radius, height;
// 			int n = sscanf(p + 2, "%31s %31s %lf %lf %31s %63[^\n]",
// 				center, axis, &radius, &height, colorstr, matstr);
// 			if (scene->num_cylinders >= cylinder_cap) {
// 				cylinder_cap *= 2;
// 				scene->cylinders = realloc(scene->cylinders,
// 					cylinder_cap * sizeof(t_cylinder));
// 			}
// 			scene->cylinders[scene->num_cylinders].center = parse_vec3(center);
// 			scene->cylinders[scene->num_cylinders].axis =
// 				vec3_normalize(parse_vec3(axis));
// 			scene->cylinders[scene->num_cylinders].radius = radius;
// 			scene->cylinders[scene->num_cylinders].height = height;
// 			scene->cylinders[scene->num_cylinders].material.color =
// 				parse_color(colorstr);
// 			parse_material(matstr,
// 				&scene->cylinders[scene->num_cylinders].material);
// 			scene->num_cylinders++;
// 		}
// 	}
// 	fclose(f);
// 	return 1;
// }
