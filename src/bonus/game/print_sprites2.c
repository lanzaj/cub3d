/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_sprites2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlanza <jlanza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 16:01:22 by jlanza            #+#    #+#             */
/*   Updated: 2023/04/09 00:45:42 by jlanza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

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

void	init_boundary(t_param *prm, t_img *xpm, t_boundary *b, int dx)
{
	b->start.x = dx - (b->col.px_wall / 2);
	b->start.y = b->col.px_cell;
	b->stop.x = b->col.px_wall + b->start.x;
	b->stop.y = b->col.px_wall + b->start.y;
	b->offset_start.x = 0;
	b->offset_start.y = 0;
	b->offset_stop.x = 0;
	b->offset_stop.y = 0;
	if (xpm == &prm->map.barrel_texture)
	{
		b->offset_start.x = (18 * b->col.px_wall / 64);
		b->offset_stop.x = (18 * b->col.px_wall / 64);
		b->offset_start.y = (30 * b->col.px_wall / 64) - b->col.ofset;
	}
	if (xpm == &prm->map.cables_texture)
	{
		b->offset_stop.y = (50 * b->col.px_wall / 64) + b->col.ofset;
		b->offset_start.x = (15 * b->col.px_wall / 64);
		b->offset_stop.x = (14 * b->col.px_wall / 64);
	}
	b->i.x = b->start.x + b->offset_start.x;
	if (b->i.x < 0)
		b->i.x = 0;
}

int	put_on_one_pixel(t_param *prm, t_img *xpm, t_boundary b, t_sprite *s)
{
	t_point		pixel;
	double		dist;
	t_coord_int	coord;

	dist = (s->coord.x - prm->pos_player.x) * (s->coord.x - prm->pos_player.x)
		+ (s->coord.y - prm->pos_player.y) * (s->coord.y - prm->pos_player.y);
	coord.x = (b.i.x - b.start.x) * xpm->width / (b.col.px_wall);
	coord.y = (b.i.y - b.start.y + b.col.ofset) * xpm->height / (b.col.px_wall);
	if (coord.x < 0 || coord.x >= xpm->width
		|| coord.y < 0 || coord.y >= xpm->height)
		return (0);
	if (s->red_color && s->red_color > *get_red_color())
		pixel.color = get_darken_color(xpm, coord, dist, &s->red_color);
	else
		pixel.color = get_darken_color(xpm, coord, dist, get_red_color());
	pixel.x = b.i.x;
	pixel.y = b.i.y;
	if (check_distance_y(prm, s->coord, b.i))
		return (pixel_put_img(&(prm->layer.front), pixel));
	return (0);
}
