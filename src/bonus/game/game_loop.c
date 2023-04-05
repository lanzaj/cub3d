/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbocquel <mbocquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 14:02:26 by mbocquel          #+#    #+#             */
/*   Updated: 2023/04/05 14:46:42 by mbocquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

unsigned long	get_timediff_us(struct timeval t, struct timeval t0)
{
	unsigned long	ts;

	ts = (t.tv_sec - t0.tv_sec) * 1000000 + (t.tv_usec - t0.tv_usec);
	return (ts);
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
	prm->last_time = tv;
	prm->frame++;
	if ((prm->frame) > LOOP)
		prm->frame = 0;
}

int	game_loop(t_param *prm)
{
	update_frame(prm);
	move_player(prm);
	rotate_player(prm);
	find_door_to_open(prm);
	change_door_status(prm);
	print_game(prm);
	print_every_sprite(prm);
	if (prm->print_minimap)
	{
		print_minimap(prm);
		print_window_minimap(prm, prm->width - 20 - prm->mini_map.width, 20);
	}
	mlx_put_image_to_window(prm->mlx, prm->win, prm->layer.front.img, 0, 0);
	return (0);
}

/* int	game_loop(t_param *prm)
{
	t_coord	sprite;
	clock_t	start;
	clock_t	end;

	start = clock();
	update_frame(prm);
	end = clock();
	if (prm->frame % 5 == 0)
		printf("update_frame %f ms\n", ((double) (end - start))
		/ (CLOCKS_PER_SEC / 1000));

	start = clock();
	move_player(prm);
	end = clock();
	if (prm->frame % 5 == 0)
		printf("move_player %f ms\n", ((double) (end - start))
		/ (CLOCKS_PER_SEC / 1000));

	start = clock();
	rotate_player(prm);
	end = clock();
	if (prm->frame % 5 == 0)
		printf("rotate_player %f ms\n", ((double) (end - start))
		/ (CLOCKS_PER_SEC / 1000));

	start = clock();
	find_door_to_open(prm);
	end = clock();
	if (prm->frame % 5 == 0)
		printf("find_door_to_open %f ms\n", ((double) (end - start))
		/ (CLOCKS_PER_SEC / 1000));

	start = clock();
	change_door_status(prm);
	end = clock();
	if (prm->frame % 5 == 0)
		printf("change_door_status %f ms\n", ((double) (end - start))
		/ (CLOCKS_PER_SEC / 1000));
	
	start = clock();
	print_game(prm);
	end = clock();
	if (prm->frame % 5 == 0)
		printf("print_game %f ms\n", ((double) (end - start))
		/ (CLOCKS_PER_SEC / 1000));
	
	start = clock();
	sprite.x = 4.5;
	sprite.y = 4.5;
	print_sprite(prm, sprite);
	end = clock();
	if (prm->frame % 5 == 0)
		printf("print_sprite %f ms\n", ((double) (end - start))
		/ (CLOCKS_PER_SEC / 1000));
	
	start = clock();
	mlx_put_image_to_window(prm->mlx, prm->win, prm->layer.front.img, 0, 0);
	end = clock();
	if (prm->frame % 5 == 0)
		printf("mlx_put_image_to_window %f ms\n", ((double) (end - start))
		/ (CLOCKS_PER_SEC / 1000));
	
	start = clock();
	print_minimap(prm);
	end = clock();
	if (prm->frame % 5 == 0)
		printf("print_minimap %f ms\n", ((double) (end - start)) 
		/ (CLOCKS_PER_SEC / 1000));
		
	start = clock();
	mlx_put_image_to_window(prm->mlx, prm->win, prm->mini_map.img,
		prm->width - 10 - prm->mini_map.width, 10);
	end = clock();
	if (prm->frame % 5 == 0)
		printf("mlx_put_image_to_window %f ms\n------------\n\n",
		((double) (end - start)) / (CLOCKS_PER_SEC / 1000));
		
	return (0);
}
*/