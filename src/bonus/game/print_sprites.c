/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_sprites.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlanza <jlanza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 16:01:22 by jlanza            #+#    #+#             */
/*   Updated: 2023/04/05 14:27:40 by jlanza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	init_col_px_sprite(t_param *prm, t_coord sprite, t_px_col *col)
{
	col->px_wall = (prm->height * 3)
		/ (2 * ft_max_d(0.01, get_distance(prm->pos_player, sprite)));
	col->px_cell = (prm->height - ft_min(col->px_wall, prm->height)) / 2;
	col->px_total = 2 * col->px_cell + col->px_wall;
	col->color_cell = -1;
	col->color_floor = -1;
	col->ofset = (ft_max(0, (col->px_total - prm->height) / 2));
}

static void	pixel_put_img(t_img *img, t_point pixel)
{
	char	*dst;

	if (!(pixel.x < 0 || pixel.x >= img->width || pixel.y < 0
			|| pixel.y >= img->height
			|| pixel.color == -1 || get_t(pixel.color) == 255))
	{
		dst = img->addr + (pixel.y * img->line_length
				+ pixel.x * (img->bits_per_pixel / 8));
		*(unsigned int *)dst = pixel.color;
	}
}

static int	check_distance_x(t_param *prm, t_coord sprite, t_coord_int i)
{
	if (prm->impact[i.x].is_door && prm->impact[i.x].status_door != CLOSED)
		return (get_distance(sprite, prm->pos_player)
			< get_distance(prm->pos_player, prm->impact[i.x].wall_only)
			&& get_distance(sprite, prm->pos_player) > 0.3);
	else
		return (get_distance(sprite, prm->pos_player)
			< get_distance(prm->pos_player, prm->impact[i.x].wall_and_door)
			&& get_distance(sprite, prm->pos_player) > 0.3);
}

static int	check_distance_y(t_param *prm, t_coord sprite, t_coord_int i)
{
	t_px_col	col;

	if (get_distance(sprite, prm->pos_player)
		< get_distance(prm->pos_player, prm->impact[i.x].wall_and_door)
		&& get_distance(sprite, prm->pos_player) > 0.3)
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

static void	init_boundary(t_param *prm, t_img *xpm, t_boundary *b, int dx)
{
	b->start.x = dx - (b->col.px_wall / 2);

	b->start.y = b->col.px_cell;
	b->stop.x = b->col.px_wall + b->start.x;
	b->stop.y = b->col.px_wall + b->start.y;
	b->offset_start.x = 0;
	b->offset_start.y = 0;
	if (xpm == &prm->map.barrel_texture)
	{
		b->offset_start.x = (18 * b->col.px_wall / 64);
		//b->offset_stop
		b->offset_start.y = (30 * b->col.px_wall / 64) - b->col.ofset;
	}
	b->i.x = b->start.x + b->offset_start.x;
	if (b->i.x < 0)
		b->i.x = 0;
}

static void	put_img_to_front(t_param *prm, t_img *xpm, int dx, t_coord sprite)
{
	t_point		pixel;
	t_boundary	b;

	init_col_px_sprite(prm, sprite, &b.col);
	init_boundary(prm, xpm, &b, dx);
	while (b.i.x < b.stop.x && b.i.x >= 0 && b.i.x < prm->width)
	{
		b.i.y = b.start.y + b.offset_start.y;
		if (check_distance_x(prm, sprite, b.i))
		{
			while (b.i.y < b.stop.y && b.i.y >= 0 && b.i.y < prm->height)
			{
				pixel.color = get_color(xpm,
						(b.i.x - b.start.x) * xpm->width / (b.col.px_wall),
						(b.i.y - b.start.y + (b.col.ofset))
						* xpm->height / (b.col.px_wall));
				pixel.x = b.i.x;
				pixel.y = b.i.y;
				if (check_distance_y(prm, sprite, b.i))
				{
					int tmp = pixel.color;
					pixel.color = 0x00000000;
					pixel_put_img(&(prm->layer.front), pixel);
					pixel.color = tmp;
					pixel_put_img(&(prm->layer.front), pixel);
				}
				b.i.y++;
			}
		}
		b.i.x++;
	}
}

static double	get_angle_with_player_view(t_param *prm, t_coord sprite)
{
	return (convert_angle(-atan2((sprite.y - prm->pos_player.y),
				sprite.x - prm->pos_player.x)));
}

static void	print_sprite(t_param *prm, t_coord sprite, t_img *xpm)
{
	double	theta;
	int		dx;

	dx = 0;
	theta = get_angle_with_player_view(prm, sprite);
	dx = (int)nearbyint((tan(convert_angle(prm->view_ang - theta))
				* prm->width) / (2 * 0.5773502)) + (prm->width / 2);
	if (convert_angle(prm->view_ang - theta - PI / 2) >= PI)
		put_img_to_front(prm, xpm, dx, sprite);
}

void	print_every_sprite(t_param *prm)
{
	t_list		*current;
	t_sprite	*sprite;

	current = prm->sprite_lst;
	while (current)
	{
		sprite = (t_sprite *)current->content;
		if (sprite->type == 'B')
		{
			print_sprite(prm, sprite->coord, &prm->map.barrel_texture);
		}
		if (sprite->type == 'C')
		{
			print_sprite(prm, sprite->coord, &prm->map.cables_texture);
		}
		if (sprite->type == 'R')
		{
			print_sprite(prm, sprite->coord, &prm->map.front1_texture);
		}
		current = current->next;
	}
}
