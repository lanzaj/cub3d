/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlanza <jlanza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 15:16:10 by jlanza            #+#    #+#             */
/*   Updated: 2023/03/22 17:40:56 by jlanza           ###   ########.fr       */
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
	if ((initiate_mlx(&prm, 480, 480) && ft_printf_fd(2, "Error\nInitiate mlx"))
		|| parsing_map(&prm, argv[1]))
		return (ft_exit(&prm, EXIT_FAILURE));
	printf("color floor : %x\ncolor sky : %x\n", prm.map.floor_color, prm.map.ceiling_color);
	print_mapi(prm.map.map);
	initiate_img_minimap(&prm);
	print_minimap(&prm);
	init_player_pos(&prm);
	print_player(&prm);
	mlx_hook(prm.win, 17, (1L << 0), close_win, &prm);
	mlx_key_hook(prm.win, handle_key, &prm);
	mlx_loop(prm.mlx);
	return (0);
}
