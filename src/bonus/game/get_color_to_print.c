/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_color_to_print.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlanza <jlanza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 12:12:52 by mbocquel          #+#    #+#             */
/*   Updated: 2023/04/04 16:23:43 by jlanza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

double	pos_impact(t_param *prm, t_coord point)
{
	if (!is_valid_coord(prm, point))
		return (-1);
	if (point.y == (int)point.y
		&& ft_strchr("123456789D", prm->map.map[(int)point.y][(int)point.x]))
		return (1 - (point.x - (double)((int)point.x)));
	if (point.y == (int)point.y && (int)point.y - 1 >= 0
		&& ft_strchr("123456789D", prm->map.map[(int)point.y - 1][(int)point.x]))
		return ((point.x - (double)((int)point.x)));
	if (point.x == (int)point.x
		&& ft_strchr("123456789D", prm->map.map[(int)point.y][(int)point.x]))
		return (point.y - (double)((int)point.y));
	if (point.x == (int)point.x && (int)point.x - 1 >= 0
		&& ft_strchr("123456789D", prm->map.map[(int)point.y][(int)point.x - 1]))
		return (1 - (point.y - (double)((int)point.y)));
	return (0);
}
/*
void	get_correct_xpm(t_param *prm, t_dir dir, t_img	*xpm)
{
	if (dir == SOUTH)
		xpm = &(prm->map.south_texture);
	else if (dir == NORTH)
		xpm = &(prm->map.north_texture);
	else if (dir == EAST)
		xpm = &(prm->map.east_texture);
	else if (dir == WEST)
		xpm = &(prm->map.west_texture);
	else if (dir == WALL_3)
		xpm = &(prm->map.wall3_texture);
	else if (dir == WALL_4)
		xpm = &(prm->map.wall4_texture);
	else if (dir == WALL_5)
		xpm = &(prm->map.wall5_texture);
	else if (dir == WALL_6)
		xpm = &(prm->map.wall6_texture);
	else if (dir == WALL_7)
		xpm = &(prm->map.wall7_texture);
	else if (dir == WALL_8)
		xpm = &(prm->map.wall8_texture);
	else if (dir == WALL_9)
		xpm = &(prm->map.wall9_texture);
	else
		xpm = &(prm->map.door_texture);
}
*/

int	get_texture_px_color(t_param *prm, t_coord wall, double pos_y)
{
	int		px_x;
	int		px_y;
	t_dir	dir;
	t_img	*xpm;

	xpm = NULL;
	dir = get_type_of_wall(prm, wall);
	if (dir == SOUTH)
		xpm = &(prm->map.south_texture);
	else if (dir == NORTH)
		xpm = &(prm->map.north_texture);
	else if (dir == EAST)
		xpm = &(prm->map.east_texture);
	else if (dir == WEST)
		xpm = &(prm->map.west_texture);
	else if (dir == WALL_3)
		xpm = &(prm->map.wall3_texture);
	else if (dir == WALL_4)
		xpm = &(prm->map.wall4_texture);
	else if (dir == WALL_5)
		xpm = &(prm->map.wall5_texture);
	else if (dir == WALL_6)
		xpm = &(prm->map.wall6_texture);
	else if (dir == WALL_7)
		xpm = &(prm->map.wall7_texture);
	else if (dir == WALL_8)
		xpm = &(prm->map.wall8_texture);
	else if (dir == WALL_9)
		xpm = &(prm->map.wall9_texture);
	else
		xpm = &(prm->map.door_texture);
	px_x = (int)(pos_impact(prm, wall) * (double)xpm->width);
	px_y = (int)(pos_y * (double)xpm->height);
	if (px_x < 0 || px_x > xpm->width || px_y < 0 || px_y > xpm->height)
		return (-1);
	return (*(int *)(xpm->addr + (px_x * (xpm->bits_per_pixel / 8)
			+ px_y * xpm->line_length)));
}

int	get_color_px(t_param *prm, t_px_col col, int y, t_coord wall)
{
	int		y_bis;
	double	pos_v_in_wall;

	y_bis = y + col.ofset;
	if (y_bis < col.px_cell)
		return (prm->map.ceiling_color);
	if (y_bis >= col.px_cell + col.px_wall)
		return (prm->map.floor_color);
	pos_v_in_wall = (double)(y_bis - col.px_cell) / (double)col.px_wall;
	return (get_texture_px_color(prm, wall, pos_v_in_wall));
}
