/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_door.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlanza <jlanza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 19:19:52 by mbocquel          #+#    #+#             */
/*   Updated: 2023/04/06 06:05:49 by jlanza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	find_door(t_param *prm, t_coord door)
{
	t_coord	coord;

	coord = door;
	if (has_hit_a_door(prm, door) == SOUTH_DOOR)
		coord.x = (int)door.x;
	if (has_hit_a_door(prm, door) == NORTH_DOOR)
	{
		coord.y = door.y - 1;
		coord.x = (int)door.x;
	}
	if (has_hit_a_door(prm, door) == EAST_DOOR)
		coord.y = (int)door.y;
	if (has_hit_a_door(prm, door) == WEST_DOOR)
	{
		coord.x = door.x - 1;
		coord.y = (int)door.y;
	}
	return (get_id_door(prm, (int)coord.x, (int)coord.y));
}

void	init_col_px_door(t_param *prm, t_coord door, double ang, t_px_col *col)
{
	int	id_door;

	col->px_open = 0;
	id_door = find_door(prm, door);
	col->px_wall = (prm->height * 3)
		/ (2 * ft_max_d(0.01, get_distance(prm->pos_player, door) * cos(ang)));
	if (id_door != -1)
		col->px_open = (col->px_wall * prm->tab_doors[id_door]->percent_open)
			/ 100;
	col->px_cell = (prm->height - ft_min(col->px_wall, prm->height)) / 2;
	col->px_total = 2 * col->px_cell + col->px_wall;
	col->color_cell = prm->map.ceiling_color;
	col->color_floor = prm->map.floor_color;
	col->ofset = (ft_max(0, (col->px_total - prm->height) / 2));
}

void	print_door_slice(t_param *prm, int x, t_coord door, double ang)
{
	int			y;
	t_px_col	col;
	int			color;

	init_col_px_door(prm, door, ang, &col);
	y = 0;
	while (x > 0 && x < prm->width && y < prm->height)
	{
		color = get_color_px_door(prm, col, y, door);
		if (color != -1)
			my_mlx_pixel_put(&(prm->layer.front), x, y, color);
		y++;
	}
}
