/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_sprites.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlanza <jlanza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 16:01:22 by jlanza            #+#    #+#             */
/*   Updated: 2023/03/31 14:59:59 by jlanza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	init_col_px(t_param *prm, t_coord wall, double ang, t_px_col *col)
{
	col->px_wall = (prm->height * 3)
		/ (2 * ft_max_d(0.01, get_distance(prm->pos_player, wall) * cos(ang)));
	col->px_cell = (prm->height - ft_min(col->px_wall, prm->height)) / 2;
	col->px_total = 2 * col->px_cell + col->px_wall;
	col->color_cell = prm->map.ceiling_color; // couleur ciel
	col->color_floor = prm->map.floor_color; // couleur sol
	col->ofset = (ft_max(0, (col->px_total - prm->height) / 2));
}

void	print_wall_slice(t_param *prm, int x, t_coord wall, double ang)
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
}

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
}
///////////// get color //////////////////////
double	pos_impact(t_param *prm, t_coord point)
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

int	get_texture_px_color(t_param *prm, t_coord wall, double pos_y)
{
	int		px_x;
	int		px_y;
	t_dir	dir;
	t_img	*xpm;

	dir = has_hit_a_wall(prm, wall);
	if (dir == SOUTH)
		xpm = &(prm->map.south_texture);
	else if (dir == NORTH)
		xpm = &(prm->map.north_texture);
	else if (dir == EAST)
		xpm = &(prm->map.east_texture);
	else
		xpm = &(prm->map.west_texture);
	px_x = (int)(pos_impact(prm, wall) * (double)xpm->width);
	px_y = (int)(pos_y * (double)xpm->height);
	if (px_x < 0 || px_x > xpm->width || px_y < 0 || px_y > xpm->height)
		return (-1);
	return (*(int *)(xpm->addr + (px_x * (xpm->bits_per_pixel / 8)
			+ px_y * xpm->line_length)));
}

int	get_color_px(t_param *prm, t_px_col col, int y, t_coord wall)
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


// a partir d'une coord, trouver la colonne de pixel a afficher
/*
soit Xp et Yp les coord du player

*/
void	pixel_put_front_layer(t_param *prm, t_point pixel)
{
	char	*dst;

	if (!(pixel.x < 0 || pixel.x >= (*prm).layer.front.width || pixel.y < 0
			|| pixel.y >= (*prm).layer.front.height
			|| pixel.color == -1 || get_t(pixel.color) == 255))
	{
		dst = (*prm).layer.front.addr
			+ (pixel.y * (*prm).layer.front.line_length
				+ pixel.x * ((*prm).layer.front.bits_per_pixel / 8));
		*(unsigned int *)dst = pixel.color;
	}
}

// besoin de coord, besoin de couleur, de distance et de deplacement vertical
void	put_img_to_front(t_param *prm, t_img *xpm, t_point screen, double scale)
{
	t_point	img;

	img.y = screen.y;
	while (img.y < xpm->height + screen.y)
	{
		img.x = screen.x;
		while (img.x < xpm->width + screen.x)
		{
			img.color = get_color(xpm, img.x - screen.x, img.y - screen.y);
			pixel_put_front_layer(prm, img);
			img.x++;
		}
		img.y++;
	}
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
	printf("\r%f", convert_angle(prm->view_ang - theta - PI / 2));
	if (convert_angle(prm->view_ang - theta - PI / 2) < PI)
	{
		printf("\r%f toto", convert_angle(prm->view_ang - theta - PI / 2));
		dx = -prm->width;
	}
	return ((int)nearbyint(dx));
}
//ang = atan((dx * 2 * 0.5773502) / prm->width);
void	print_column(t_param *prm, double x_sprite, double y_sprite)
{
	int	x;
	int	y;

	x = 0;
	x = get_center_column(prm, x_sprite, y_sprite) + (prm->width / 2);
	if (x < 0 || x >= prm->width)
		return ;
	y = 0;
	while (y < prm->height)
	{
		my_mlx_pixel_put(&(prm->layer.front), x, y, 0x00FFFFFF);
		y++;
	}
}

/* fonction qui permet de connaitre la taille d'un mur
col->px_wall = (prm->height * 3)
		/ (2 * ft_max_d(0.01, get_distance(prm->pos_player, wall) * cos(ang)));*/

/* trouver le mur le plus proche
wall = find_wall(prm, convert_angle(prm->view_ang + ang));*/

/* recuperer la distance entre le wall et le player
get_distance(prm->pos_player, wall)*/


// imprimer une image dont le centre est la center column

