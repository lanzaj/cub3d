/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbocquel <mbocquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 16:15:55 by mbocquel          #+#    #+#             */
/*   Updated: 2023/03/30 17:58:32 by mbocquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	initiate_img_game(t_param *prm)
{
	prm->layer.front.img = mlx_new_image(prm->mlx, prm->width,
			prm->height);
	prm->layer.front.addr = mlx_get_data_addr(prm->layer.front.img,
			&(prm->layer.front.bits_per_pixel), &(prm->layer.front.line_length),
			&(prm->layer.front.endian));
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
	int			y;
	t_px_col	col;

	init_col_px(prm, wall, ang, &col);
	y = 0;
	while (x >= 0 && x < prm->width && y < prm->height)
	{
		my_mlx_pixel_put(&(prm->layer.front), x, y,
			get_color_px(prm, col, y, wall));
		y++;
	}
}

void	print_game(t_param *prm)
{
	int			x;

	ft_memset(prm->impact, 0, prm->width * sizeof(t_impact));
	update_impact_tab(prm);
	x = 0;
	while (x < prm->width)
	{
		if (prm->impact[x].is_door == FALSE || (prm->impact[x].is_door == TRUE
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
	mlx_put_image_to_window(prm->mlx, prm->win, prm->layer.front.img, 0, 0);
}