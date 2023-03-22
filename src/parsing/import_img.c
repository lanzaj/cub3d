/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   import_img.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlanza <jlanza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 16:13:17 by jlanza            #+#    #+#             */
/*   Updated: 2023/03/22 15:40:25 by jlanza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	import_img(t_param *prm, t_img *xpm, char *path)
{
	xpm->img = mlx_xpm_file_to_image(prm->mlx,
			path, &(xpm->width), &(xpm->height));
	if (xpm->img == NULL)
	{
		return (1);
	}
	xpm->addr = mlx_get_data_addr(xpm->img, &(xpm->bits_per_pixel),
			&(xpm->line_length), &(xpm->endian));
	return (0);
}
