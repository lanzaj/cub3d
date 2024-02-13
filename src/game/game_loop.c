/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbocquel <mbocquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 14:02:26 by mbocquel          #+#    #+#             */
/*   Updated: 2023/04/12 11:21:32 by mbocquel         ###   ########.fr       */
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
