/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbocquel <mbocquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 17:21:36 by mbocquel          #+#    #+#             */
/*   Updated: 2023/03/17 18:44:04 by mbocquel         ###   ########.fr       */
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

void	move_player(t_param *prm, int key)
{
	if (key == KEY_A)
		prm->pos_player.x -= 0.1;
	if (key == KEY_D)
		prm->pos_player.x += 0.1;
	if (key == KEY_W)
		prm->pos_player.y -= 0.1;
	if (key == KEY_S)
		prm->pos_player.y += 0.1;
	if (prm->pos_player.x < 0)
		prm->pos_player.x = 0;
	if (prm->pos_player.y < 0)
		prm->pos_player.y = 0;
	if (prm->pos_player.x > prm->map.map_width - 1)
		prm->pos_player.x = prm->map.map_width - 1;
	if (prm->pos_player.y > prm->map.map_height - 1)
		prm->pos_player.y = prm->map.map_height - 1;
	print_minimap(prm);
	print_player(prm);
}

void	rotate_player(t_param *prm, int key)
{
	if (key == KEY_RIGHT_ARROW)
		prm->view_dir = rotate((double)PI / 24, prm->view_dir);
	if (key == KEY_LEFT_ARROW)
		prm->view_dir = rotate((double)(-PI / 24), prm->view_dir);
	print_minimap(prm);
	print_player(prm);
}
