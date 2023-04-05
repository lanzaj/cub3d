/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_and_rotate.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbocquel <mbocquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 14:11:13 by mbocquel          #+#    #+#             */
/*   Updated: 2023/04/05 16:03:24 by mbocquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	move_player(t_param *prm)
{
	double	speed;
	t_coord	move_dir;

	speed = 0.05;
	move_dir = get_wanted_move_dir(prm);
	if (!(move_dir.x == 0 && move_dir.y == 0) && is_valid_move(prm,
			sum_vect(prm->pos_player, prod_vect(speed, move_dir))))
		prm->pos_player = pos_buff(prm,
				sum_vect(prm->pos_player, prod_vect(speed, move_dir)));
}

void	rotate_player(t_param *prm)
{
	if (prm->key.left && !prm->key.right)
	{
		if (prm->view_ang == 2 * PI)
			prm->view_ang = 0;
		prm->view_dir = rotate((double)PI / 128, prm->view_dir);
		prm->screen_dir = rotate((double)PI / 128, prm->screen_dir);
		prm->view_ang += (double)PI / 128;
		if (prm->view_ang == 2 * PI)
			prm->view_ang = 0;
	}
	if (!prm->key.left && prm->key.right)
	{
		if (prm->view_ang == 0)
			prm->view_ang = 2 * PI;
		prm->view_dir = rotate((double)(-PI / 128), prm->view_dir);
		prm->screen_dir = rotate((double)(-PI / 128), prm->screen_dir);
		prm->view_ang -= (double)PI / 128;
		if (prm->view_ang == 0)
			prm->view_ang = 2 * PI;
	}
}
