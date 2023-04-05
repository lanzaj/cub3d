/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_minimap_window.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbocquel <mbocquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 12:58:18 by mbocquel          #+#    #+#             */
/*   Updated: 2023/04/05 13:18:39 by mbocquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

/*void	pixel_put_img(t_img *img, t_point pixel)
{
	char	*dst;

	if (!(pixel.x < 0 || pixel.x >= img->width || pixel.y < 0
			|| pixel.y >= img->height
			|| pixel.color == -1 || get_t(pixel.color) == 255))
	{
		dst = img->addr + (pixel.y * img->line_length
				+ pixel.x * (img->bits_per_pixel / 8));
		*(unsigned int *)dst = pixel.color;
	}
}
*/

void	print_window_minimap(t_param *prm, int x, int y)
{
	t_point	p;

	p.y = y;
	while (p.y < prm->mm_window.height + y)
	{
		p.x = x;
		while (p.x < prm->mm_window.width + x)
		{
			p.color = get_color(&(prm->mm_window), p.x - x, p.y - y);
			pixel_put_img(&(prm->layer.front), p);
			(p.x)++;
		}
		(p.y)++;
	}
}
