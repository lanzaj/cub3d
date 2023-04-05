/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_sprites.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbocquel <mbocquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 16:01:22 by jlanza            #+#    #+#             */
/*   Updated: 2023/04/05 14:49:18 by mbocquel         ###   ########.fr       */
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

static void	put_img_to_front(t_param *prm, t_img *xpm, int dx, t_coord sprite)
{
	t_point		pixel;
	t_coord_int	i;
	t_coord_int	start;
	t_px_col	col;

	init_col_px_sprite(prm, sprite, &col);
	start.x = dx - (col.px_wall / 2);
	start.y = col.px_cell;
	i.x = start.x;
	if (i.x < 0)
		i.x = 0;
	while (i.x < col.px_wall + start.x && i.x >= 0 && i.x < prm->width)
	{
		i.y = start.y;
		if (check_distance_x(prm, sprite, i))
		{
			while (i.y < col.px_wall + start.y && i.y >= 0 && i.y < prm->height)
			{
				pixel.color = get_color(xpm,
						(i.x - start.x) * xpm->width / (col.px_wall),
						(i.y - start.y + (col.ofset))
						* xpm->height / (col.px_wall));
				pixel.x = i.x;
				pixel.y = i.y;
				if (check_distance_y(prm, sprite, i))
					pixel_put_img(&(prm->layer.front), pixel);
				i.y++;
			}
		}
		i.x++;
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
