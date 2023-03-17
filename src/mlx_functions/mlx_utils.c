/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_put_pixel.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbocquel <mbocquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 10:27:16 by mbocquel          #+#    #+#             */
/*   Updated: 2023/03/17 12:06:47 by mbocquel         ###   ########.fr       */
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
