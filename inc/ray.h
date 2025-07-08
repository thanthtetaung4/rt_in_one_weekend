/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoo <aoo@student.42singapore.sg>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 03:32:11 by taung             #+#    #+#             */
/*   Updated: 2025/07/09 06:51:16 by aoo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_H
# define RAY_H

# include "rt.h"

typedef struct s_ray
{
	t_vec3	origin;
	t_vec3	dir;
	double	t_min;
	double	t_max;
}	t_ray;

t_ray	init_ray(t_vec3 origin, t_vec3 dir, double t_min, double t_max);

#endif
