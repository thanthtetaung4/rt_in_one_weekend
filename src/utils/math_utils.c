/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taung <taung@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 14:18:00 by taung             #+#    #+#             */
/*   Updated: 2025/07/11 14:19:29 by taung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/rt.h"

double	degrees_to_radians(double degrees)
{
	return (degrees * (PI / 180.0));
}

double	ft_fabs(double x)
{
	if (x < 0)
		return (-x);
	return (x);
}
