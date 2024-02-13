/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_color_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbocquel <mbocquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 11:29:19 by mbocquel          #+#    #+#             */
/*   Updated: 2023/04/12 11:30:14 by mbocquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	darken_color(int color, t_coord wall, t_coord player)
{
	int		r;
	int		g;
	int		b;
	double	dist;
	int		*red_color;

	red_color = get_red_color();
	dist = (wall.x - player.x) * (wall.x - player.x)
		+ (wall.y - player.y) * (wall.y - player.y);
	if (dist < 25)
		dist = 0;
	else
		dist = dist - 25;
	r = ((unsigned char *)&color)[2] - dist + *red_color;
	if (r < 0)
		r = 0;
	if (r > 255)
		r = 255;
	g = ((unsigned char *)&color)[1] - dist - *red_color;
	if (g < 0)
		g = 0;
	b = ((unsigned char *)&color)[0] - dist - *red_color;
	if (b < 0)
		b = 0;
	return (*(int *)(unsigned char [4]){b, g, r, ((unsigned char *)&color)[3]});
}

int	darken_color_floor(int color, int x)
{
	unsigned int		t;
	unsigned int		r;
	unsigned int		g;
	unsigned int		b;
	int					gradient;

	gradient = 2420;
	if (x < gradient)
		x = 0;
	else
		x = (x - gradient) / 3;
	t = get_t(color);
	r = ft_max(get_r(color) - x, 0);
	g = ft_max(get_g(color) - x, 0);
	b = ft_max(get_b(color) - x, 0);
	return (create_trgb(t, r, g, b));
}

int	red_filter(t_param *prm, t_coord_int coord)
{
	int		r;
	int		g;
	int		b;
	int		*red_color;
	int		color;

	color = get_color(&prm->layer.back, coord.x, coord.y);
	red_color = get_red_color();
	r = ((unsigned char *)&color)[2] + *red_color;
	if (r < 0)
		r = 0;
	if (r > 255)
		r = 255;
	g = ((unsigned char *)&color)[1] - *red_color;
	if (g < 0)
		g = 0;
	b = ((unsigned char *)&color)[0] - *red_color;
	if (b < 0)
		b = 0;
	return (*(int *)(unsigned char [4]){b, g, r, ((unsigned char *)&color)[3]});
}
