/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlanza <jlanza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 15:16:10 by jlanza            #+#    #+#             */
/*   Updated: 2023/04/13 11:42:22 by jlanza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/cub3d.h"

int	initiate_mlx(t_param *prm, int width, int height)
{
	prm->mlx = mlx_init();
	if (prm->mlx == NULL)
		return (ft_printf_fd(2, "Error\nInit mlx"), 1);
	garbage_col(prm, 0, prm->mlx);
	prm->win = mlx_new_window(prm->mlx, width, height, "CUB3D");
	if (prm->win == NULL)
	{
		mlx_destroy_display(prm->mlx);
		ft_printf_fd(2, "Error\nCreating window");
		return (1);
	}
	prm->width = width;
	prm->height = height;
	if (import_img(prm, &prm->layer.loading, "./img/loading.xpm"))
	{
		mlx_destroy_window(prm->mlx, prm->win);
		mlx_destroy_display(prm->mlx);
		return (ft_printf_fd(2, "Error\nAssets not imported\n"));
	}
	mlx_put_image_to_window(prm->mlx, prm->win, prm->layer.loading.img, 0, 0);
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

void	print_command_list(void)
{
	ft_printf("\n ############################### - COMMANDS -\
 ###############################\n");
	ft_printf(" #\e[1;37m      ⬆                              \
                                     #\n");
	ft_printf(" #\e[0;37m     🇼                  \e[0;36m Lef\
t click \e[0mShoot      \e[0;36m  TAB \e[0mPause       \e[0m         #\n");
	ft_printf(" #\e[0;37m ⬅ 🇦 🇸 🇩  ➡     ⬅ 🖱  ➡  \e[0;36m \
Ctrl       \e[0mShoot    \e[0;36m    F \e[0m  Hide / display fps\e[0m   #\n");
	ft_printf(" #\e[0;37m      ⬇                 \e[0;36m Space\
      \e[0mOpen door   \e[0;36m M   \e[0mHide / display map\e[0m   #\n");
	ft_printf(" #   Moving        View   \e[0;36m Shift      \e[0mSprint\
      \e[0;36m ESC \e[0mExit           \e[0m      #\n");
	ft_printf(" #                                              \
                            #\n");
	ft_printf(" ###############################################\
#############################\n\n");
}

int	main(int argc, char *argv[])
{
	t_param	prm;

	if (argc != 2 && ft_printf_fd(2, "Error\nWrong number of arguments\n"))
		return (1);
	ft_memset(&prm, 0, sizeof(t_param));
	if (initiate_mlx(&prm, 1280, 720) || allocate_impact_tab(&prm))
		return (ft_exit(&prm, EXIT_FAILURE));
	initiate_img_game(&prm);
	initiate_img_minimap(&prm);
	init_life(&prm);
	init_gun(&prm);
	parsing_map(&prm, argv[1]);
	print_floor_and_sky(&prm, prm.map.ceiling_color, prm.map.floor_color);
	print_command_list();
	mlx_mouse_move(prm.mlx, prm.win, prm.width / 2, prm.height / 2);
	mlx_hook(prm.win, 17, 1L << 0, close_win, &prm);
	mlx_hook(prm.win, 2, 1L << 0, key_press, &prm);
	mlx_hook(prm.win, 3, 1L << 1, key_release, &prm);
	mlx_hook(prm.win, 9, 1L << 21, enter_window, &prm);
	mlx_hook(prm.win, 10, 1L << 21, leave_window, &prm);
	mlx_hook(prm.win, 6, 1L << 6, handle_mouse_move, &prm);
	mlx_hook(prm.win, 4, 1L << 2, handle_mouse_click, &prm);
	mlx_loop_hook(prm.mlx, game_loop, &prm);
	mlx_loop(prm.mlx);
	return (0);
}
