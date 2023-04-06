/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_doors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlanza <jlanza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 15:42:20 by mbocquel          #+#    #+#             */
/*   Updated: 2023/04/06 04:35:09 by jlanza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static int	get_nb_doors(t_param *prm)
{
	int	x;
	int	y;
	int	count;

	y = 0;
	count = 0;
	while (prm->map.map[y])
	{
		x = 0;
		while (prm->map.map[y][x])
		{
			if (prm->map.map[y][x] == 'D')
				count++;
			x++;
		}
		y++;
	}
	return (count);
}

static int	init_door(t_param *prm, int x, int y, int n_door)
{
	prm->tab_doors[n_door] = ft_calloc_gc(prm, 0, 1, sizeof(t_door));
	if (prm->tab_doors[n_door] == NULL)
		return (1);
	(prm->tab_doors[n_door])->x = x;
	(prm->tab_doors[n_door])->y = y;
	return (0);
}

int	get_id_door(t_param *prm, int x, int y)
{
	int	i;

	i = 0;
	while ((prm->tab_doors)[i] != NULL)
	{
		if ((prm->tab_doors)[i]->x == x && (prm->tab_doors)[i]->y == y)
			return (i);
		i++;
	}
	return (-1);
}

int	init_doors_tab(t_param *prm)
{
	int	x;
	int	y;
	int	n_door;

	y = -1;
	n_door = 0;
	prm->tab_doors = ft_calloc_gc(prm, 0,
			get_nb_doors(prm) + 1, sizeof(t_door *));
	if (prm->tab_doors == NULL)
		return (1);
	while (prm->map.map[++y])
	{
		x = -1;
		while (prm->map.map[y][++x])
		{
			if (prm->map.map[y][x] == 'D')
			{
				if (init_door(prm, x, y, n_door))
					return (1);
				n_door++;
			}
		}
	}
	return (0);
}

t_door_status	status_door(t_param *prm, int x, int y)
{
	int	id;

	id = get_id_door(prm, x, y);
	if (id == -1)
		return (CLOSED);
	return ((prm->tab_doors[id])->status);
}
