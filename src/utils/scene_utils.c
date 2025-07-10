#include "rt.h"
#include <string.h>

t_scene	*create_scene(void)
{
	t_scene	*scene;

	scene = ft_calloc(1, sizeof(t_scene));
	if (!scene)
	{
		printf("Error: Failed to allocate scene\n");
		return (NULL);
	}
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
