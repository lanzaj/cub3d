/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_sprites_3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbocquel <mbocquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 16:01:22 by jlanza            #+#    #+#             */
/*   Updated: 2023/04/12 11:16:47 by mbocquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	print_every_sprite(t_param *prm)
{
	t_list		*current;
	t_sprite	*sprite;

	current = prm->sprite_lst;
	ft_lstsort(prm, current, &cmp_distance);
	while (current)
	{
		sprite = (t_sprite *)current->content;
		select_sprite(prm, sprite);
		current = current->next;
	}
}

void	init_col_px_sprite(t_param *prm, t_coord sprite, t_px_col *col)
{
	col->px_wall = (prm->height * 3)
		/ (2 * ft_max_d(0.01, get_distance(prm->pos_player, sprite)));
	col->px_cell = (prm->height - ft_min(col->px_wall, prm->height)) / 2;
	col->px_total = 2 * col->px_cell + col->px_wall;
	col->color_cell = -1;
	col->color_floor = -1;
	col->ofset = (ft_max(0, (col->px_total - prm->height) / 2));
}

int	check_distance_x(t_param *prm, t_coord sprite, t_coord_int i)
{
	if (prm->impact[i.x].is_door
		&& prm->impact[i.x].status_door != CLOSED)
		return (get_distance_square(sprite, prm->pos_player)
			< get_distance_square(prm->pos_player, prm->impact[i.x].wall_only)
			&& get_distance_square(sprite, prm->pos_player) > 0.3 * 0.3);
	else
		return (get_distance_square(sprite, prm->pos_player)
			< get_distance_square(prm->pos_player,
				prm->impact[i.x].wall_and_door)
			&& get_distance_square(sprite, prm->pos_player) > 0.3 * 0.3);
}

int	check_distance_y(t_param *prm, t_coord sprite, t_coord_int i)
{
	t_px_col	col;

	if (get_distance_square(sprite, prm->pos_player)
		< get_distance_square(prm->pos_player, prm->impact[i.x].wall_and_door)
		&& get_distance_square(sprite, prm->pos_player) > 0.3 * 0.3)
		return (1);
	init_col_px(prm, prm->impact[i.x].wall_and_door,
		prm->impact[i.x].ang, &col);
	if (prm->impact[i.x].is_door
		&& (prm->impact[i.x].status_door == OPENING
			|| prm->impact[i.x].status_door == CLOSING))
	{
		return (
			(col.px_wall * (100 - prm->tab_doors[find_door(prm,
							prm->impact[i.x].wall_and_door)
					]->percent_open)) / 100 - col.ofset + col.px_cell < i.y);
	}
	else
		return (1);
}
