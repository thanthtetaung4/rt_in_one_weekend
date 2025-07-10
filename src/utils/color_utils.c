/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taung <taung@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 17:44:35 by taung             #+#    #+#             */
/*   Updated: 2025/07/10 18:11:05 by taung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/rt.h"

void	rgbthex(t_rgb color, int *hex_color)
{
	*hex_color = ((int)color.x << 16) | ((int)color.y << 8) | (int)color.z;
}

t_color	color_multiply(t_color a, t_color b)
{
	t_color	result;

	result.r = (a.r * b.r) / 255;
	result.g = (a.g * b.g) / 255;
	result.b = (a.b * b.b) / 255;
	return (result);
}

t_color	color_scale(t_color color, double factor)
{
	t_color	result;

	result.r = (int)(color.r * factor);
	result.g = (int)(color.g * factor);
	result.b = (int)(color.b * factor);
	return (result);
}

t_color	color_add(t_color a, t_color b)
{
	t_color	result;

	result.r = a.r + b.r;
	result.g = a.g + b.g;
	result.b = a.b + b.b;
	return (result);
}

t_color	color_clamp(t_color color)
{
	t_color	result;

	if (color.r > 255)
		result.r = 255;
	else if (color.r < 0)
		result.r = 0;
	else
		result.r = color.r;
	if (color.g > 255)
		result.g = 255;
	else if (color.g < 0)
		result.g = 0;
	else
		result.g = color.g;
	if (color.b > 255)
		result.b = 255;
	else if (color.b < 0)
		result.b = 0;
	else
		result.b = color.b;
	return (result);
}
