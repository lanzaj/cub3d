/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_a_wall.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlanza <jlanza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 15:26:31 by mbocquel          #+#    #+#             */
/*   Updated: 2023/04/06 04:36:04 by jlanza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	is_valid_coord(t_param *prm, t_coord coord)
{
	if (coord.x < 0 || coord.y < 0)
		return (0);
	if (coord.x >= prm->map.map_width)
		return (0);
	if (coord.y >= prm->map.map_height)
		return (0);
	return (1);
}

int	has_hit_a_door(t_param *prm, t_coord point)
{
	if (point.y == (int)point.y
		&& prm->map.map[(int)point.y][(int)point.x] == 'D')
		return (SOUTH_DOOR);
	if (point.y == (int)point.y
		&& (int)point.y - 1 >= 0
		&& prm->map.map[(int)point.y - 1][(int)point.x] == 'D')
		return (NORTH_DOOR);
	if (point.x == (int)point.x
		&& prm->map.map[(int)point.y][(int)point.x] == 'D')
		return (EAST_DOOR);
	if (point.x == (int)point.x
		&& (int)point.x - 1 >= 0
		&& prm->map.map[(int)point.y][(int)point.x - 1] == 'D')
		return (WEST_DOOR);
	return (0);
}

int	has_hit_a_closed_door(t_param *prm, t_coord point)
{
	if (point.y == (int)point.y
		&& prm->map.map[(int)point.y][(int)point.x] == 'D'
		&& (!prm->nbr_door_open
			|| status_door(prm, (int)point.x, (int)point.y) == CLOSED))
		return (SOUTH_DOOR);
	if (point.y == (int)point.y
		&& (int)point.y - 1 >= 0
		&& prm->map.map[(int)point.y - 1][(int)point.x] == 'D'
		&& (!prm->nbr_door_open
			|| status_door(prm, (int)point.x, (int)point.y - 1) == CLOSED))
		return (NORTH_DOOR);
	if (point.x == (int)point.x
		&& prm->map.map[(int)point.y][(int)point.x] == 'D'
		&& (!prm->nbr_door_open
			|| status_door(prm, (int)point.x, (int)point.y) == CLOSED))
		return (EAST_DOOR);
	if (point.x == (int)point.x
		&& (int)point.x - 1 >= 0
		&& prm->map.map[(int)point.y][(int)point.x - 1] == 'D'
		&& (!prm->nbr_door_open
			|| status_door(prm, (int)point.x - 1, (int)point.y) == CLOSED))
		return (WEST_DOOR);
	return (0);
}

int	has_hit_a_wall(t_param *prm, t_coord point)
{
	if (!is_valid_coord(prm, point))
		return (-1);
	if (point.y == (int)point.y
		&& ft_strchr("123456789", prm->map.map[(int)point.y][(int)point.x]))
		return (SOUTH);
	if (point.y == (int)point.y && (int)point.y - 1 >= 0
		&& ft_strchr("123456789", prm->map.map[(int)point.y - 1][(int)point.x]))
		return (NORTH);
	if (point.x == (int)point.x
		&& ft_strchr("123456789", prm->map.map[(int)point.y][(int)point.x]))
		return (EAST);
	if (point.x == (int)point.x && (int)point.x - 1 >= 0
		&& ft_strchr("123456789", prm->map.map[(int)point.y][(int)point.x - 1]))
		return (WEST);
	return (has_hit_a_closed_door(prm, point));
}

int	has_hit_a_wall_or_door(t_param *prm, t_coord point)
{
	if (has_hit_a_wall(prm, point))
		return (has_hit_a_wall(prm, point));
	if (has_hit_a_door(prm, point))
		return (has_hit_a_door(prm, point));
	return (0);
}
