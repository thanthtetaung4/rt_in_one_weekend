/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taung <taung@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 14:20:04 by taung             #+#    #+#             */
/*   Updated: 2025/07/11 14:21:36 by taung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

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
	printf(", material:\n");
	printf("\tambient: %f\n", mat.ambient);
	printf("\tdiffuse: %f\n", mat.diffuse);
	printf("\tspecular: %f\n", mat.specular);
	printf("\tshininess: %f\n", mat.shininess);
}
