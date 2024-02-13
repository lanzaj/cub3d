/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ai.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlanza <jlanza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 19:21:43 by jlanza            #+#    #+#             */
/*   Updated: 2024/02/12 19:36:16 by jlanza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	update_shooting_frame(t_param *prm, int *shooting)
{
	(*shooting)++;
	if (*shooting > 40)
	{
		*shooting = 0;
		prm->n_life--;
	}
}

void	ai_enemies(t_param *prm, t_sprite *sprite, int seen)
{
	static int	shooting = 0;
	double		dist;

	if (seen > 0)
		sprite->has_been_seen = 1;
	dist = get_distance_square(sprite->coord, prm->pos_player);
	if (sprite->type == 'R')
	{
		if ((sprite->seen && !sprite->ok_to_shoot)
			|| (!sprite->seen && dist > 1 && sprite->has_been_seen))
			sprite->follow = TRUE;
		if (sprite->health > 0 && ((seen > 1 && dist < SHOOT_DST_SQ)
				|| (dist <= 1 && sprite->has_been_seen)))
		{
			sprite->ok_to_shoot = TRUE;
			sprite->follow = FALSE;
			update_shooting_frame(prm, &shooting);
		}
		else
			sprite->ok_to_shoot = FALSE;
	}
}

void	do_gun_damage(t_param *prm, t_sprite *sprite, int targeted)
{
	if ((sprite->type == 'B' || sprite->type == 'R') && targeted
		&& (prm->gun.frame_count == 1 && sprite->health > 0))
		sprite->health--;
	if (sprite->type == 'R' && sprite->last_health != sprite->health)
	{
		sprite->red_color = 255;
		sprite->last_health = sprite->health;
	}
}
