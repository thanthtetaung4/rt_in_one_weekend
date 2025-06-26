/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter_param.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoo <aoo@student.42singapore.sg>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 20:49:34 by aoo               #+#    #+#             */
/*   Updated: 2025/05/30 21:03:20 by aoo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter_param(t_list *lst, void (*f)(void *, void *), void *param)
{
	while (lst && f && param)
	{
		f(lst->data, param);
		lst = lst->next;
	}
}
