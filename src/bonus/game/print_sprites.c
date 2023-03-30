/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_sprites.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlanza <jlanza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 16:01:22 by jlanza            #+#    #+#             */
/*   Updated: 2023/03/30 02:03:20 by jlanza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

/* void	init_col_px(t_param *prm, t_coord wall, double ang, t_px_col *col)
{
	col->px_wall = (prm->height * 3)
		/ (2 * ft_max_d(0.01, get_distance(prm->pos_player, wall) * cos(ang)));
	col->px_cell = (prm->height - ft_min(col->px_wall, prm->height)) / 2;
	col->px_total = 2 * col->px_cell + col->px_wall;
	col->color_cell = prm->map.ceiling_color;
	col->color_floor = prm->map.floor_color;
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
} */

// a partir d'une coord, trouver la colonne de pixel a afficher
/*
soit Xp et Yp les coord du player


*/

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
	//theta = convert_angle(theta);
	//printf("%f \n", convert_angle(-atan2((prm->pos_player.y) - 3.5, prm->pos_player.x - 3.5)));
	//printf("%f %f\n", convert_angle(-atan2((prm->pos_player.y) - 3.5, prm->pos_player.x - 3.5)), theta);
	dx = (tan(prm->view_ang - theta) * prm->width) / (2 * 0.5773502);
	return ((int)nearbyint(dx ));
}
//ang = atan((dx * 2 * 0.5773502) / prm->width);
void	print_column(t_param *prm, double x_sprite, double y_sprite)
{
	int	x;
	int	y;

	x = 0;
	x = get_center_column(prm, x_sprite, y_sprite) + (prm->width / 2);
	if (x < 1 || x >= prm->width)
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

