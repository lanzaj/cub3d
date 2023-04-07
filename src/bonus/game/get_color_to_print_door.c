/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_color_to_print_door.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlanza <jlanza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 12:12:52 by mbocquel          #+#    #+#             */
/*   Updated: 2023/04/07 16:51:25 by jlanza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

double	pos_impact_door(t_param *prm, t_coord point)
{
	if (point.y == (int)point.y
		&& prm->map.map[(int)point.y][(int)point.x] == 'D')
		return (1 - (point.x - (double)((int)point.x)));
	if (point.y == (int)point.y
		&& ((int)point.y - 1 >= 0
			&& prm->map.map[(int)point.y - 1][(int)point.x] == 'D'))
		return ((point.x - (double)((int)point.x)));
	if (point.x == (int)point.x
		&& prm->map.map[(int)point.y][(int)point.x] == 'D')
		return (point.y - (double)((int)point.y));
	if (point.x == (int)point.x
		&& ((int)point.x - 1 >= 0
			&& prm->map.map[(int)point.y][(int)point.x - 1] == 'D'))
		return (1 - (point.y - (double)((int)point.y)));
	return (0);
}

int	get_texture_px_color_door(t_param *prm, t_coord wall, double pos_y)
{
	int		px_x;
	int		px_y;
	t_img	*xpm;

	xpm = &(prm->map.door_texture);
	px_x = (int)(pos_impact_door(prm, wall) * (double)xpm->width);
	px_y = (int)(pos_y * (double)xpm->height);
	if (px_x < 0 || px_x >= xpm->width || px_y < 0 || px_y >= xpm->height)
		return (-1);
	return (darken_color(*(int *)(xpm->addr + (px_x * (xpm->bits_per_pixel / 8)
				+ px_y * xpm->line_length)), wall, prm->pos_player));
}

int	get_color_px_door(t_param *prm, t_px_col col, int y, t_coord door)
{
	int		y_bis;
	double	pos_v_in_wall;
	int		id_door;

	id_door = find_door(prm, door);
	y_bis = y + col.ofset + col.px_open;
	if (y + col.ofset < col.px_cell
		&& prm->tab_doors[id_door]->status != CLOSED)
		return (-1);
	if (y + col.ofset < col.px_cell
		&& prm->tab_doors[id_door]->status == CLOSED)
		return (col.color_cell);
	if (y + col.ofset > col.px_cell + col.px_wall - 1
		&& prm->tab_doors[id_door]->status != CLOSED)
		return (-1);
	if (y + col.ofset > col.px_cell + col.px_wall - 1
		&& prm->tab_doors[id_door]->status == CLOSED)
		return (col.color_floor);
	pos_v_in_wall = (double)(y_bis - col.px_cell) / (double)col.px_wall;
	return (get_texture_px_color_door(prm, door, pos_v_in_wall));
}
