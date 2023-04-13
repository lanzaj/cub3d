/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlanza <jlanza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 15:29:45 by mbocquel          #+#    #+#             */
/*   Updated: 2023/04/13 11:44:18 by jlanza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	garbage_col(t_param *prm, int id, void *ptr)
{
	t_garb	*new_garb;

	new_garb = (t_garb *)malloc(sizeof(t_garb));
	if (new_garb == NULL)
		return (1);
	new_garb->ptr = ptr;
	new_garb->id = id;
	new_garb->next = NULL;
	if (prm->garb == NULL)
		prm->garb = new_garb;
	else
	{
		new_garb->next = prm->garb;
		prm->garb = new_garb;
	}
	return (0);
}

void	empty_all_garbage(t_param *prm)
{
	t_garb	*elem_garb;
	t_garb	*temp;

	elem_garb = prm->garb;
	while (elem_garb)
	{
		temp = elem_garb;
		free(elem_garb->ptr);
		elem_garb = temp->next;
		free(temp);
	}
	prm->garb = NULL;
}

void	empty_garbage(t_param *prm, int id)
{
	t_garb	*elem;
	t_garb	*temp;
	t_garb	*previous;

	previous = NULL;
	elem = prm->garb;
	if (id == -1)
		empty_all_garbage(prm);
	while (id != -1 && elem)
	{
		if (elem->id != id)
		{
			previous = elem;
			elem = elem->next;
			continue ;
		}
		if (previous)
			previous->next = elem->next;
		else
			prm->garb = elem->next;
		temp = elem;
		elem = elem->next;
		free(temp->ptr);
		free(temp);
	}
}

void	print_garbage(t_param *prm)
{
	t_garb	*elem;

	elem = prm->garb;
	if (elem == NULL)
		ft_printf_fd(2, "Garbage empty...\n");
	while (elem)
	{
		ft_printf("%d - %p\n", elem->id, elem->ptr);
		elem = elem->next;
	}
}

void	remove_from_garb(t_param *prm, void *ptr)
{
	t_garb	*elem;
	t_garb	*previous;

	previous = NULL;
	elem = prm->garb;
	while (elem && elem->ptr != ptr)
	{
		previous = elem;
		elem = elem->next;
	}
	if (elem)
	{
		if (previous)
			previous->next = elem->next;
		else
			prm->garb = elem->next;
		free(elem->ptr);
		free(elem);
	}
}
