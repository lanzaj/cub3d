/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_event.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbocquel <mbocquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 17:58:53 by mbocquel          #+#    #+#             */
/*   Updated: 2023/04/07 14:45:28 by mbocquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	rotate_mouse_player(t_param *prm, double speed)
{
	if (speed < 0)
	{
		speed = -speed;
		if (prm->view_ang == 2 * PI)
			prm->view_ang = 0;
		prm->view_dir = rotate((double)PI * speed / MOUSE_SPEED, prm->view_dir);
		prm->screen_dir = rotate((double)PI * speed
				/ MOUSE_SPEED, prm->screen_dir);
		prm->view_ang += (double)PI * speed / MOUSE_SPEED;
		if (prm->view_ang == 2 * PI)
			prm->view_ang = 0;
	}
	else if (speed > 0)
	{
		if (prm->view_ang == 0)
			prm->view_ang = 2 * PI;
		prm->view_dir = rotate((double)(-PI * speed
					/ MOUSE_SPEED), prm->view_dir);
		prm->screen_dir = rotate((double)(-PI * speed / MOUSE_SPEED),
				prm->screen_dir);
		prm->view_ang -= (double)PI * speed / MOUSE_SPEED;
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

int	handle_mouse_click(int button, int x, int y, void *p)
{
	t_param	*prm;

	prm = (t_param *)p;
	(void)x;
	(void)y;
	if (button == 1 && prm->gun.shooting == FALSE)
	{
		if (prm->in_focus)
			prm->gun.shooting = TRUE;
		else
			enter_window(p);
	}
	return (0);
}
