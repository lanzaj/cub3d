/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   import_img.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbocquel <mbocquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 16:13:17 by jlanza            #+#    #+#             */
/*   Updated: 2023/04/12 16:04:55 by mbocquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	import_img(t_param *data, t_img *xpm, char *path)
{
	char		*new_path;
	static int	i = 0;

	new_path = trim_str(data, path);
	if (new_path == NULL)
		return (1);
	xpm->img = mlx_xpm_file_to_image(data->mlx,
			new_path, &(xpm->width), &(xpm->height));
	if (xpm->img == NULL)
		return (1);
	data->img_tab[i] = xpm->img;
	i++;
	xpm->addr = mlx_get_data_addr(xpm->img, &(xpm->bits_per_pixel),
			&(xpm->line_length), &(xpm->endian));
	return (0);
}
