/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_screen_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbocquel <mbocquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 11:19:08 by mbocquel          #+#    #+#             */
/*   Updated: 2023/04/12 11:24:36 by mbocquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	print_red(t_param *prm)
{
	int			x;
	int			y;

	y = 0;
	while (y < prm->height)
	{
		x = 0;
		while (x < prm->width)
		{
			my_mlx_pixel_put(&prm->layer.front, x, y, 0x00FF0000);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(prm->mlx, prm->win, prm->layer.front.img, 0, 0);
}

void	print_game_over(t_param *prm)
{
	static int	t0 = 1;

	if (t0 == 1)
	{
		print_red(prm);
		t0 = 0;
	}
	if (fade_to_dark(prm) < 255)
		return ;
	if (prm->frame % 40 > 20)
		mlx_put_image_to_window(prm->mlx, prm->win,
			prm->layer.lost[0].img, 0, 0);
	else
		mlx_put_image_to_window(prm->mlx, prm->win,
			prm->layer.lost[1].img, 0, 0);
}

void	print_win(t_param *prm)
{
	if (fade_to_dark(prm) < 255)
		return ;
	if (prm->frame % 40 > 20)
		mlx_put_image_to_window(prm->mlx, prm->win,
			prm->layer.win[0].img, 0, 0);
	else
		mlx_put_image_to_window(prm->mlx, prm->win,
			prm->layer.win[1].img, 0, 0);
}

void	print_start(t_param *prm)
{
	static int	starting = 0;

	if (prm->key.key_space == 1)
	{
		if (starting == 0)
			ft_memcpy(prm->layer.front.addr,
				prm->layer.start[prm->frame % 40 > 20].addr, 3686399);
		starting = 1;
	}
	if (starting == 0)
		mlx_put_image_to_window(prm->mlx, prm->win,
			prm->layer.start[prm->frame % 40 > 20].img, 0, 0);
	else
	{
		if (fade_to_dark_start_screen(prm) >= 500)
			prm->start = 1;
	}
}

void	print_pause(t_param *prm)
{
	int		x;
	int		y;

	y = 0;
	while (y < prm->height)
	{
		x = 0;
		while (x < prm->width)
		{
			my_mlx_pixel_put(&prm->layer.pause[2], x, y,
				get_grey_color(prm, &prm->layer.front, x, y));
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(prm->mlx, prm->win, prm->layer.pause[2].img, 0, 0);
}
