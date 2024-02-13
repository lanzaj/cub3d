/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbocquel <mbocquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 14:11:13 by mbocquel          #+#    #+#             */
/*   Updated: 2023/04/05 18:45:17 by mbocquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

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
