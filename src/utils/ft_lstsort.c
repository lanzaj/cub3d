/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlanza <jlanza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 15:44:51 by jlanza            #+#    #+#             */
/*   Updated: 2023/04/06 03:15:04 by jlanza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	ft_memswap(void **a, void **b)
{
	void	*tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

void	ft_lstsort(t_param *prm, t_list *lst,
	int (*fcmp)(t_param *prm, t_list *a, t_list *b))
{
	t_list		*start;
	char		not_sorted;

	not_sorted = 1;
	if (!lst)
		return ;
	start = lst;
	while (not_sorted)
	{
		not_sorted = 0;
		lst = start;
		while (lst->next)
		{
			if (fcmp(prm, lst, lst->next) > 0)
			{
				not_sorted = 1;
				ft_memswap(&(lst->content), &(lst->next->content));
			}
			lst = lst->next;
		}
	}
}

int	cmp_distance(t_param *prm, t_list *a, t_list *b)
{
	return (get_distance_square(prm->pos_player,
			((t_sprite *)a->content)->coord)
		< get_distance_square(prm->pos_player,
			((t_sprite *)b->content)->coord));
}
