/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_sprites_4.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbocquel <mbocquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 11:17:03 by mbocquel          #+#    #+#             */
/*   Updated: 2023/04/12 11:17:07 by mbocquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	init_boundary_part2(t_param *prm, t_img *xpm, t_boundary *b)
{
	if (xpm == &prm->map.cables_texture)
	{
		b->offset_stop.y = (50 * b->col.px_wall / 64) + b->col.ofset;
		b->offset_start.x = (15 * b->col.px_wall / 64);
		b->offset_stop.x = (14 * b->col.px_wall / 64);
	}
	if (xpm == &prm->map.health_texture)
	{
		b->offset_start.y = (44 * b->col.px_wall / 64) - b->col.ofset;
		b->offset_start.x = (21 * b->col.px_wall / 64);
		b->offset_stop.x = (21 * b->col.px_wall / 64);
	}
	b->i.x = b->start.x + b->offset_start.x;
	if (b->i.x < 0)
		b->i.x = 0;
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
	init_boundary_part2(prm, xpm, b);
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
