/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbocquel <mbocquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 18:09:38 by mbocquel          #+#    #+#             */
/*   Updated: 2023/03/20 20:19:39 by mbocquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	ft_init_coord(t_coord *first_h, t_coord *first_v, t_coord *delt_h,
	t_coord *delt_v)
{
	ft_memset(first_h, 0, sizeof(t_coord));
	ft_memset(first_v, 0, sizeof(t_coord));
	ft_memset(delt_h, 10000, sizeof(t_coord));
	ft_memset(delt_v, 10000, sizeof(t_coord));
}

t_coord	find_wall(t_param *prm, double ray_ang)
{
	t_coord	first_h;
	t_coord	first_v;
	t_coord	delt_h;
	t_coord	delt_v;
	t_coord	wall;

	ft_init_coord(&first_h, &first_v, &delt_h, &delt_v);
	ft_memset(&wall, 0, sizeof(t_coord));
	//first horizontal
	if (ray_ang < PI && ray_ang > 0)
	{
		first_h.y = (int)(prm->pos_player.y);
		first_h.x = prm->pos_player.x
			+ ((prm->pos_player.y - first_h.y) / tan(ray_ang));
	}
	else if (ray_ang > PI && ray_ang < 2 * PI)
	{
		first_h.y = (int)(prm->pos_player.y) + 1;
		first_h.x = prm->pos_player.x
			+ ((prm->pos_player.y - first_h.y) / tan(ray_ang));
	}
	//first vertical
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
	//delta y
	if (ray_ang < PI && ray_ang > 0)
	{
		delt_h = first_h;
		while (prm->map.map[(int)delt_h.y - 1][(int)delt_h.x] == '0')
		{
			delt_h.y = delt_h.y - 1;
			delt_h.x = delt_h.x + (1 / tan(ray_ang));
		}
	}
	else if (ray_ang > PI && ray_ang < 2 * PI)
	{
		delt_h = first_h;
		while (prm->map.map[(int)delt_h.y][(int)delt_h.x] == '0')
		{
			delt_h.y = delt_h.y + 1;
			delt_h.x = delt_h.x - (1 / tan(ray_ang));
		}
	}
	//delta x
	if (ray_ang < PI / 2 || ray_ang > 3 * PI / 2)
	{
		delt_v = first_v;
		while (prm->map.map[(int)delt_v.y][(int)delt_v.x] == '0')
		{
			delt_v.x = delt_v.x + 1;
			delt_v.y = delt_v.x + tan(ray_ang);
		}
	}
	else if (ray_ang > PI / 2 && ray_ang < 3 * PI / 2)
	{
		delt_v = first_v;
		while (prm->map.map[(int)delt_v.y][(int)delt_v.x - 1] == '0')
		{
			delt_v.x = delt_v.x - 1;
			delt_v.y = delt_v.x - tan(ray_ang);
		}
	}
	/*Besoin de calculer la distance la plus courte entre le point et les deux possibles stops */
	return (delt_v);
}
