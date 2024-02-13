/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_minimap.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlanza <jlanza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 18:34:55 by mbocquel          #+#    #+#             */
/*   Updated: 2023/04/08 13:16:59 by jlanza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	initiate_img_minimap(t_param *prm)
{
	t_point	p;
	t_point	middle;

	prm->mm_res = 10;
	prm->mini_map.width = 150;
	prm->mini_map.height = 150;
	p.x = prm->mini_map.width / 2;
	p.y = 0;
	middle.x = prm->mini_map.width / 2;
	middle.y = prm->mini_map.height / 2;
	prm->mm_ray = get_distance_point(p, middle);
	import_img(prm, &(prm->mm_window), "./img/hublot3.xpm");
	prm->print_minimap = TRUE;
}

void	init_print_mimimap(t_param *prm, t_point *p,
	t_point *middle, t_coord *new_orig)
{
	middle->x = prm->mini_map.width / 2;
	middle->y = prm->mini_map.height / 2;
	new_orig->x = prm->pos_player.x
		- (double)(prm->mini_map.width / 2) / prm->mm_res;
	new_orig->y = prm->pos_player.y
		- (double)(prm->mini_map.height / 2) / prm->mm_res;
	p->x = -1;
}

void	print_minimap(t_param *prm)
{
	t_point	p;
	t_point	middle;
	t_coord	new_orig;
	t_coord	coord;

	init_print_mimimap(prm, &p, &middle, &new_orig);
	while (++p.x < prm->mini_map.width)
	{
		p.y = -1;
		while (++p.y < prm->mini_map.height)
		{
			coord.x = new_orig.x + (double)p.x / prm->mm_res;
			coord.y = new_orig.y + (double)p.y / prm->mm_res;
			if (get_distance_point(p, middle) < prm->mm_ray - 3)
			{
				if (mm_is_wall_or_out(prm, coord))
					put_px_minimap(prm, p, 0x0c0c0c);
				else if (mm_is_door(prm, coord))
					put_px_minimap(prm, p, 0x9f7315);
				else
					put_px_minimap(prm, p, 0x3e3c3c);
			}
		}
	}
	print_player(prm);
}

void	print_player(t_param *prm)
{
	t_point	del;
	t_point	p;
	int		size;

	p.x = prm->mini_map.width / 2;
	p.y = prm->mini_map.height / 2;
	p.color = 0xcccccc;
	size = 1;
	del.x = p.x - size;
	while (del.x <= p.x + size)
	{
		del.y = p.y - size;
		while (del.y <= p.y + size)
		{
			if (del.x >= 0 && del.x < prm->mini_map.width && del.y >= 0
				&& del.y < prm->mini_map.height)
				put_px_minimap(prm, del, p.color);
			del.y++;
		}
		del.x++;
	}
	print_window_minimap(prm, prm->width - 20 - prm->mini_map.width, 20);
}

/* void	print_raytracing(t_param *prm)
{
	double	ray_ang;
	int		color;

	color = create_trgb(0, 0, 0, 255);
	ray_ang = prm->view_ang - 30 * ((2 * PI) / 360);
	while (ray_ang < prm->view_ang + 30 * ((2 * PI) / 360))
	{
		put_segment_img(&(prm->mini_map),
			get_minimap_pos(prm, prm->pos_player, color),
			get_minimap_pos(prm,
				find_wall(prm, convert_angle(ray_ang)), color));
		ray_ang += (2 * PI) / 360;
	}
} */

/*
void	print_player(t_param *prm)
{
	t_point	del;
	t_point	p;
	int		size;

	p.x = prm->mini_map.width / 2;
	p.y = prm->mini_map.height / 2;
	p.color = create_trgb(0, 255, 0, 0);
	size = 4;
	del.x = p.x - size;
	del.y = p.y - size;
	while (del.x <= p.x + size)
	{
		if (del.x >= 0 && del.x < prm->mini_map.width && p.y >= 0
			&& p.y < prm->mini_map.height)
			my_mlx_pixel_put(&(prm->layer.front), prm->width - 20
				- prm->mini_map.width + del.x, 20 + p.y, p.color);
		del.x++;
	}
	while (del.y <= p.y + size)
	{
		if (del.x >= 0 && del.x < prm->mini_map.width && p.y >= 0
			&& p.y < prm->mini_map.height)
			my_mlx_pixel_put(&(prm->layer.front), prm->width - 20
				- prm->mini_map.width + p.x, 20 + del.y, p.color);
		del.y++;
	}
}*/

/*void	print_player(t_param *prm)
{
	t_point	del;
	t_point	p;

	p = get_minimap_pos(prm, prm->pos_player, create_trgb(0, 255, 0, 0));
	del.x = p.x - 2;
	while (del.x <= p.x + 2)
	{
		del.y = p.y - 2;
		while (del.y <= p.y + 2)
		{
			if (del.x >= 0 && del.x < prm->mini_map.width && del.y >= 0
				&& del.y < prm->mini_map.height)
				my_mlx_pixel_put(&(prm->mini_map), del.x, del.y, p.color);
			del.y++;
		}
		del.x++;
	}
	put_segment_img(&(prm->mini_map), p,
		get_minimap_pos(prm, sum_vect(prm->pos_player,
				prod_vect(0.7, prm->view_dir)), p.color));
}*/
