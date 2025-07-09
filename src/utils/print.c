# include "rt.h"

void	print_xyz(t_vec3 origin)
{
	printf("xyz - [%f, %f, %f]", origin.x, origin.y, origin.z);
}

void	print_rgb(t_color color)
{
	printf("rgb - [%d, %d, %d]", color.r, color.g, color.b);
}

void	print_mat(t_material mat)
{
	printf("material:\n");
	printf("\tambient: %f\n", mat.ambient);
	printf("\tdiffuse: %f\n", mat.diffuse);
	printf("\tspecular: %f\n", mat.specular);
	printf("\tshininess: %f\n", mat.shininess);
}

void	print_pl(t_plane *planes, int num_planes)
{
	int	i;

	i = 0;
	while (i < num_planes)
	{
		printf("plane : ");
		print_xyz(planes[i].point);
		printf(", ");
		print_xyz(planes[i].normal);
		printf(", ");
		print_rgb(planes[i].material.color);
		printf("\n");
		print_mat(planes[i].material);
		i++;
	}
}


void	print_sp(t_sphere *spheres, int sp_count)
{
	int	i;

	i = 0;
	while (i < sp_count)
	{
		printf("sphere : ");
		print_xyz(spheres[i].center);
		printf(", radius - %f, ", spheres[i].radius);
		print_rgb(spheres[i].material.color);
		print_mat(spheres[i].material);
		printf("\n");
		i++;
	}
}

void	print_cy(t_cylinder *cylinders, int num_cylinders)
{
	int	i;

	i = 0;
	while (i < num_cylinders)
	{
		printf("cylinder : ");
		print_xyz(cylinders[i].center);
		printf(", ");
		print_xyz(cylinders[i].axis);
		printf(", radius - %f, height - %f, ", cylinders[i].radius,
				cylinders[i].height);
		print_rgb(cylinders[i].material.color);
		print_mat(cylinders[i].material);
		printf("\n");
		i++;
	}
}

void	print_l(t_point_light *lights, int num_lights)
{
	int	i;

	i = 0;
	while (i < num_lights)
	{
		printf("light : ");
		print_xyz(lights[i].position);
		printf(", intensity - %f, ", lights[i].intensity);
		print_rgb(lights[i].color);
		printf("\n");
		i++;
	}
}

void	print_ambient(t_ambient_light amb)
{
	printf("ambient : ratio - %f, ", amb.intensity);
	print_rgb(amb.color);
	printf("\n");
}

int	print_2d_array(char **arr)
{
	int i = 0;
	while (arr && arr[i])
	{
		printf("\t%s\n", arr[i]);
		i++;
	}
	return (1);
}

void	print_camera(t_camera camera)
{
	printf("camera : ");
	print_xyz(camera.P);
	printf(", ");
	print_xyz(camera.D);
	printf(", fov - %f\n", camera.fov);
}

int	print_data(t_data data)
{
	print_ambient(data.scene->ambient);
	print_camera(data.scene->camera);
	print_l(data.scene->lights, data.scene->num_lights);
	print_sp(data.scene->spheres, data.scene->num_spheres);
	print_cy(data.scene->cylinders, data.scene->num_cylinders);
	print_pl(data.scene->planes, data.scene->num_planes);
	return (10);
}
