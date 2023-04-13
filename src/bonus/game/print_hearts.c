/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_hearts.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlanza <jlanza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 16:20:17 by mbocquel          #+#    #+#             */
/*   Updated: 2023/04/13 11:32:07 by jlanza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	init_life(t_param *prm)
{
	import_img(prm, &(prm->health_bar[0]), "./img/health0.xpm");
	import_img(prm, &(prm->health_bar[1]), "./img/health1bis.xpm");
	import_img(prm, &(prm->health_bar[2]), "./img/health2.xpm");
	import_img(prm, &(prm->health_bar[3]), "./img/health3.xpm");
	import_img(prm, &(prm->health_bar[4]), "./img/health4.xpm");
	prm->n_life = LIFE_NUMBER;
}

void	print_health_bar(t_param *prm, int x, int y)
{
	t_point	p;

	p.y = y;
	while (p.y < prm->health_bar[prm->n_life].height + y)
	{
		p.x = x;
		while (p.x < prm->health_bar[prm->n_life].width + x)
		{
			if (prm->n_life == 1 && prm->frame % 10 < 4)
				p.color = get_color(&(prm->health_bar[0]), p.x - x, p.y - y);
			else
				p.color = get_color(&(prm->health_bar[prm->n_life]),
						p.x - x, p.y - y);
			pixel_put_img(&(prm->layer.front), p);
			(p.x)++;
		}
		(p.y)++;
	}
}
