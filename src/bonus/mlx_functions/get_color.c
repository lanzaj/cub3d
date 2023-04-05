/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlanza <jlanza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 14:46:20 by jlanza            #+#    #+#             */
/*   Updated: 2023/04/05 19:45:04 by jlanza           ###   ########.fr       */
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

int	darken_color(int color, t_coord wall, t_coord player)
{
	unsigned int		t;
	unsigned int		r;
	unsigned int		g;
	unsigned int		b;
	double				dist;

	//return(color);
	dist = get_distance(wall, player);
	if (dist < 5)
		dist = 0;
	else
		dist = (dist - 5) * 12;
	t = get_t(color);
	r = ft_max(get_r(color) - dist, 0);
	g = ft_max(get_g(color) - dist, 0);
	b = ft_max(get_b(color) - dist, 0);
	return (create_trgb(t, r, g, b));
}

int	darken_color_floor(int color, int x)
{
	unsigned int		t;
	unsigned int		r;
	unsigned int		g;
	unsigned int		b;
	int					gradient;

	//return (color);
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
