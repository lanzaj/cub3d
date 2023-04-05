/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbocquel <mbocquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 17:21:36 by mbocquel          #+#    #+#             */
/*   Updated: 2023/04/05 14:45:09 by mbocquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	update_key_m(t_param *prm)
{
	if (prm->key.key_m == 1)
		prm->key.key_m = 0;
	else
		prm->key.key_m = 1;
}

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
	if (keycode == KEY_SPACE)
		prm->key.key_space = 1;
	if (keycode == KEY_TAB)
		leave_win(p);
	if (keycode == KEY_M && prm->print_minimap)
		prm->print_minimap = FALSE;
	else if (keycode == KEY_M)
		prm->print_minimap = TRUE;
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

void	rotate_mouse_player(t_param *prm, double speed)
{
	if (speed < 0)
	{
		speed = -speed;
		if (prm->view_ang == 2 * PI)
			prm->view_ang = 0;
		prm->view_dir = rotate((double)PI * speed / 36000, prm->view_dir);
		prm->screen_dir = rotate((double)PI * speed / 36000, prm->screen_dir);
		prm->view_ang += (double)PI * speed / 36000;
		if (prm->view_ang == 2 * PI)
			prm->view_ang = 0;
	}
	else if (speed > 0)
	{
		if (prm->view_ang == 0)
			prm->view_ang = 2 * PI;
		prm->view_dir = rotate((double)(-PI * speed / 36000), prm->view_dir);
		prm->screen_dir = rotate((double)(-PI * speed / 36000),
				prm->screen_dir);
		prm->view_ang -= (double)PI * speed / 36000;
		if (prm->view_ang == 0)
			prm->view_ang = 2 * PI;
	}
	mlx_mouse_move(prm->mlx, prm->win, prm->width / 2, prm->height / 2);
}

int	handle_mouse_move(int x, int y, void *param)
{
	t_param	*prm;

	(void)y;
	prm = (t_param *)param;
	if (prm->in_focus)
	{
		if (x != prm->width / 2)
			rotate_mouse_player(prm, (double)(x - (prm->width / 2)));
	}
	return (0);
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
