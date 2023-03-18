/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbocquel <mbocquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 10:27:16 by mbocquel          #+#    #+#             */
/*   Updated: 2023/03/18 16:39:35 by mbocquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	ft_swap_seg(t_seg *seg, t_point *delt)
{
	ft_swap(&((*seg).start.x), &((*seg).end.x));
	ft_swap(&((*seg).start.y), &((*seg).end.y));
	ft_swap(&((*seg).start.color), &((*seg).end.color));
	(*delt).x = -(*delt).x;
	(*delt).y = -(*delt).y;
}

int	get_color_gradian(t_point p_s, t_point p_e, t_point p)
{
	int	col;
	int	dseg2;
	int	d2;
	int	e;

	e = 0;
	dseg2 = pow(p_e.y - p_s.y, 2) + pow(p_e.x - p_s.x, 2);
	d2 = pow(p.y - p_s.y, 2) + pow(p.x - p_s.x, 2);
	if (dseg2)
		e = (int)(sqrt(((float)d2 / (float)dseg2)) * 100);
	col = create_trgb(
			(e * get_t(p_e.color) + (100 - e) * get_t(p_s.color)) / 100,
			(e * get_r(p_e.color) + (100 - e) * get_r(p_s.color)) / 100,
			(e * get_g(p_e.color) + (100 - e) * get_g(p_s.color)) / 100,
			(e * get_b(p_e.color) + (100 - e) * get_b(p_s.color)) / 100);
	return (col);
}
