/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbocquel <mbocquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 14:46:20 by jlanza            #+#    #+#             */
/*   Updated: 2023/04/12 11:30:24 by mbocquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	get_color(t_img *xpm, int x, int y)
{
	if (x < 0 || x >= xpm->width || y < 0 || y >= xpm->height)
		return (-1);
	return (*(int *)(xpm->addr + (x * (xpm->bits_per_pixel / 8)
			+ y * xpm->line_length)));
}

int	get_fade_color(t_img *xpm, int x, int y)
{
	int	color;
	int	r;
	int	g;
	int	b;

	if (x < 0 || x >= xpm->width || y < 0 || y >= xpm->height)
		return (-1);
	color = *(int *)(xpm->addr + (x * (xpm->bits_per_pixel / 8)
				+ y * xpm->line_length));
	r = ((unsigned char *)&color)[2] - 30;
	if (r < 0)
		r = 0;
	g = ((unsigned char *)&color)[1] - 30;
	if (g < 0)
		g = 0;
	b = ((unsigned char *)&color)[0] - 30;
	if (b < 0)
		b = 0;
	return (*(int *)(unsigned char [4]){b, g, r, 0});
}

int	get_grey_color(t_param *prm, t_img *xpm, int x, int y)
{
	int	color;
	int	r;
	int	g;
	int	b;

	if (x < 0 || x >= xpm->width || y < 0 || y >= xpm->height)
		return (-1);
	if (get_t(get_color(&prm->layer.pause[prm->frame % 40 > 20], x, y)) != 255)
		return (get_color(&prm->layer.pause[prm->frame % 40 > 20], x, y));
	color = *(int *)(xpm->addr + (x * (xpm->bits_per_pixel / 8)
				+ y * xpm->line_length));
	r = ((unsigned char *)&color)[2];
	g = ((unsigned char *)&color)[1];
	b = ((unsigned char *)&color)[0];
	if (r == g && g == b)
		return (*(int *)(unsigned char [4]){b, g, r, 0});
	color = (r + g + b) / 3;
	return (*(int *)(unsigned char [4]){color, color, color, 0});
}

int	*get_red_color(void)
{
	static int	red_color = 0;

	return (&red_color);
}

int	get_darken_color(t_img *xpm, t_coord_int coord, double dist, int *red_color)
{
	int	r;
	int	g;
	int	b;
	int	color;

	color = *(int *)(xpm->addr + (coord.x * (xpm->bits_per_pixel / 8)
				+ coord.y * xpm->line_length));
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
