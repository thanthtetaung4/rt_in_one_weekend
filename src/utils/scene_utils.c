#include "../../inc/rt.h"

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

static t_material	create_red_material(void)
{
	return ((t_material){
		.color = {255, 0, 0},
		.ambient = 0.2,
		.diffuse = 0.7,
		.specular = 0.3,
		.shininess = 50
	});
}

static t_material	create_blue_material(void)
{
	return ((t_material){
		.color = {0, 0, 255},
		.ambient = 0.2,
		.diffuse = 0.8,
		.specular = 0.5,
		.shininess = 100
	});
}

static t_material	create_green_material(void)
{
	return ((t_material){
		.color = {0, 255, 0},
		.ambient = 0.2,
		.diffuse = 0.6,
		.specular = 0.4,
		.shininess = 30
	});
}

static t_material	create_yellow_material(void)
{
	return ((t_material){
		.color = {255, 255, 0},
		.ambient = 0.3,
		.diffuse = 0.5,
		.specular = 0.2,
		.shininess = 10
	});
}

static t_material	create_magenta_material(void)
{
	return ((t_material){
		.color = {255, 0, 255},
		.ambient = 0.2,
		.diffuse = 0.7,
		.specular = 0.6,
		.shininess = 80
	});
}

static t_material	create_cyan_material(void)
{
	return ((t_material){
		.color = {0, 255, 255},
		.ambient = 0.2,
		.diffuse = 0.6,
		.specular = 0.4,
		.shininess = 40
	});
}

static void	setup_camera_regular(t_scene *scene)
{
	scene->camera = (t_camera){
		.P = vec3_create(0, 0, -1),
		.D = vec3_create(0, 0, 1),
		.fov = PI / 4
	};
}

static void	setup_spheres_regular(t_scene *scene)
{
	t_material	red_material;
	t_material	blue_material;
	t_material	green_material;
	t_material	yellow_material;

	red_material = create_red_material();
	blue_material = create_blue_material();
	green_material = create_green_material();
	yellow_material = create_yellow_material();
	scene->num_spheres = 4;
	scene->spheres = malloc(scene->num_spheres * sizeof(t_sphere));
	scene->spheres[0] = (t_sphere){.center = {0, -1, 3}, .radius = 1, .material = red_material};
	scene->spheres[1] = (t_sphere){.center = {2, 2, 4}, .radius = 1, .material = blue_material};
	scene->spheres[2] = (t_sphere){.center = {-2, 3, 4}, .radius = 1, .material = green_material};
	scene->spheres[3] = (t_sphere){.center = {0, -5001, 0}, .radius = 5000, .material = yellow_material};
}

static void	setup_cylinders_regular(t_scene *scene)
{
	t_material	magenta_material;
	t_material	cyan_material;

	magenta_material = create_magenta_material();
	cyan_material = create_cyan_material();
	scene->num_cylinders = 2;
	scene->cylinders = malloc(scene->num_cylinders * sizeof(t_cylinder));
	scene->cylinders[0] = (t_cylinder){
		.center = {0, 0, 5},
		.axis = vec3_normalize(vec3_create(0, 1, 0)),
		.radius = 0.5,
		.height = 2.0,
		.material = magenta_material
	};
	scene->cylinders[1] = (t_cylinder){
		.center = {3, 0, 4},
		.axis = vec3_normalize(vec3_create(1, 0, 0)),
		.radius = 0.3,
		.height = 1.5,
		.material = cyan_material
	};
}

static void	setup_planes_regular(t_scene *scene)
{
	t_material	cyan_material;

	cyan_material = create_cyan_material();
	scene->num_planes = 1;
	scene->planes = malloc(scene->num_planes * sizeof(t_plane));
	scene->planes[0] = (t_plane){
		.point = {0, 0, 8},
		.normal = vec3_normalize(vec3_create(0, 0, -1)),
		.material = cyan_material
	};
}

static void	setup_lighting_regular(t_scene *scene)
{
	scene->ambient = (t_ambient_light){
		.intensity = 0.3,
		.color = {255, 255, 255}
	};
	scene->num_lights = 2;
	scene->lights = malloc(scene->num_lights * sizeof(t_point_light));
	scene->lights[0] = (t_point_light){
		.position = {2, 3, -2},
		.intensity = 1.0,
		.color = {255, 255, 255}
	};
	scene->lights[1] = (t_point_light){
		.position = {-2, 2, 2},
		.intensity = 0.8,
		.color = {255, 0, 0}
	};
}

void	setup_regular_scene(t_scene *scene)
{
	if (!scene)
		return ;
	setup_camera_regular(scene);
	setup_spheres_regular(scene);
	setup_cylinders_regular(scene);
	setup_planes_regular(scene);
	setup_lighting_regular(scene);
}

static t_material	create_black_material(void)
{
	return ((t_material){
		.color = {20, 20, 20},
		.ambient = 0.1,
		.diffuse = 0.3,
		.specular = 0.1,
		.shininess = 10
	});
}

static void	setup_camera_box(t_scene *scene)
{
	scene->camera = (t_camera){
		.P = vec3_create(0, 0, -4),
		.D = vec3_create(0, 0, 1),
		.fov = PI / 3
	};
}

static void	setup_spheres_box(t_scene *scene)
{
	t_material	red_material;
	t_material	blue_material;
	t_material	green_material;

	red_material = create_red_material();
	blue_material = create_blue_material();
	green_material = create_green_material();
	scene->num_spheres = 3;
	scene->spheres = malloc(scene->num_spheres * sizeof(t_sphere));
	scene->spheres[0] = (t_sphere){
		.center = {0, 0, 2},
		.radius = 0.8,
		.material = red_material
	};
	scene->spheres[1] = (t_sphere){
		.center = {-1.5, 0, 1},
		.radius = 0.6,
		.material = blue_material
	};
	scene->spheres[2] = (t_sphere){
		.center = {1.5, 0, 1},
		.radius = 0.6,
		.material = green_material
	};
}

static void	setup_cylinders_box(t_scene *scene)
{
	t_material	yellow_material;

	yellow_material = create_yellow_material();
	scene->num_cylinders = 2;
	scene->cylinders = malloc(scene->num_cylinders * sizeof(t_cylinder));
	scene->cylinders[0] = (t_cylinder){
		.center = {0, -0.5, 0},
		.axis = vec3_normalize(vec3_create(0, 1, 0)),
		.radius = 0.4,
		.height = 1.5,
		.material = yellow_material
	};
	scene->cylinders[1] = (t_cylinder){
		.center = {0, 0.5, 0},
		.axis = vec3_normalize(vec3_create(1, 0, 0)),
		.radius = 0.3,
		.height = 2.0,
		.material = yellow_material
	};
}

static void	setup_planes_box(t_scene *scene)
{
	t_material	black_material;

	black_material = create_black_material();
	scene->num_planes = 4;
	scene->planes = malloc(scene->num_planes * sizeof(t_plane));
	scene->planes[0] = (t_plane){
		.point = {-3, 0, 0},
		.normal = vec3_normalize(vec3_create(1, 0, 0)),
		.material = black_material
	};
	scene->planes[1] = (t_plane){
		.point = {3, 0, 0},
		.normal = vec3_normalize(vec3_create(-1, 0, 0)),
		.material = black_material
	};
	scene->planes[2] = (t_plane){
		.point = {0, 3, 0},
		.normal = vec3_normalize(vec3_create(0, -1, 0)),
		.material = black_material
	};
	scene->planes[3] = (t_plane){
		.point = {0, -3, 0},
		.normal = vec3_normalize(vec3_create(0, 1, 0)),
		.material = black_material
	};
}

static void	setup_lighting_box(t_scene *scene)
{
	scene->ambient = (t_ambient_light){
		.intensity = 0.2,
		.color = {255, 255, 255}
	};
	scene->num_lights = 2;
	scene->lights = malloc(scene->num_lights * sizeof(t_point_light));
	scene->lights[0] = (t_point_light){
		.position = {0, 2, -2},
		.intensity = 1.0,
		.color = {255, 255, 255}
	};
	scene->lights[1] = (t_point_light){
		.position = {2, 0, 2},
		.intensity = 0.8,
		.color = {255, 255, 255}
	};
}

void	setup_box_scene(t_scene *scene)
{
	if (!scene)
		return ;
	setup_camera_box(scene);
	setup_spheres_box(scene);
	setup_cylinders_box(scene);
	setup_planes_box(scene);
	setup_lighting_box(scene);
}

static t_material	create_pipe_material(void)
{
	return ((t_material){
		.color = {100, 100, 100},
		.ambient = 0.3,
		.diffuse = 0.5,
		.specular = 0.2,
		.shininess = 20
	});
}

static t_material	create_purple_material(void)
{
	return ((t_material){
		.color = {128, 0, 128},
		.ambient = 0.2,
		.diffuse = 0.6,
		.specular = 0.4,
		.shininess = 40
	});
}

static void	setup_camera_pipe(t_scene *scene)
{
	scene->camera = (t_camera){
		.P = vec3_create(0, 0, 0),
		.D = vec3_create(0, 0, 1),
		.fov = PI / 4
	};
}

static void	setup_spheres_pipe(t_scene *scene)
{
	t_material	red_material;
	t_material	blue_material;
	t_material	green_material;
	t_material	yellow_material;
	t_material	purple_material;

	red_material = create_red_material();
	blue_material = create_blue_material();
	green_material = create_green_material();
	yellow_material = create_yellow_material();
	purple_material = create_purple_material();
	scene->num_spheres = 5;
	scene->spheres = malloc(scene->num_spheres * sizeof(t_sphere));
	scene->spheres[0] = (t_sphere){
		.center = {1.5, 1.0, 3},
		.radius = 0.4,
		.material = red_material
	};
	scene->spheres[1] = (t_sphere){
		.center = {-1.2, 0.8, 5},
		.radius = 0.3,
		.material = blue_material
	};
	scene->spheres[2] = (t_sphere){
		.center = {0.8, -1.5, 7},
		.radius = 0.5,
		.material = green_material
	};
	scene->spheres[3] = (t_sphere){
		.center = {-0.5, -0.8, 9},
		.radius = 0.2,
		.material = yellow_material
	};
	scene->spheres[4] = (t_sphere){
		.center = {2.0, -0.3, 11},
		.radius = 0.35,
		.material = purple_material
	};
}

static void	setup_cylinders_pipe(t_scene *scene)
{
	t_material	pipe_material;
	t_material	yellow_material;
	t_material	purple_material;

	pipe_material = create_pipe_material();
	yellow_material = create_yellow_material();
	purple_material = create_purple_material();
	scene->num_cylinders = 3;
	scene->cylinders = malloc(scene->num_cylinders * sizeof(t_cylinder));
	scene->cylinders[0] = (t_cylinder){
		.center = {0, 0, 0},
		.axis = vec3_normalize(vec3_create(0, 0, 1)),
		.radius = 2.0,
		.height = 100.0,
		.material = pipe_material
	};
	scene->cylinders[1] = (t_cylinder){
		.center = {0.5, 1.8, 4},
		.axis = vec3_normalize(vec3_create(1, 0, 0)),
		.radius = 0.2,
		.height = 0.8,
		.material = yellow_material
	};
	scene->cylinders[2] = (t_cylinder){
		.center = {-1.8, -0.5, 6},
		.axis = vec3_normalize(vec3_create(0, 1, 0)),
		.radius = 0.15,
		.height = 0.6,
		.material = purple_material
	};
}

static void	setup_lighting_pipe(t_scene *scene)
{
	scene->ambient = (t_ambient_light){
		.intensity = 0.4,
		.color = {255, 255, 255}
	};
	scene->num_lights = 3;
	scene->lights = malloc(scene->num_lights * sizeof(t_point_light));
	scene->lights[0] = (t_point_light){
		.position = {0, 0, -2},
		.intensity = 1.0,
		.color = {255, 255, 255}
	};
	scene->lights[1] = (t_point_light){
		.position = {2, 2, 8},
		.intensity = 0.8,
		.color = {255, 255, 255}
	};
	scene->lights[2] = (t_point_light){
		.position = {-2, -2, 12},
		.intensity = 0.6,
		.color = {255, 200, 200}
	};
}

void	setup_pipe_scene(t_scene *scene)
{
	if (!scene)
		return ;
	setup_camera_pipe(scene);
	setup_spheres_pipe(scene);
	setup_cylinders_pipe(scene);
	scene->num_planes = 0;
	scene->planes = NULL;
	setup_lighting_pipe(scene);
}
