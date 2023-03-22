/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlanza <jlanza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 14:02:26 by mbocquel          #+#    #+#             */
/*   Updated: 2023/03/22 19:41:17 by jlanza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	update_frame(t_param *prm)
{
	prm->frame++;
	if ((prm->frame) > LOOP)
	prm->frame = 0;
}

int	game_loop(t_param *prm)
{
	update_frame(prm);
	move_player(prm);
	rotate_player(prm);
	print_game(prm);
	print_minimap(prm, prm->width - 10 - prm->mini_map.width, 10);
	return (0);
}


void	move_player(t_param *prm)
{
	t_coord	new_pos;
	float	speed;

	speed = 0.1;
	new_pos = prm->pos_player;
	if (prm->key.key_w != prm->key.key_s && prm->key.key_a != prm->key.key_d)
		speed = 0.707106 * speed;
	if (prm->key.key_w && !prm->key.key_s)
		new_pos = sum_vect(new_pos, prod_vect(speed, prm->view_dir));
	if (!prm->key.key_w && prm->key.key_s)
		new_pos = sum_vect(new_pos, prod_vect(-speed, prm->view_dir));
	if (prm->key.key_d && !prm->key.key_a)
		new_pos = sum_vect(new_pos, prod_vect(speed, prm->screen_dir));
	if (prm->key.key_a && !prm->key.key_d)
		new_pos = sum_vect(new_pos, prod_vect(-speed, prm->screen_dir));
	if (is_valid_move(prm, new_pos))
		prm->pos_player = new_pos;
}

void	rotate_player(t_param *prm)
{
	if (prm->key.left && !prm->key.right)
	{
		if (prm->view_ang == 2 * PI)
			prm->view_ang = 0;
		prm->view_dir = rotate((double)PI / 64, prm->view_dir);
		prm->screen_dir = rotate((double)PI / 64, prm->screen_dir);
		prm->view_ang += (double)PI / 64;
		if (prm->view_ang == 2 * PI)
			prm->view_ang = 0;
	}
	if (!prm->key.left && prm->key.right)
	{
		if (prm->view_ang == 0)
			prm->view_ang = 2 * PI;
		prm->view_dir = rotate((double)(-PI / 64), prm->view_dir);
		prm->screen_dir = rotate((double)(-PI / 64), prm->screen_dir);
		prm->view_ang -= (double)PI / 64;
		if (prm->view_ang == 0)
			prm->view_ang = 2 * PI;
	}
}
