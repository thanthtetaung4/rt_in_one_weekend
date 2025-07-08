/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taung <taung@student.42singapore.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 03:32:11 by taung             #+#    #+#             */
/*   Updated: 2025/07/09 03:32:23 by taung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_H
# define RAY_H

# include "rt.h"

typedef struct s_ray
{
	t_vec3	origin;
	t_vec3	direction;
}			t_ray;

#endif
