/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_screen_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbocquel <mbocquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 11:20:43 by mbocquel          #+#    #+#             */
/*   Updated: 2023/04/12 11:21:23 by mbocquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	print_special_screen(t_param *prm)
{
	if (prm->start == 0)
		print_start(prm);
	else if (prm->n_life <= 0)
		print_game_over(prm);
	else if (prm->nbr_enemies <= 0)
		print_win(prm);
	else if (!prm->in_focus)
		print_pause(prm);
}

void	update_red_color(t_param *prm)
{
	static int	last_health = LIFE_NUMBER;
	int			*red_color;

	red_color = get_red_color();
	if (last_health != prm->n_life)
	{
		if (last_health > prm->n_life)
			*red_color = 255;
		last_health = prm->n_life;
	}
	else
	{
		if (*red_color > 0)
			*red_color -= 70;
	}
	if (*red_color < 0)
		*red_color = 0;
}

int	fade_to_dark(t_param *prm)
{
	int			x;
	int			y;
	static int	fade = 0;

	y = 0;
	while (fade < 255 && y < prm->height)
	{
		x = 0;
		while (x < prm->width)
		{
			my_mlx_pixel_put(&prm->layer.front, x, y,
				get_fade_color(&prm->layer.front, x, y));
			x++;
		}
		y++;
	}
	if (fade < 255)
	{
		mlx_put_image_to_window(prm->mlx, prm->win, prm->layer.front.img, 0, 0);
		fade += 10;
	}
	return (fade);
}

int	fade_to_dark_start_screen(t_param *prm)
{
	int			x;
	int			y;
	static int	fade = 0;

	y = 0;
	while (fade < 255 && y < prm->height)
	{
		x = 0;
		while (x < prm->width)
		{
			my_mlx_pixel_put(&prm->layer.front, x, y,
				get_fade_color(&prm->layer.front, x, y));
			x++;
		}
		y++;
	}
	if (fade < 500)
		fade += 10;
	if (fade < 255)
		mlx_put_image_to_window(prm->mlx, prm->win, prm->layer.front.img, 0, 0);
	if (fade > 255 && fade < 500)
		mlx_put_image_to_window(prm->mlx, prm->win, prm->layer.goal.img, 0, 0);
	return (fade);
}
