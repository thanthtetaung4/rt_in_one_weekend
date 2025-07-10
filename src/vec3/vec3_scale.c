/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_scale.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taung <taung@student.42singapore.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 17:43:13 by taung             #+#    #+#             */
/*   Updated: 2025/07/10 17:43:16 by taung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec3.h"

t_vec3	vec3_scale(t_vec3 v, double s)
{
	return (vec3_create(v.x * s, v.y * s, v.z * s));
}

t_vec3	vec3_div(t_vec3 v, double s)
{
	return (vec3_create(v.x / s, v.y / s, v.z / s));
}

double	vec3_length_squared(t_vec3 v)
{
	return (v.x * v.x + v.y * v.y + v.z * v.z);
}

double	vec3_length(t_vec3 v)
{
	return (sqrt(vec3_length_squared(v)));
}

t_vec3	vec3_normalize(t_vec3 v)
{
	double	len;

	len = sqrt(vec3_dot(v, v));
	return (vec3_div(v, len));
}
