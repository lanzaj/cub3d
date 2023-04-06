/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_gun.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbocquel <mbocquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 16:54:14 by mbocquel          #+#    #+#             */
/*   Updated: 2023/04/06 17:57:54 by mbocquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	init_gun(t_param *prm)
{
	import_img(prm, &(prm->gun.gun1), "./img/gun_bis.xpm");
	import_img(prm, &(prm->gun.gun2), "./img/gun_shoot_bis2.xpm");
	import_img(prm, &(prm->gun.explo[0]), "./img/Explosion0.xpm");
	import_img(prm, &(prm->gun.explo[1]), "./img/Explosion1.xpm");
	import_img(prm, &(prm->gun.explo[2]), "./img/Explosion2.xpm");
	import_img(prm, &(prm->gun.explo[3]), "./img/Explosion3.xpm");
	import_img(prm, &(prm->gun.explo[4]), "./img/Explosion4.xpm");
	import_img(prm, &(prm->gun.explo[5]), "./img/Explosion5.xpm");
	import_img(prm, &(prm->gun.explo[6]), "./img/Explosion6.xpm");
	prm->gun.select = 1;
}

static t_img	*get_gun_xpm(t_param *prm)
{
	if (prm->gun.select == 1)
		return (&(prm->gun.gun1));
	if (prm->gun.select == 2)
		return (&(prm->gun.gun2));
	return (NULL);
}

void	update_shoot(t_param *prm)
{
	if (prm->gun.shooting)
	{
		if (prm->gun.select == 1)
		{
			prm->gun.select++;
			prm->gun.frame_count = 0;
		}
		else if (prm->gun.select == 2 && prm->gun.frame_count == SHOOT_FRAME)
		{
			prm->gun.select = 1;
			prm->gun.frame_count = 0;
			prm->gun.shooting = FALSE;
		}
		else
			prm->gun.frame_count++;
	}
}

void	print_gun(t_param *prm)
{
	t_point	p;
	int		x;
	int		y;
	t_img	*xpm;

	update_shoot(prm);
	xpm = get_gun_xpm(prm);
	y = prm->height - xpm->height;
	x = prm->width / 2 - xpm->width / 2 ;
	p.y = y;
	while (p.y < xpm->height + y)
	{
		p.x = x;
		while (p.x < xpm->width + x)
		{
			p.color = get_color(xpm, p.x - x, p.y - y);
			pixel_put_img(&(prm->layer.front), p);
			(p.x)++;
		}
		(p.y)++;
	}
}
