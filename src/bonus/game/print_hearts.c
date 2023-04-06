/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_hearts.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlanza <jlanza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 16:20:17 by mbocquel          #+#    #+#             */
/*   Updated: 2023/04/06 05:47:00 by jlanza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	init_life(t_param *prm)
{
	import_img(prm, &(prm->img_heart), "./img/heart.xpm");
	prm->n_life = LIFE_NUMBER;
}

void	print_single_heart(t_param *prm, int x, int y)
{
	t_point	p;

	p.y = y;
	while (p.y < prm->img_heart.height + y)
	{
		p.x = x;
		while (p.x < prm->img_heart.width + x)
		{
			p.color = get_color(&(prm->img_heart), p.x - x, p.y - y);
			pixel_put_img(&(prm->layer.front), p);
			(p.x)++;
		}
		(p.y)++;
	}
}

void	print_hearts(t_param *prm)
{
	int		i;
	t_point	p;

	i = 0;
	while (i < prm->n_life)
	{
		p.x = 40 + i * (5 + prm->img_heart.width);
		p.y = 30;
		print_single_heart(prm, p.x, p.y);
		i++;
	}
}
