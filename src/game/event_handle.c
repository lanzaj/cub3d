/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbocquel <mbocquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 17:21:36 by mbocquel          #+#    #+#             */
/*   Updated: 2023/03/24 14:03:44 by mbocquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	key_press(int keycode, void *p)
{
	t_param	*prm;

	prm = (t_param *)p;
	if (keycode == KEY_ESC)
		close_win(p);
	if (keycode == KEY_W)
		prm->key.key_w = 1;
	if (keycode == KEY_A)
		prm->key.key_a = 1;
	if (keycode == KEY_S)
		prm->key.key_s = 1;
	if (keycode == KEY_D)
		prm->key.key_d = 1;
	if (keycode == KEY_RIGHT_ARROW)
		prm->key.right = 1;
	if (keycode == KEY_LEFT_ARROW)
		prm->key.left = 1;
	return (0);
}

int	key_release(int keycode, void *p)
{
	t_param	*prm;

	prm = (t_param *)p;
	if (keycode == KEY_ESC)
		close_win(p);
	if (keycode == KEY_W)
		prm->key.key_w = 0;
	if (keycode == KEY_A)
		prm->key.key_a = 0;
	if (keycode == KEY_S)
		prm->key.key_s = 0;
	if (keycode == KEY_D)
		prm->key.key_d = 0;
	if (keycode == KEY_RIGHT_ARROW)
		prm->key.right = 0;
	if (keycode == KEY_LEFT_ARROW)
		prm->key.left = 0;
	return (0);
}

int	handle_mouse_move(int x, int y, void *param)
{
	t_param	*prm;

	(void)y;
	prm = (t_param *)param;
	if (x < prm->width / 4)
		prm->key.left = 1;
	else if (x >= prm->width / 4 && x < (prm->width * 3) / 4)
	{
		prm->key.left = 0;
		prm->key.right = 0;
	}
	else
		prm->key.right = 1;
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
