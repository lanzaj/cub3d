/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_close.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlanza <jlanza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 16:39:32 by mbocquel          #+#    #+#             */
/*   Updated: 2023/04/06 03:49:23 by jlanza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	change_state_opening(t_param *prm, int id)
{
	(prm->tab_doors[id])->percent_open += SPEED_MOVE_DOOR;
	if ((prm->tab_doors[id])->percent_open == 100)
		(prm->tab_doors[id])->status = OPENED;
}

static void	change_state_closing(t_param *prm, int id)
{
	(prm->tab_doors[id])->percent_open -= SPEED_MOVE_DOOR;
	if ((prm->tab_doors[id])->percent_open == 0)
	{
		(prm->tab_doors[id])->status = CLOSED;
		prm->nbr_door_open--;
	}
}

int	ok_to_close_door(t_param *prm, int id)
{
	t_coord	coord_door;

	coord_door.x = (double)(prm->tab_doors[id])->x + 0.5;
	coord_door.y = (double)(prm->tab_doors[id])->y + 0.5;
	if (get_distance_square(coord_door, prm->pos_player)
		< DIST_DOOR * DIST_DOOR)
		return (0);
	return (1);
}

static void	change_state_open(t_param *prm, int id)
{
	(prm->tab_doors[id])->count_open++;
	if ((prm->tab_doors[id])->count_open >= TIME_CLOSE_DOOR
		&& ok_to_close_door(prm, id))
	{
		(prm->tab_doors[id])->status = CLOSING;
		(prm->tab_doors[id])->count_open = 0;
	}
}

void	change_door_status(t_param *prm)
{
	int	id;

	id = 0;
	while (prm->tab_doors[id])
	{
		if ((prm->tab_doors[id])->status == OPENING)
			change_state_opening(prm, id);
		if ((prm->tab_doors[id])->status == CLOSING)
			change_state_closing(prm, id);
		if ((prm->tab_doors[id])->status == OPENED)
			change_state_open(prm, id);
		id++;
	}
}
