/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbocquel <mbocquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 14:02:26 by mbocquel          #+#    #+#             */
/*   Updated: 2023/03/27 14:03:37 by mbocquel         ###   ########.fr       */
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

/*void	move_player(t_param *prm)
{
	float	speed;

	speed = 0.1;
	if (prm->key.key_w != prm->key.key_s && prm->key.key_a != prm->key.key_d)
		speed = 0.707106 * speed;
	if (prm->key.key_w && !prm->key.key_s && is_valid_move(prm,
			sum_vect(prm->pos_player, prod_vect(speed, prm->view_dir))))
		prm->pos_player = sum_vect(prm->pos_player,
				prod_vect(speed, prm->view_dir));
	if (!prm->key.key_w && prm->key.key_s && is_valid_move(prm,
			sum_vect(prm->pos_player, prod_vect(-speed, prm->view_dir))))
		prm->pos_player = sum_vect(prm->pos_player,
				prod_vect(-speed, prm->view_dir));
	if (prm->key.key_d && !prm->key.key_a && is_valid_move(prm,
			sum_vect(prm->pos_player, prod_vect(speed, prm->screen_dir))))
		prm->pos_player = sum_vect(prm->pos_player,
				prod_vect(speed, prm->screen_dir));
	if (prm->key.key_a && !prm->key.key_d && is_valid_move(prm,
			sum_vect(prm->pos_player, prod_vect(-speed, prm->screen_dir))))
		prm->pos_player = sum_vect(prm->pos_player,
				prod_vect(-speed, prm->screen_dir));
}*/

t_coord	get_wanted_move(t_param *prm, float speed)
{
	t_coord	move;

	ft_memset(&move, 0, sizeof(t_coord));
	if (prm->key.key_w && !prm->key.key_s && !prm->key.key_a && !prm->key.key_d)
		move = prod_vect(speed, prm->view_dir);
	if (!prm->key.key_w && prm->key.key_s && !prm->key.key_a && !prm->key.key_d)
		move = prod_vect(-speed, prm->view_dir);
	if (!prm->key.key_w && !prm->key.key_s && !prm->key.key_a && prm->key.key_d)
		move = prod_vect(speed, prm->screen_dir);
	if (!prm->key.key_w && !prm->key.key_s && prm->key.key_a && !prm->key.key_d)
		move = prod_vect(-speed, prm->screen_dir);
	if (prm->key.key_w && !prm->key.key_s && !prm->key.key_a && prm->key.key_d)
		move = sum_vect(prod_vect(speed, prm->view_dir),
				prod_vect(speed, prm->screen_dir));
	if (!prm->key.key_w && prm->key.key_s && !prm->key.key_a && prm->key.key_d)
		move = sum_vect(prod_vect(-speed, prm->view_dir),
				prod_vect(speed, prm->screen_dir));
	if (!prm->key.key_w && prm->key.key_s && prm->key.key_a && !prm->key.key_d)
		move = sum_vect(prod_vect(-speed, prm->view_dir),
				prod_vect(-speed, prm->screen_dir));
	if (prm->key.key_w && !prm->key.key_s && prm->key.key_a && !prm->key.key_d)
		move = sum_vect(prod_vect(speed, prm->view_dir),
				prod_vect(-speed, prm->screen_dir));
	return (move);
}

t_coord	get_possible_move(t_param *prm, t_coord move)
{
	t_coord	move;
}

void	move_player(t_param *prm)
{
	float	speed;
	t_coord	new_pos;
	t_coord	move;

	speed = 0.1;
	if (prm->key.key_w != prm->key.key_s && prm->key.key_a != prm->key.key_d)
		speed = 0.707106 * speed;
	move = get_wanted_move(prm, speed);
	move = get_possible_move(prm, move);
	prm->pos_player = sum_vect(prm->pos_player, move);
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
