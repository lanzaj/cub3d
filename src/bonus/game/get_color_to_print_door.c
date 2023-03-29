/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_color_to_print_door.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbocquel <mbocquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 12:12:52 by mbocquel          #+#    #+#             */
/*   Updated: 2023/03/29 20:36:03 by mbocquel         ###   ########.fr       */
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
	t_dir	dir;
	t_img	*xpm;

	dir = has_hit_a_wall_or_door(prm, wall);
	if (dir == SOUTH)
		xpm = &(prm->map.south_texture);
	else if (dir == NORTH)
		xpm = &(prm->map.north_texture);
	else if (dir == EAST)
		xpm = &(prm->map.east_texture);
	else if (dir == WEST)
		xpm = &(prm->map.west_texture);
	else
		xpm = &(prm->map.door_texture);
	px_x = (int)(pos_impact_door(prm, wall) * (double)xpm->width);
	px_y = (int)(pos_y * (double)xpm->height);
	if (px_x < 0 || px_x > xpm->width || px_y < 0 || px_y > xpm->height)
		return (-1);
	return (*(int *)(xpm->addr + (px_x * (xpm->bits_per_pixel / 8)
			+ px_y * xpm->line_length)));
}

int	get_color_px_door(t_param *prm, t_px_col col, int y, t_coord wall)
{
	int		y_bis;
	double	pos_v_in_wall;

	y_bis = y + col.ofset;
	if (y_bis < col.px_cell)
		return (-1);
	if (y_bis >= col.px_cell + col.px_wall)
		return (-1);
	pos_v_in_wall = (double)(y_bis - col.px_cell) / (double)col.px_wall;
	return (get_texture_px_color_door(prm, wall, pos_v_in_wall));
}
//Besoin de gerer l'ouverture de la porte. 