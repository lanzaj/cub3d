/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlanza <jlanza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 16:15:55 by mbocquel          #+#    #+#             */
/*   Updated: 2023/04/11 15:57:12 by jlanza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	initiate_img_game(t_param *prm)
{
	prm->layer.front.img = mlx_new_image(prm->mlx, prm->width,
			prm->height);
	prm->layer.front.width = prm->width;
	prm->layer.front.height = prm->height;
	prm->layer.front.addr = mlx_get_data_addr(prm->layer.front.img,
			&(prm->layer.front.bits_per_pixel), &(prm->layer.front.line_length),
			&(prm->layer.front.endian));
	prm->layer.back.img = mlx_new_image(prm->mlx, prm->width,
			prm->height);
	prm->layer.back.width = prm->width;
	prm->layer.back.height = prm->height;
	prm->layer.back.addr = mlx_get_data_addr(prm->layer.back.img,
			&(prm->layer.back.bits_per_pixel), &(prm->layer.back.line_length),
			&(prm->layer.back.endian));
	init_tab_xpm(prm);
	import_img(prm, &prm->layer.start[0], "./img/start0.xpm");
	import_img(prm, &prm->layer.start[1], "./img/start1.xpm");
	import_img(prm, &prm->layer.lost[0], "./img/loose0.xpm");
	import_img(prm, &prm->layer.lost[1], "./img/loose1.xpm");
	import_img(prm, &prm->layer.win[0], "./img/win0.xpm");
	import_img(prm, &prm->layer.win[1], "./img/win1.xpm");
	import_img(prm, &prm->layer.pause[0], "./img/pause0.xpm");
	import_img(prm, &prm->layer.pause[1], "./img/pause1.xpm");
	import_img(prm, &prm->layer.pause[2], "./img/pause2.xpm");
	import_img(prm, &prm->layer.goal, "./img/goal.xpm");
}

void	init_col_px(t_param *prm, t_coord wall, double ang, t_px_col *col)
{
	col->px_wall = (prm->height * 3)
		/ (2 * ft_max_d(0.01, get_distance(prm->pos_player, wall) * cos(ang)));
	col->px_cell = (prm->height - ft_min(col->px_wall, prm->height)) / 2;
	col->px_total = 2 * col->px_cell + col->px_wall;
	col->color_cell = prm->map.ceiling_color;
	col->color_floor = prm->map.floor_color;
	col->ofset = (ft_max(0, (col->px_total - prm->height) / 2));
	col->px_open = 0;
}

void	print_wall_slice(t_param *prm, int x, t_coord wall, double ang)
{
	t_coord_int	coord;
	t_px_col	col;

	init_col_px(prm, wall, ang, &col);
	coord.x = x;
	coord.y = 0;
	while (x > 0 && x < prm->width && coord.y < prm->height)
	{
		my_mlx_pixel_put(&(prm->layer.front), x, coord.y,
			get_color_px(prm, col, coord, wall));
		coord.y++;
	}
}

void	print_game(t_param *prm)
{
	int	x;

	ft_memset(prm->impact, 0, prm->width * sizeof(t_impact));
	update_impact_tab(prm);
	x = 0;
	while (x < prm->width)
	{
		if (!prm->nbr_door_open || prm->impact[x].is_door == FALSE
			|| (prm->impact[x].is_door == TRUE
				&& prm->impact[x].status_door == CLOSED))
			print_wall_slice(prm, x,
				prm->impact[x].wall_and_door, prm->impact[x].ang);
		else
		{
			print_wall_slice(prm, x,
				prm->impact[x].wall_only, prm->impact[x].ang);
			if (prm->impact[x].status_door != OPENED)
				print_door_slice(prm, x,
					prm->impact[x].wall_and_door, prm->impact[x].ang);
		}
		x++;
	}
}
