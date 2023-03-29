/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_first_wall_only.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbocquel <mbocquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 18:09:38 by mbocquel          #+#    #+#             */
/*   Updated: 2023/03/29 18:53:54 by mbocquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

t_coord	find_first_h_w_only(t_param *prm, double ray_ang)
{
	t_coord	first_h;

	if (ray_ang == PI / 2)
	{
		first_h.y = (int)prm->pos_player.y;
		first_h.x = prm->pos_player.x;
		return (first_h);
	}
	else if (ray_ang == 3 * PI / 2)
	{
		first_h.y = (int)prm->pos_player.y + 1;
		first_h.x = prm->pos_player.x;
		return (first_h);
	}
	return (find_first_h_part_2_w_only(prm, ray_ang));
}

t_coord	find_first_h_part_2_w_only(t_param *prm, double ray_ang)
{
	t_coord	first_h;

	if (ray_ang != PI / 2 && ray_ang > 0 && ray_ang < PI)
	{
		first_h.y = (int)(prm->pos_player.y);
		first_h.x = prm->pos_player.x
			+ ((prm->pos_player.y - first_h.y) / tan(ray_ang));
	}
	else if (ray_ang != 3 * PI / 2 && ray_ang > PI && ray_ang < 2 * PI)
	{
		first_h.y = (int)(prm->pos_player.y) + 1;
		first_h.x = prm->pos_player.x
			+ ((prm->pos_player.y - first_h.y) / tan(ray_ang));
	}
	else
	{
		first_h.x = -1;
		first_h.y = -1;
	}
	return (first_h);
}

t_coord	find_first_v_w_only(t_param *prm, double ray_ang)
{
	t_coord	first_v;

	if (ray_ang == 0)
	{
		first_v.x = (int)prm->pos_player.x + 1;
		first_v.y = prm->pos_player.y;
		return (first_v);
	}
	else if (ray_ang == PI)
	{
		first_v.x = (int)prm->pos_player.x;
		first_v.y = prm->pos_player.y;
		return (first_v);
	}
	return (find_first_v_part_2_w_only(prm, ray_ang));
}

t_coord	find_first_v_part_2_w_only(t_param *prm, double ray_ang)
{
	t_coord	first_v;

	if (ray_ang < PI / 2 || ray_ang > 3 * PI / 2)
	{
		first_v.x = (int)(prm->pos_player.x) + 1;
		first_v.y = prm->pos_player.y
			+ (prm->pos_player.x - first_v.x) * tan(ray_ang);
	}
	else if (ray_ang > PI / 2 && ray_ang < 3 * PI / 2)
	{
		first_v.x = (int)(prm->pos_player.x);
		first_v.y = prm->pos_player.y
			+ tan(ray_ang) * (prm->pos_player.x - first_v.x);
	}
	else
	{
		first_v.x = -1;
		first_v.y = -1;
	}
	return (first_v);
}
