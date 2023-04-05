/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_minimap_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbocquel <mbocquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 11:21:39 by mbocquel          #+#    #+#             */
/*   Updated: 2023/04/05 18:39:29 by mbocquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	put_px_minimap(t_param *prm, t_point p, int color)
{
	my_mlx_pixel_put(&(prm->layer.front), prm->width
		- 20 - prm->mini_map.width + p.x, 20 + p.y, color);
}

t_bool	mm_is_wall_or_out(t_param *prm, t_coord coord)
{
	if (!is_valid_coord(prm, coord) || ft_strchr("123456789M",
			prm->map.map[(int)coord.y][(int)coord.x]))
		return (TRUE);
	return (FALSE);
}

t_bool	mm_is_door(t_param *prm, t_coord coord)
{
	if (is_valid_coord(prm, coord)
		&& prm->map.map[(int)coord.y][(int)coord.x] == 'D')
		return (TRUE);
	return (FALSE);
}
