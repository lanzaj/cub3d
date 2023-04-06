/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   impact_raycast.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlanza <jlanza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 17:57:54 by mbocquel          #+#    #+#             */
/*   Updated: 2023/04/06 04:10:10 by jlanza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	allocate_impact_tab(t_param *prm)
{
	prm->impact = ft_calloc_gc(prm, 0, prm->width + 1, sizeof(t_impact));
	if (prm->impact == NULL)
		return (1);
	return (0);
}

void	update_impact_tab(t_param *prm)
{
	int			x;
	int			dx;

	x = prm->width / 2;
	dx = 0;
	while (x - dx >= 0)
	{
		prm->impact[x - dx].ang = atan((dx * 2 * 0.5773502) / prm->width);
		prm->impact[x - dx].wall_and_door = find_wall(prm,
				convert_angle(prm->view_ang + prm->impact[x - dx].ang));
		if (has_hit_a_door(prm, prm->impact[x - dx].wall_and_door))
		{
			prm->impact[x - dx].is_door = TRUE;
			prm->impact[x - dx].id_door = find_door(prm,
					prm->impact[x - dx].wall_and_door);
			if (prm->impact[x - dx].id_door != -1)
				prm->impact[x - dx].status_door
					= prm->tab_doors[prm->impact[x - dx].id_door]->status;
			if (prm->impact[x - dx].status_door != CLOSED)
				prm->impact[x - dx].wall_only = find_wall_only(prm,
						convert_angle(prm->view_ang + prm->impact[x - dx].ang));
		}
		dx++;
	}
	update_impact_tab_part2(prm);
}

void	update_impact_tab_part2(t_param *prm)
{
	int			x;
	int			dx;

	x = prm->width / 2;
	dx = 0;
	while (x + dx < prm->width)
	{
		prm->impact[x + dx].ang = atan((dx * 2 * 0.5773502) / prm->width);
		prm->impact[x + dx].wall_and_door = find_wall(prm,
				convert_angle(prm->view_ang - prm->impact[x + dx].ang));
		if (has_hit_a_door(prm, prm->impact[x + dx].wall_and_door))
		{
			prm->impact[x + dx].is_door = TRUE;
			prm->impact[x + dx].id_door = find_door(prm,
					prm->impact[x + dx].wall_and_door);
			if (prm->impact[x + dx].id_door != -1)
				prm->impact[x + dx].status_door
					= prm->tab_doors[prm->impact[x + dx].id_door]->status;
			if (prm->impact[x + dx].status_door != CLOSED)
				prm->impact[x + dx].wall_only = find_wall_only(prm,
						convert_angle(prm->view_ang - prm->impact[x + dx].ang));
		}
		dx++;
	}
}
