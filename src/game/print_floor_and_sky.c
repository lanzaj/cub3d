/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_floor_and_sky.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlanza <jlanza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 17:56:04 by jlanza            #+#    #+#             */
/*   Updated: 2023/04/06 02:41:16 by jlanza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	get_distance_int(int x1, int y1, int x2, int y2)
{
	return (sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2)));
}

void	print_floor_and_sky(t_param *prm, int sky, int floor)
{
	int		y;
	int		x;
	t_point	p;

	y = 0;
	while (y < prm->height)
	{
		x = 0;
		while (x < prm->width)
		{
			p.x = x;
			p.y = y;
			if (y < prm->height / 2)
				p.color = darken_color_floor(sky,
						get_distance_int(x, y, prm->width / 2,
							-3 * prm->height));
			else
				p.color = darken_color_floor(floor,
						get_distance_int(x, y, prm->width / 2,
							prm->height * 4));
			pixel_put_img(&prm->layer.back, p);
			x++;
		}
		y++;
	}
}
