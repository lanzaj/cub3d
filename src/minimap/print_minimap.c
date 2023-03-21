/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_minimap.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbocquel <mbocquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 18:34:55 by mbocquel          #+#    #+#             */
/*   Updated: 2023/03/21 16:06:12 by mbocquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	initiate_img_minimap(t_param *prm)
{
	prm->mini_map.width = 480;
	prm->mini_map.height = 480;
	prm->mini_map.img = mlx_new_image(prm->mlx, prm->mini_map.width,
			prm->mini_map.height);
	prm->mini_map.addr = mlx_get_data_addr(prm->mini_map.img,
			&(prm->mini_map.bits_per_pixel), &(prm->mini_map.line_length),
			&(prm->mini_map.endian));
}

void	print_mini_map_grid(t_param *prm)
{
	t_point	p;
	int		color;

	p.x = 0;
	color = create_trgb(0, 125, 125, 125);
	while (p.x < prm->mini_map.width)
	{
		p.y = -1;
		while (++(p.y) < prm->mini_map.height)
			my_mlx_pixel_put(&(prm->mini_map), p.x, p.y, color);
		p.x += prm->mm_res_x;
	}
	p.y = 0;
	while (p.y < prm->mini_map.height)
	{
		p.x = -1;
		while (++(p.x) < prm->mini_map.width)
			my_mlx_pixel_put(&(prm->mini_map), p.x, p.y, color);
		p.y += prm->mm_res_y;
	}
}

void	print_minimap(t_param *prm)
{
	t_point	p;
	int		color;

	p.x = 0;
	p.y = 0;
	color = create_trgb(0, 255, 255, 255);
	prm->mm_res_x = prm->mini_map.width / prm->map.map_width;
	prm->mm_res_y = prm->mini_map.height / prm->map.map_height;
	while (p.x < prm->mini_map.width)
	{
		p.y = 0;
		while (p.y < prm->mini_map.height)
		{
			if (prm->map.map[p.y / prm->mm_res_y][p.x / prm->mm_res_x] == '1'
				&& p.x < prm->mini_map.width && p.y < prm->mini_map.height)
				my_mlx_pixel_put(&(prm->mini_map), p.x, p.y, 0);
			else
				my_mlx_pixel_put(&(prm->mini_map), p.x, p.y, color);
			p.y++;
		}
		p.x++;
	}
	mlx_put_image_to_window(prm->mlx, prm->win, prm->mini_map.img, 0, 0);
}

void	print_player(t_param *prm)
{
	t_point	del;
	t_point	p;

	print_raytracing(prm);
	p.x = prm->pos_player.x * prm->mm_res_x;
	p.y = prm->pos_player.y * prm->mm_res_y;
	p.color = create_trgb(0, 0, 0, 255);
	del.x = p.x - 3;
	while (del.x <= p.x + 3)
	{
		del.y = p.y - 3;
		while (del.y <= p.y + 3)
		{
			if (del.x >= 0 && del.x < prm->mini_map.width && del.y >= 0
				&& del.y < prm->mini_map.height)
				my_mlx_pixel_put(&(prm->mini_map), del.x, del.y, p.color);
			del.y++;
		}
		del.x++;
	}
	mlx_put_image_to_window(prm->mlx, prm->win, prm->mini_map.img, 0, 0);
}

void	print_raytracing(t_param *prm)
{
	double	ray_ang;
	int		color;

	color = create_trgb(0, 255, 0, 0);
	ray_ang = prm->view_ang - 30 * ((2 * PI) / 360);
	while (ray_ang < prm->view_ang + 30 * ((2 * PI) / 360))
	{
		put_segment_img(&(prm->mini_map),
			get_minimap_pos(prm, prm->pos_player, color),
			get_minimap_pos(prm,
				find_wall(prm, convert_angle(ray_ang)), color));
		ray_ang += (2 * PI) / 360;
	}
}
