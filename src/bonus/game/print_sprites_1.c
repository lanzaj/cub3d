/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_sprites_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlanza <jlanza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 16:01:22 by jlanza            #+#    #+#             */
/*   Updated: 2024/02/12 19:36:25 by jlanza           ###   ########.fr       */
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

void	put_target_to_front(t_param *prm, t_img *xpm, int dx, t_sprite *s)
{
	t_boundary	b;
	int			tmp;

	s->seen = 0;
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
				tmp = 0;
				tmp += put_on_one_pixel(prm, xpm, b, s);
				if (b.i.x > prm->width / 2 - 5 && b.i.x < prm->width / 2 + 5)
					s->targeted += 1;
				s->seen += tmp;
				b.i.y++;
			}
		}
		b.i.x++;
	}
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
