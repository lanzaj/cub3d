/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlanza <jlanza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 14:01:39 by jlanza            #+#    #+#             */
/*   Updated: 2023/01/13 16:06:24 by jlanza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	if (lst)
	{
		if (*lst)
		{
			ft_lstclear(&((*lst)->next), (*del));
			ft_lstdelone(*lst, del);
			*lst = NULL;
		}
	}
}
