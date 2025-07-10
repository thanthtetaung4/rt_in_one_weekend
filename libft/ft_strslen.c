/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strslen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taung <taung@student.42singapore.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 15:38:11 by aoo               #+#    #+#             */
/*   Updated: 2025/07/10 14:43:51 by taung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strslen(char **strs)
{
	size_t	size;

	size = 0;
	if (!strs)
		return (-1);
	while (strs[size])
		size++;
	return (size);
}
