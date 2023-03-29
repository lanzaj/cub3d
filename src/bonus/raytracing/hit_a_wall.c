/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_a_wall.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbocquel <mbocquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 15:26:31 by mbocquel          #+#    #+#             */
/*   Updated: 2023/03/29 18:58:49 by mbocquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	is_valid_coord(t_param *prm, t_coord coord)
{
	if (coord.x < 0 || coord.y < 0)
		return (0);
	if (coord.x > prm->map.map_width - 1)
		return (0);
	if (coord.y > prm->map.map_height - 1)
		return (0);
	return (1);
}

int	has_hit_a_door(t_param *prm, t_coord point)
{
	if (point.y == (int)point.y
		&& prm->map.map[(int)point.y][(int)point.x] == 'D'
		&& status_door(prm, (int)point.x, (int)point.y) != OPENED)
		return (SOUTH_DOOR);
	if (point.y == (int)point.y
		&& (int)point.y - 1 >= 0
		&& prm->map.map[(int)point.y - 1][(int)point.x] == 'D'
		&& status_door(prm, (int)point.x, (int)point.y - 1) != OPENED)
		return (NORTH_DOOR);
	if (point.x == (int)point.x
		&& prm->map.map[(int)point.y][(int)point.x] == 'D'
		&& status_door(prm, (int)point.x, (int)point.y) != OPENED)
		return (EAST_DOOR);
	if (point.x == (int)point.x
		&& (int)point.x - 1 >= 0
		&& prm->map.map[(int)point.y][(int)point.x - 1] == 'D'
		&& status_door(prm, (int)point.x - 1, (int)point.y) != OPENED)
		return (WEST_DOOR);
	return (0);
}

int	has_hit_a_wall(t_param *prm, t_coord point)
{
	if (!is_valid_coord(prm, point))
		return (-1);
	if (point.y == (int)point.y
		&& prm->map.map[(int)point.y][(int)point.x] == '1')
		return (SOUTH);
	if (point.y == (int)point.y
		&& ((int)point.y - 1 >= 0
			&& prm->map.map[(int)point.y - 1][(int)point.x] == '1'))
		return (NORTH);
	if (point.x == (int)point.x
		&& prm->map.map[(int)point.y][(int)point.x] == '1')
		return (EAST);
	if (point.x == (int)point.x
		&& ((int)point.x - 1 >= 0
			&& prm->map.map[(int)point.y][(int)point.x - 1] == '1'))
		return (WEST);
	return (0);
}

int	has_hit_a_wall_or_door(t_param *prm, t_coord point)
{
	if (has_hit_a_wall(prm, point))
		return (has_hit_a_wall(prm, point));
	if (has_hit_a_door(prm, point))
		return (has_hit_a_door(prm, point));
	return (0);
}
