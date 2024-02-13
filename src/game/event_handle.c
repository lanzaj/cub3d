/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlanza <jlanza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 17:21:36 by mbocquel          #+#    #+#             */
/*   Updated: 2023/04/06 14:03:01 by jlanza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static int	key_press_part2(int keycode, void *p)
{
	t_param	*prm;

	prm = (t_param *)p;
	if (keycode == KEY_RIGHT_ARROW && prm->in_focus)
		prm->key.right = 1;
	if (keycode == KEY_LEFT_ARROW && prm->in_focus)
		prm->key.left = 1;
	if (keycode == KEY_SPACE && prm->in_focus)
		prm->key.key_space = 1;
	if (keycode == KEY_TAB)
		leave_win(p);
	if (keycode == KEY_M && prm->print_minimap)
		prm->print_minimap = FALSE;
	else if (keycode == KEY_M)
		prm->print_minimap = TRUE;
	if (keycode == KEY_CTRL && prm->in_focus)
		handle_mouse_click(1, 0, 0, p);
	if (keycode == KEY_SHIFT)
		prm->key.key_shift = 1;
	if (keycode == KEY_F && prm->print_fps && ft_printf("\r                  \r"))
		prm->print_fps = FALSE;
	else if (keycode == KEY_F)
		prm->print_fps = TRUE;
	return (0);
}

int	key_press(int keycode, void *p)
{
	t_param	*prm;

	prm = (t_param *)p;
	if (keycode == KEY_ESC)
		close_win(p);
	if (keycode == KEY_W && prm->in_focus)
		prm->key.key_w = 1;
	if (keycode == KEY_A && prm->in_focus)
		prm->key.key_a = 1;
	if (keycode == KEY_S && prm->in_focus)
		prm->key.key_s = 1;
	if (keycode == KEY_D && prm->in_focus)
		prm->key.key_d = 1;
	return (key_press_part2(keycode, p));
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
	if (keycode == KEY_SHIFT)
		prm->key.key_shift = 0;
	return (0);
}
