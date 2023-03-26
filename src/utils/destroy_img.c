/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_img.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlanza <jlanza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 14:36:26 by jlanza            #+#    #+#             */
/*   Updated: 2023/03/26 23:14:22 by jlanza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	destroy_images(t_param *prm)
{
	int	i;

	i = 0;
	while (i < 124 && prm->img_tab[i] != 0)
	{
		mlx_destroy_image(prm->mlx, prm->img_tab[i]);
		i++;
	}
}
