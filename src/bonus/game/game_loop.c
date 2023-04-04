/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlanza <jlanza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 14:02:26 by mbocquel          #+#    #+#             */
/*   Updated: 2023/04/04 14:42:23 by jlanza           ###   ########.fr       */
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
	t_coord	sprite;

	update_frame(prm);
	move_player(prm);
	rotate_player(prm);
	find_door_to_open(prm);
	change_door_status(prm);
	print_game(prm);
	sprite.x = 4.5;
	sprite.y = 4.5;
	print_sprite(prm, sprite);
	mlx_put_image_to_window(prm->mlx, prm->win, prm->layer.front.img, 0, 0);
	print_minimap(prm);
	mlx_put_image_to_window(prm->mlx, prm->win, prm->mini_map.img,
		prm->width - 10 - prm->mini_map.width, 10);
	return (0);
}
