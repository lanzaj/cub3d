/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel_put_img.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbocquel <mbocquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 12:57:08 by mbocquel          #+#    #+#             */
/*   Updated: 2023/04/10 14:58:57 by mbocquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	pixel_put_img(t_img *img, t_point pixel)
{
	char	*dst;

	if (!(pixel.x < 0 || pixel.x >= img->width || pixel.y < 0
			|| pixel.y >= img->height
			|| pixel.color == -1 || ((unsigned char *)&pixel.color)[3] == 255))
	{
		dst = img->addr + (pixel.y * img->line_length
				+ pixel.x * (img->bits_per_pixel / 8));
		*(unsigned int *)dst = pixel.color;
		return (1);
	}
	if (pixel.color == -1 || ((unsigned char *)&pixel.color)[3] == 255)
		return (1);
	return (0);
}
