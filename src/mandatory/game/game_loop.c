/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbocquel <mbocquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 14:02:26 by mbocquel          #+#    #+#             */
/*   Updated: 2023/03/29 14:11:07 by mbocquel         ###   ########.fr       */
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
	return (0);
}

t_coord	get_wanted_move_dir(t_param *prm)
{
	t_coord	move;

	ft_memset(&move, 0, sizeof(t_coord));
	if (prm->key.key_w && !prm->key.key_s && !prm->key.key_a && !prm->key.key_d)
		move = prod_vect(1, prm->view_dir);
	if (!prm->key.key_w && prm->key.key_s && !prm->key.key_a && !prm->key.key_d)
		move = prod_vect(-1, prm->view_dir);
	if (!prm->key.key_w && !prm->key.key_s && !prm->key.key_a && prm->key.key_d)
		move = prod_vect(1, prm->screen_dir);
	if (!prm->key.key_w && !prm->key.key_s && prm->key.key_a && !prm->key.key_d)
		move = prod_vect(-1, prm->screen_dir);
	if (prm->key.key_w && !prm->key.key_s && !prm->key.key_a && prm->key.key_d)
		move = sum_vect(prod_vect(0.707106, prm->view_dir),
				prod_vect(0.707106, prm->screen_dir));
	if (!prm->key.key_w && prm->key.key_s && !prm->key.key_a && prm->key.key_d)
		move = sum_vect(prod_vect(-0.707106, prm->view_dir),
				prod_vect(0.707106, prm->screen_dir));
	if (!prm->key.key_w && prm->key.key_s && prm->key.key_a && !prm->key.key_d)
		move = sum_vect(prod_vect(-0.707106, prm->view_dir),
				prod_vect(-0.707106, prm->screen_dir));
	if (prm->key.key_w && !prm->key.key_s && prm->key.key_a && !prm->key.key_d)
		move = sum_vect(prod_vect(0.707106, prm->view_dir),
				prod_vect(-0.707106, prm->screen_dir));
	return (move);
}

double	angle_move(t_param *prm)
{
	double	ang;

	ang = convert_angle(prm->view_ang);
	if (!prm->key.key_w && prm->key.key_s && !prm->key.key_a && !prm->key.key_d)
		ang = convert_angle(prm->view_ang + PI);
	if (!prm->key.key_w && !prm->key.key_s && !prm->key.key_a && prm->key.key_d)
		ang = convert_angle(prm->view_ang - PI / 2);
	if (!prm->key.key_w && !prm->key.key_s && prm->key.key_a && !prm->key.key_d)
		ang = convert_angle(prm->view_ang + PI / 2);
	if (prm->key.key_w && !prm->key.key_s && !prm->key.key_a && prm->key.key_d)
		ang = convert_angle(prm->view_ang - PI / 4);
	if (!prm->key.key_w && prm->key.key_s && !prm->key.key_a && prm->key.key_d)
		ang = convert_angle(prm->view_ang - (3 * PI) / 4);
	if (!prm->key.key_w && prm->key.key_s && prm->key.key_a && !prm->key.key_d)
		ang = convert_angle(prm->view_ang + (3 * PI) / 4);
	if (prm->key.key_w && !prm->key.key_s && prm->key.key_a && !prm->key.key_d)
		ang = convert_angle(prm->view_ang + PI / 4);
	return (ang);
}

t_coord	pos_buff(t_param *prm, t_coord pos)
{
	double	buf;
	t_coord	new_pos;
	double	ang_move;

	ang_move = angle_move(prm);
	buf = 0.2;
	new_pos = pos;
	if (ang_move > 0 && ang_move < PI
		&& prm->map.map[(int)(pos.y) - 1][(int)(pos.x)] != '0'
			&& pos.y - (int)(pos.y) < buf)
		new_pos.y = (int)(pos.y) + buf;
	if (ang_move > PI && ang_move < 2 * PI
		&& prm->map.map[(int)(pos.y) + 1][(int)(pos.x)] != '0'
			&& (int)(pos.y) + 1 - pos.y < buf)
		new_pos.y = (int)(pos.y) + 1 - buf;
	if ((ang_move > (3 * PI) / 2 || ang_move < PI / 2)
		&& prm->map.map[(int)(pos.y)][(int)(pos.x) + 1] != '0'
			&& (int)(pos.x) + 1 - pos.x < buf)
		new_pos.x = (int)(pos.x + 1) - buf;
	if (ang_move > PI / 2 && ang_move < (3 * PI) / 2
		&& prm->map.map[(int)(pos.y)][(int)(pos.x) - 1] != '0'
			&& pos.x - (int)(pos.x) < buf)
		new_pos.x = (int)pos.x + buf;
	return (new_pos);
}
