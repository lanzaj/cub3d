/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_sprites.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlanza <jlanza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 16:01:22 by jlanza            #+#    #+#             */
/*   Updated: 2023/04/02 23:01:28 by jlanza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
/*

void	print_game(t_param *prm)
{
	int		x;
	t_coord	wall;
	double	ang;
	int		dx;

	x = prm->width / 2;
	dx = 0;
	while (x - dx > 0)
	{
		ang = atan((dx * 2 * 0.5773502) / prm->width);
		wall = find_wall(prm, convert_angle(prm->view_ang + ang));
		print_wall_slice(prm, x - dx, wall, ang);
		dx++;
	}
	dx = 0;
	while (x + dx < prm->width)
	{
		ang = atan((dx * 2 * 0.5773502) / prm->width);
		wall = find_wall(prm, convert_angle(prm->view_ang - ang));
		print_wall_slice(prm, x + dx, wall, ang);
		dx++;
	}
} */
///////////// get color //////////////////////
/* double	pos_impact(t_param *prm, t_coord point)
{
	if (!is_valid_coord(prm, point))
		return (-1);
	if (point.y == (int)point.y
		&& prm->map.map[(int)point.y][(int)point.x] == '1')
		return (1 - (point.x - (double)((int)point.x)));
	if (point.y == (int)point.y
		&& ((int)point.y - 1 >= 0
			&& prm->map.map[(int)point.y - 1][(int)point.x] == '1'))
		return ((point.x - (double)((int)point.x)));
	if (point.x == (int)point.x
		&& prm->map.map[(int)point.y][(int)point.x] == '1')
		return (point.y - (double)((int)point.y));
	if (point.x == (int)point.x
		&& ((int)point.x - 1 >= 0
			&& prm->map.map[(int)point.y][(int)point.x - 1] == '1'))
		return (1 - (point.y - (double)((int)point.y)));
	return (0);
}
*/

/* int	get_texture_px_color(t_param *prm, t_coord wall, double pos_y)
{
	int		px_x;
	int		px_y;
	t_img	*xpm;

	xpm = &(prm->map.west_texture);
	px_x = (int)(pos_impact(prm, wall) * (double)xpm->width);
	px_y = (int)(pos_y * (double)xpm->height);
	if (px_x < 0 || px_x > xpm->width || px_y < 0 || px_y > xpm->height)
		return (-1);
	return (*(int *)(xpm->addr + (px_x * (xpm->bits_per_pixel / 8)
			+ px_y * xpm->line_length)));
} */

int get_color(t_img *xpm, int x, int y)
{
	if (x < 0 || x >= xpm->width || y < 0 || y >= xpm->height)
		return (-1);
	return (*(int *)(xpm->addr + (x * (xpm->bits_per_pixel / 8) + y * xpm->line_length)));
}

int	get_color_sprite(t_param *prm, t_px_col col, int y, t_coord wall)
{
	int		y_bis;
	double	pos_v_in_wall;

	y_bis = y + col.ofset;
	if (y_bis < col.px_cell)
		return (col.color_cell);
	if (y_bis >= col.px_cell + col.px_wall)
		return (col.color_floor);
	pos_v_in_wall = (double)(y_bis - col.px_cell) / (double)col.px_wall;
	return (get_texture_px_color(prm, wall, pos_v_in_wall));
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

/* void	print_wall_slice(t_param *prm, int x, t_coord wall, double ang)
{
	int			y;
	t_px_col	col;

	init_col_px(prm, wall, ang, &col);
	y = 1;
	while (x > 0 && x < prm->width && y < prm->height)
	{
		my_mlx_pixel_put(&(prm->layer.front), x, y,
			get_color_px(prm, col, y, wall));
		y++;
	}
} */

// a partir d'une coord, trouver la colonne de pixel a afficher
/*
soit Xp et Yp les coord du player

*/
void	pixel_put_img(t_img *img, t_point pixel)
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

/* return la couleur d'un pixel a une position*/


void	put_img_to_front(t_param *prm, t_img *xpm, t_coord_int screen, t_coord sprite)
{
	t_point		pixel;
	t_coord_int	i;
	t_coord_int	start;
	t_px_col	col;

// screen.x est le centre de la colonne du sprite
// screen.y est le decalage haut bas

	init_col_px_sprite(prm, sprite, &col);
	start.x = screen.x - (col.px_wall / 2);
	start.y = col.px_cell + screen.y;
	i.y = start.y;
	while (i.y < col.px_wall + start.y)
	{
		i.x = start.x;
		while (i.x < col.px_wall + start.x)
		{
			pixel.color = get_color(xpm, (i.x - start.x) * xpm->width / (col.px_wall) , (i.y - start.y) * xpm->height / (col.px_cell));
			pixel.x = i.x;
			pixel.y = i.y;
			pixel_put_img(&(prm->layer.front), pixel);
			i.x++;
		}
		i.y++;
	}
	(void)xpm;
}

double	get_angle_with_player_view(t_param *prm, double x_sprite, double y_sprite)
{
	return (convert_angle(-atan2((y_sprite - prm->pos_player.y), (x_sprite - prm->pos_player.x))));
}

int	get_center_column(t_param *prm, double x_sprite, double y_sprite)
{
	double	dx;
	double	theta;
	t_coord	wall;

	theta = get_angle_with_player_view(prm, x_sprite, y_sprite);
	wall = find_wall(prm, theta);
	put_segment_img(&prm->mini_map, get_minimap_pos(prm, prm->pos_player, 0x00000000), get_minimap_pos(prm, wall, 0x00000000));
	dx = (tan(convert_angle(prm->view_ang - theta)) * prm->width) / (2 * 0.5773502);
	if (convert_angle(prm->view_ang - theta - PI / 2) < PI)
		dx = -prm->width;
	return ((int)nearbyint(dx));
}

void	print_column(t_param *prm, double x_sprite, double y_sprite)
{
	t_coord_int	screen;
	t_coord		sprite;

	sprite.x = x_sprite;
	sprite.y = y_sprite;
	screen.x = 0;
	screen.x = get_center_column(prm, x_sprite, y_sprite) + (prm->width / 2);
	screen.y = 0;
	put_img_to_front(prm, &prm->map.east_texture, screen, sprite);
}

/* fonction qui permet de connaitre la taille d'un mur
col->px_wall = (prm->height * 3)
		/ (2 * ft_max_d(0.01, get_distance(prm->pos_player, wall) * cos(ang)));*/

/* trouver le mur le plus proche
wall = find_wall(prm, convert_angle(prm->view_ang + ang));*/

/* recuperer la distance entre le wall et le player
get_distance(prm->pos_player, wall)*/


// imprimer une image dont le centre est la center column

