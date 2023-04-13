/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlanza <jlanza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 15:16:10 by jlanza            #+#    #+#             */
/*   Updated: 2023/04/13 10:40:39 by jlanza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/cub3d.h"

/*Besoin de garbage collecter la partie parsing*/

int	initiate_mlx(t_param *prm, int width, int height)
{
	prm->mlx = mlx_init();
	if (prm->mlx == NULL)
		return (ft_printf_fd(2, "Error\nInit mlx"), 1);
	garbage_col(prm, 0, prm->mlx);
	prm->win = mlx_new_window(prm->mlx, width, height, "Cub 3D");
	if (prm->win == NULL)
	{
		mlx_destroy_display(prm->mlx);
		ft_printf_fd(2, "Error\nCreating window");
		return (1);
	}
	prm->width = width;
	prm->height = height;
	return (0);
}

void	print_mapi(char **map)
{
	int	i;

	i = 0;
	while (map[i])
	{
		ft_putendl_fd(map[i], 1);
		i++;
	}
}

int	main(int argc, char *argv[])
{
	t_param	prm;

	if (argc != 2 && ft_printf_fd(2, "Error: wrong number of arguments\n"))
		return (1);
	ft_memset(&prm, 0, sizeof(t_param));
	if (initiate_mlx(&prm, 1280, 720))
		return (ft_exit(&prm, EXIT_FAILURE));
	parsing_map(&prm, argv[1]);
	initiate_img_game(&prm);
	mlx_hook(prm.win, 17, 1L << 0, close_win, &prm);
	mlx_hook(prm.win, 2, 1L << 0, key_press, &prm);
	mlx_hook(prm.win, 3, 1L << 1, key_release, &prm);
	mlx_loop_hook(prm.mlx, game_loop, &prm);
	mlx_loop(prm.mlx);
	return (0);
}
