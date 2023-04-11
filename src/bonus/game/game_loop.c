/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlanza <jlanza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 14:02:26 by mbocquel          #+#    #+#             */
/*   Updated: 2023/04/11 18:17:44 by jlanza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

unsigned long	get_timediff_us(struct timeval t, struct timeval t0)
{
	unsigned long	ts;

	ts = (t.tv_sec - t0.tv_sec) * 1000000 + (t.tv_usec - t0.tv_usec);
	return (ts);
}

static void	print_fps(t_param *prm)
{
	struct timeval	tv;
	int				fps;
	unsigned long	time_past;

	gettimeofday(&tv, NULL);
	time_past = get_timediff_us(tv, prm->last_time);
	fps = (int)((double)1 / ((double)time_past / (double)1000000));
	if (prm->last_time.tv_sec && prm->frame % 5 == 0)
		ft_printf("\rfps : %d      \r", fps);
}

static void	update_frame(t_param *prm)
{
	struct timeval	tv;
	unsigned long	time_past;
	double			fps_wanted;
	unsigned long	time_to_wait;

	gettimeofday(&tv, NULL);
	fps_wanted = (double)FPS;
	time_to_wait = (unsigned long)(((double)1 / fps_wanted) * 1000000);
	if (prm->last_time.tv_sec)
	{
		time_past = get_timediff_us(tv, prm->last_time);
		if (time_past < time_to_wait)
			usleep(time_to_wait - time_past);
	}
	if (prm->print_fps)
		print_fps(prm);
	gettimeofday(&tv, NULL);
	prm->last_time = tv;
	prm->frame++;
	if ((prm->frame) > LOOP)
		prm->frame = 0;
}

static void	update_red_color(t_param *prm)
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

int	game_loop(t_param *prm)
{
	update_frame(prm);
	if (prm->start && prm->nbr_enemies != 0 && prm->n_life > 0 && prm->in_focus)
	{
		update_red_color(prm);
		if (!(*get_red_color()))
			ft_memcpy(prm->layer.front.addr, prm->layer.back.addr, 3686399);
		move_player(prm);
		rotate_player(prm);
		find_door_to_open(prm);
		change_door_status(prm);
		print_game(prm);
		print_every_sprite(prm);
		if (prm->print_minimap)
			print_minimap(prm);
		print_health_bar(prm, 10, 10);
		print_gun(prm);
		move_all_enemies(prm);
		mlx_put_image_to_window(prm->mlx, prm->win, prm->layer.front.img, 0, 0);
	}
	else
		print_special_screen(prm);
	return (0);
}
