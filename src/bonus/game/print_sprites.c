/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_sprites.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlanza <jlanza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 16:01:22 by jlanza            #+#    #+#             */
/*   Updated: 2023/04/06 16:56:08 by jlanza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static int	put_img_to_front(t_param *prm, t_img *xpm, int dx, t_coord sprite)
{
	t_boundary b;
	int ret;

	ret = 0;
	init_col_px_sprite(prm, sprite, &b.col);
	init_boundary(prm, xpm, &b, dx);
	while (b.i.x < b.stop.x - b.offset_stop.x && b.i.x >= 0 && b.i.x < prm->width)
	{
		b.i.y = b.start.y + b.offset_start.y;
		if (check_distance_x(prm, sprite, b.i))
		{
			while (b.i.y < b.stop.y - b.offset_stop.y && b.i.y >= 0 && b.i.y < prm->height)
			{
				ret += put_on_one_pixel(prm, xpm, b, sprite);
				b.i.y++;
			}
		}
		b.i.x++;
	}
	return (ret);
}

static double get_angle_with_player_view(t_param *prm, t_coord sprite)
{
	return (convert_angle(-atan2((sprite.y - prm->pos_player.y),
								 sprite.x - prm->pos_player.x)));
}

static void print_sprite(t_param *prm, t_sprite *sprite, t_img *xpm)
{
	double theta;
	int dx;
	int seen;

	dx = 0;
	theta = get_angle_with_player_view(prm, sprite->coord);
	dx = (int)nearbyint((tan(convert_angle(prm->view_ang - theta)) * prm->width) / (2 * 0.5773502)) + (prm->width / 2);
	if (convert_angle(prm->view_ang - theta - PI / 2) >= PI)
		seen = put_img_to_front(prm, xpm, dx, sprite->coord);
	if (sprite->type == 'B' && seen && (prm->gun.shooting || sprite->health == 0) && convert_angle(prm->view_ang - theta - PI / 2) >= PI / 4)
	{
		if (sprite->health != 0)
			sprite->health--;
		if (sprite->health == 0)
		{
			put_img_to_front(prm, &prm->gun.explo[sprite->frame], dx, sprite->coord);
			sprite->frame++;
			if (sprite->frame == 7)
				sprite->dead = 1;
		}
	}
}

void print_every_sprite(t_param *prm)
{
	t_list *current;
	t_sprite *sprite;

	current = prm->sprite_lst;
	ft_lstsort(prm, current, &cmp_distance);
	while (current)
	{
		sprite = (t_sprite *)current->content;
		if (sprite->type == 'B' && !sprite->dead)
		{
			print_sprite(prm, sprite, &prm->map.barrel_texture);
		}
		if (sprite->type == 'C')
		{
			print_sprite(prm, sprite, &prm->map.cables_texture);
		}
		if (sprite->type == 'R')
		{
			print_sprite(prm, sprite, &prm->map.front1_texture);
		}
		current = current->next;
	}
}
