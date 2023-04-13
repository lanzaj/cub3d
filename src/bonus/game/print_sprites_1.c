/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_sprites_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlanza <jlanza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 16:01:22 by jlanza            #+#    #+#             */
/*   Updated: 2023/04/13 10:00:07 by jlanza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	put_img_to_front(t_param *prm, t_img *xpm, int dx, t_sprite *s)
{
	t_boundary	b;
	int			ret;

	ret = 0;
	init_col_px_sprite(prm, s->coord, &b.col);
	init_boundary(prm, xpm, &b, dx);
	while (b.i.x < b.stop.x - b.offset_stop.x
		&& b.i.x >= 0 && b.i.x < prm->width)
	{
		b.i.y = b.start.y + b.offset_start.y;
		if (check_distance_x(prm, s->coord, b.i))
		{
			while (b.i.y < b.stop.y - b.offset_stop.y
				&& b.i.y >= 0 && b.i.y < prm->height)
			{
				ret += put_on_one_pixel(prm, xpm, b, s);
				b.i.y++;
			}
		}
		b.i.x++;
	}
	return (ret);
}

double	get_angle_with_player_view(t_param *prm, t_coord sprite)
{
	return (convert_angle(-atan2((sprite.y - prm->pos_player.y),
				sprite.x - prm->pos_player.x)));
}

void	explode(t_param *prm, t_sprite *sprite)
{
	t_list	*current;

	current = prm->sprite_lst;
	while (current)
	{
		if (current->content != sprite
			&& get_distance(((t_sprite *)current->content)->coord,
				sprite->coord) < 1.5
			&& ((t_sprite *)current->content)->health != 0)
			((t_sprite *)current->content)->health--;
		current = current->next;
	}
	if (get_distance(sprite->coord, prm->pos_player) < 1.5)
		prm->n_life--;
}

void	ai_enemies(t_param *prm, t_sprite *sprite, int seen)
{
	static int	shooting = 0;

	if (seen)
		sprite->has_been_seen = 50000;
	if (sprite->type == 'R' && sprite->has_been_seen && !sprite->ok_to_shoot)
	{
		sprite->follow = TRUE;
		sprite->has_been_seen--;
	}
	if (sprite->type == 'R' && seen > 100000
		&& get_distance_square(sprite->coord, prm->pos_player) < SHOOT_DST_SQ
		&& sprite->health > 0)
	{
		sprite->ok_to_shoot = TRUE;
		sprite->follow = FALSE;
		shooting++;
		if (shooting > 40)
		{
			shooting = 0;
			prm->n_life--;
		}
	}
	else
		sprite->ok_to_shoot = FALSE;
}

void	do_gun_damage(t_param *prm, t_sprite *sprite, int dx, int seen)
{
	if ((sprite->type == 'B' || sprite->type == 'R') && seen
		&& (prm->gun.frame_count == 1 && sprite->health > 0)
		&& dx > (prm->width / 2) - 50 && dx < (prm->width / 2) + 50)
		sprite->health--;
	if (sprite->type == 'R' && sprite->last_health != sprite->health)
	{
		sprite->red_color = 255;
		sprite->last_health = sprite->health;
	}
}
