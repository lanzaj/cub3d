/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbocquel <mbocquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 17:21:36 by mbocquel          #+#    #+#             */
/*   Updated: 2023/03/21 17:45:47 by mbocquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	handle_key(int key, void *p)
{
	t_param	*prm;

	prm = (t_param *)p;
	(void)prm;
	if (key == KEY_A || key == KEY_W || key == KEY_S || key == KEY_D)
		move_player(prm, key);
	if (key == KEY_LEFT_ARROW || key == KEY_RIGHT_ARROW)
		rotate_player(prm, key);
	if (key == KEY_ESC)
		close_win(p);
	return (0);
}

int	is_valid_move(t_param *prm, t_coord pos)
{
	int	x;
	int	y;

	x = (int)pos.x;
	y = (int)pos.y;
	if (prm->map.map[y][x] == '0')
		return (1);
	return (0);
}

void	move_player(t_param *prm, int key)
{
	t_coord	new_pos;

	if (key == KEY_W)
		new_pos = sum_vect(prm->pos_player, prod_vect(0.1, prm->view_dir));
	if (key == KEY_S)
		new_pos = sum_vect(prm->pos_player, prod_vect(-0.1, prm->view_dir));
	if (key == KEY_D)
		new_pos = sum_vect(prm->pos_player, prod_vect(0.1, prm->screen_dir));
	if (key == KEY_A)
		new_pos = sum_vect(prm->pos_player, prod_vect(-0.1, prm->screen_dir));
	if (is_valid_move(prm, new_pos))
		prm->pos_player = new_pos;
	print_game(prm);
}

void	rotate_player(t_param *prm, int key)
{
	if (key == KEY_LEFT_ARROW)
	{
		if (prm->view_ang == 2 * PI)
			prm->view_ang = 0;
		prm->view_dir = rotate((double)PI / 16, prm->view_dir);
		prm->screen_dir = rotate((double)PI / 16, prm->screen_dir);
		prm->view_ang += (double)PI / 16;
		if (prm->view_ang == 2 * PI)
			prm->view_ang = 0;
	}
	if (key == KEY_RIGHT_ARROW)
	{
		if (prm->view_ang == 0)
			prm->view_ang = 2 * PI;
		prm->view_dir = rotate((double)(-PI / 16), prm->view_dir);
		prm->screen_dir = rotate((double)(-PI / 16), prm->screen_dir);
		prm->view_ang -= (double)PI / 16;
		if (prm->view_ang == 0)
			prm->view_ang = 2 * PI;
	}
	print_game(prm);
}
