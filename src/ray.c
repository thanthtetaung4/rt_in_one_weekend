/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taung <taung@student.42singapore.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 17:43:46 by taung             #+#    #+#             */
/*   Updated: 2025/07/10 17:43:49 by taung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_ray	init_ray(t_vec3 origin, t_vec3 dir, double t_min, double t_max)
{
	t_ray	ray;

	ray.origin = origin;
	ray.dir = dir;
	ray.t_min = t_min;
	ray.t_max = t_max;
	return (ray);
}
