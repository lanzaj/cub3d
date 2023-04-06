/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlanza <jlanza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 18:17:26 by mbocquel          #+#    #+#             */
/*   Updated: 2023/04/06 07:38:40 by jlanza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	move_player(t_param *prm)
{
	double	speed;
	t_coord	move_dir;

	speed = 0.1;
	if (prm->key.key_shift)
		speed = 0.15;
	move_dir = get_wanted_move_dir(prm);
	if (!(move_dir.x == 0 && move_dir.y == 0) && is_valid_move(prm,
			sum_vect(prm->pos_player, prod_vect(speed, move_dir))))
		prm->pos_player = pos_buff(prm,
				sum_vect(prm->pos_player, prod_vect(speed, move_dir)));
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

static int	case_pos_buff(t_param *prm, double ang_move,
	t_coord pos, double buf)
{
	if (ang_move > 0 && ang_move < PI
		&& (ft_strchr("123456789B",
				prm->map.map[(int)(pos.y) - 1][(int)(pos.x)])
		|| (prm->map.map[(int)(pos.y) - 1][(int)(pos.x)] == 'D'
			&& status_door(prm, (int)(pos.x), (int)(pos.y) - 1) != OPENED))
			&& pos.y - (int)(pos.y) < buf)
		return (1);
	if (ang_move > PI && ang_move < 2 * PI
		&& (ft_strchr("123456789B",
				prm->map.map[(int)(pos.y) + 1][(int)(pos.x)])
		|| (prm->map.map[(int)(pos.y) + 1][(int)(pos.x)] == 'D'
			&& status_door(prm, (int)(pos.x), (int)(pos.y) + 1) != OPENED))
			&& (int)(pos.y) + 1 - pos.y < buf)
		return (2);
	return (3);
}

t_coord	pos_buff(t_param *prm, t_coord pos)
{
	t_coord	new_pos;
	double	ang_move;

	ang_move = angle_move(prm);
	new_pos = pos;
	if (case_pos_buff(prm, ang_move, pos, BUF) == 1)
		new_pos.y = (int)(pos.y) + BUF;
	if (case_pos_buff(prm, ang_move, pos, BUF) == 2)
		new_pos.y = (int)(pos.y) + 1 - BUF;
	if ((ang_move > (3 * PI) / 2 || ang_move < PI / 2)
		&& (ft_strchr("123456789B",
				prm->map.map[(int)(pos.y)][(int)(pos.x) + 1])
		|| (prm->map.map[(int)(pos.y)][(int)(pos.x) + 1] == 'D'
			&& status_door(prm, (int)(pos.x) + 1, (int)(pos.y)) != OPENED))
			&& (int)(pos.x) + 1 - pos.x < BUF)
		new_pos.x = (int)(pos.x + 1) - BUF;
	if (ang_move > PI / 2 && ang_move < (3 * PI) / 2
		&& (ft_strchr("123456789B",
				prm->map.map[(int)(pos.y)][(int)(pos.x) - 1])
		|| (prm->map.map[(int)(pos.y)][(int)(pos.x) - 1] == 'D'
			&& status_door(prm, (int)(pos.x) - 1, (int)(pos.y)) != OPENED))
			&& pos.x - (int)(pos.x) < BUF)
		new_pos.x = (int)pos.x + BUF;
	return (new_pos);
}

int	is_valid_move(t_param *prm, t_coord pos)
{
	if (ft_strchr("123456789", prm->map.map[(int)(pos.y)][(int)(pos.x)]))
		return (0);
	if (prm->map.map[(int)(pos.y)][(int)(pos.x)] == 'D'
		&& status_door(prm, (int)(pos.x), (int)(pos.y)) != OPENED)
		return (0);
	return (1);
}
