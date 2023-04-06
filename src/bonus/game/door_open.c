/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_open.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlanza <jlanza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 16:17:53 by mbocquel          #+#    #+#             */
/*   Updated: 2023/04/06 03:11:18 by jlanza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	find_door_to_open(t_param *prm)
{
	int		id_door;
	t_coord	coord_door;

	if (prm->key.key_space == 1)
	{
		id_door = 0;
		while (prm->tab_doors[id_door])
		{
			coord_door.x = (double)(prm->tab_doors[id_door]->x) + 0.5;
			coord_door.y = (double)(prm->tab_doors[id_door]->y) + 0.5;
			if (get_distance_square(coord_door, prm->pos_player) < 2.5 * 2.5
				&& (prm->tab_doors[id_door])->status == CLOSED)
				(prm->tab_doors[id_door])->status = OPENING;
			id_door++;
		}
	}
	prm->key.key_space = 0;
}

t_bool	all_doors_are_closed(t_param *prm)
{
	int		i;

	i = 0;
	while (prm->tab_doors[i])
	{
		if (prm->tab_doors[i]->status != CLOSED)
			return (FALSE);
		i++;
	}
	return (TRUE);
}
