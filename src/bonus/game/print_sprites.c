/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_sprites.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbocquel <mbocquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 16:01:22 by jlanza            #+#    #+#             */
/*   Updated: 2023/04/05 15:14:31 by mbocquel         ###   ########.fr       */
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

static void	put_img_to_front(t_param *prm, t_img *xpm, int dx, t_coord sprite)
{
	t_point		pixel;
	t_boundary	b;

	init_col_px_sprite(prm, sprite, &b.col);
	init_boundary(prm, xpm, &b, dx);
	while (b.i.x < b.stop.x - b.offset_stop.x && b.i.x >= 0 && b.i.x < prm->width)
	{
		b.i.y = b.start.y + b.offset_start.y;
		if (check_distance_x(prm, sprite, b.i))
		{
			while (b.i.y < b.stop.y - b.offset_stop.y && b.i.y >= 0 && b.i.y < prm->height)
			{
				pixel.color = get_color(xpm,
						(b.i.x - b.start.x) * xpm->width / (b.col.px_wall),
						(b.i.y - b.start.y + (b.col.ofset))
						* xpm->height / (b.col.px_wall));
				pixel.x = b.i.x;
				pixel.y = b.i.y;
				if (check_distance_y(prm, sprite, b.i))
					pixel_put_img(&(prm->layer.front), pixel);
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
	//t_coord	wall;
	int		dx;

	dx = 0;
	theta = get_angle_with_player_view(prm, sprite);
	//wall = find_wall(prm, theta);
	/*put_segment_img(&prm->mini_map, get_minimap_pos(prm, prm->pos_player,
			0x00000000), get_minimap_pos(prm, wall, 0x00000000));*/
	dx = (int)nearbyint((tan(convert_angle(prm->view_ang - theta))
				* prm->width) / (2 * 0.5773502)) + (prm->width / 2);
	if (convert_angle(prm->view_ang - theta - PI / 2) >= PI)
		put_img_to_front(prm, xpm, dx, sprite);
}

void	ft_memswap(void **a, void **b)
{
	void	*tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

void		ft_lstsort(t_param *prm, t_list *lst, int (*fcmp)(t_param *prm, t_list *a, t_list *b))
{
	t_list		*start;
	char		not_sorted;

	not_sorted = 1;
	if (!lst)
		return ;
	start = lst;
	while (not_sorted)
	{
		not_sorted = 0;
		lst = start;
		while (lst->next)
		{
			if (fcmp(prm, lst, lst->next) > 0)
			{
				not_sorted = 1;
				ft_memswap(&(lst->content), &(lst->next->content));
			}
			lst = lst->next;
		}
	}
}

int	cmp_distance(t_param *prm, t_list *a, t_list *b)
{
	return (get_distance(prm->pos_player,
			((t_sprite *)a->content)->coord) < get_distance(prm->pos_player,
			((t_sprite *)b->content)->coord));
}

void	print_every_sprite(t_param *prm)
{
	t_list		*current;
	t_sprite	*sprite;

	current = prm->sprite_lst;
	ft_lstsort(prm, current, &cmp_distance);
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
