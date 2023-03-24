/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   import_img.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlanza <jlanza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 16:13:17 by jlanza            #+#    #+#             */
/*   Updated: 2023/03/24 14:36:15 by jlanza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	import_img(t_param *data, t_img *xpm, char *path)
{
	static int	i = 0;

	xpm->img = mlx_xpm_file_to_image(data->mlx,
			path, &(xpm->width), &(xpm->height));
	if (xpm->img == NULL)
		return (1);
	data->img_tab[i] = xpm->img;
	i++;
	xpm->addr = mlx_get_data_addr(xpm->img, &(xpm->bits_per_pixel),
			&(xpm->line_length), &(xpm->endian));
	return (0);
}
