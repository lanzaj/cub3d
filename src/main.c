/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbocquel <mbocquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 15:16:10 by jlanza            #+#    #+#             */
/*   Updated: 2023/03/17 12:11:30 by mbocquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/cub3d.h"

int	initiate_mlx(t_param *prm, int width, int height)
{
	prm->mlx = mlx_init();
	if (prm->mlx == NULL)
		return (1);
	garbage_col(prm, 0, prm->mlx);
	prm->win = mlx_new_window(prm->mlx, width, height, "Cub 3D");
	if (prm->win == NULL)
		return (1);
	prm->width = width;
	prm->height = height;
	return (0);
}

int	main(int argc, char *argv[])
{
	t_param prm;

	if (argc != 2 && ft_printf_fd(2, "Error: wrong number of arguments"))
		return (1);
	if (initiate_mlx(&prm, 640, 480) || parsing_map(&prm, argv[1]))
		return (ft_exit(&prm, EXIT_FAILURE));

	return ('0');
}
