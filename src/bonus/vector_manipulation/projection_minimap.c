/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection_minimap.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbocquel <mbocquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 10:59:37 by mbocquel          #+#    #+#             */
/*   Updated: 2023/03/21 16:00:39 by mbocquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

t_point	get_minimap_pos(t_param *prm, t_coord coord, int color)
{
	t_point	proj;

	proj.x = coord.x * prm->mm_res_x;
	proj.y = coord.y * prm->mm_res_y;
	proj.color = color;
	return (proj);
}

double	convert_angle(double angle)
{
	if (angle < 0)
		return (convert_angle(2 * PI + angle));
	else if (angle >= 2 * PI)
		return (convert_angle(angle - 2 * PI));
	else
		return (angle);
}
