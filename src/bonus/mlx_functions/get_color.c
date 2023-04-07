/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbocquel <mbocquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 14:46:20 by jlanza            #+#    #+#             */
/*   Updated: 2023/04/07 10:33:42 by mbocquel         ###   ########.fr       */
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

int	get_darken_color(t_img *xpm, int x, int y, double dist)
{
	int	r;
	int	g;
	int	b;
	int	color;

	if (x < 0 || x >= xpm->width || y < 0 || y >= xpm->height)
		return (-1);
	color = *(int *)(xpm->addr + (x * (xpm->bits_per_pixel / 8)
				+ y * xpm->line_length));
	if (dist < 25)
		dist = 0;
	else
		dist = dist - 25;
	r = ((unsigned char *)&color)[2] - dist;
	if (r < 0)
		r = 0;
	g = ((unsigned char *)&color)[1] - dist;
	if (g < 0)
		g = 0;
	b = ((unsigned char *)&color)[0] - dist;
	if (b < 0)
		b = 0;
	return (*(int *)(unsigned char [4]){b, g, r, ((unsigned char *)&color)[3]});
}

int	darken_color(int color, t_coord wall, t_coord player)
{
	int		r;
	int		g;
	int		b;
	double	dist;

	dist = (wall.x - player.x) * (wall.x - player.x)
		+ (wall.y - player.y) * (wall.y - player.y);
	if (dist < 25)
		dist = 0;
	else
		dist = dist - 25;
	r = ((unsigned char *)&color)[2] - dist;
	if (r < 0)
		r = 0;
	g = ((unsigned char *)&color)[1] - dist;
	if (g < 0)
		g = 0;
	b = ((unsigned char *)&color)[0] - dist;
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
