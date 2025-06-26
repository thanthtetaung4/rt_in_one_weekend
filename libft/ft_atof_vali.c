/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof_vali.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoo <aoo@student.42singapore.sg>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 20:52:09 by taung             #+#    #+#             */
/*   Updated: 2025/05/14 01:36:35 by aoo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	parse_fractional_part(const char *str, int *i, float *frac)
{
	float	decimal_place;

	*frac = 0.0f;
	decimal_place = 1.0f;
	if (str[*i] == '.')
	{
		while (str[++(*i)])
		{
			if (str[*i] >= '0' && str[*i] <= '9')
			{
				*frac = *frac * 10 + (str[*i] - '0');
				decimal_place *= 10.0f;
			}
			else
				return (0);
		}
		*frac /= decimal_place;
	}
	return (1);
}

static int	skip_sign(const char *str, int *negative)
{
	int	i;

	i = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n' || str[i] == '\v'
		|| str[i] == '\f' || str[i] == '\r')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			return (*negative = 1, ++i);
		i++;
	}
	*negative = 0;
	return (i);
}

int	ft_atof_vali(const char *str, float *result)
{
	int		i;
	int		negative;
	float	frac;

	i = 0;
	*result = 0.0f;
	i = skip_sign(str, &negative);
	while (str[i] >= '0' && str[i] <= '9')
	{
		*result = *result * 10 + (str[i] - '0');
		i++;
	}
	if (!parse_fractional_part(str, &i, &frac))
		return (0);
	*result += frac;
	if (negative)
		*result = -*result;
	return (1);
}

