/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initiate_game.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbocquel <mbocquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 16:15:55 by mbocquel          #+#    #+#             */
/*   Updated: 2023/03/22 18:41:35 by mbocquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	initiate_img_game(t_param *prm)
{
	prm->layer.front.img = mlx_new_image(prm->mlx, prm->width,
			prm->height);
	prm->layer.front.addr = mlx_get_data_addr(prm->layer.front.img,
			&(prm->layer.front.bits_per_pixel), &(prm->layer.front.line_length),
			&(prm->layer.front.endian));
}

int	get_wall_color(t_param *prm, t_coord coord)
{
	if (has_hit_a_wall(prm, coord) == 1)
		return (create_trgb(0, 190, 51, 138));
	if (has_hit_a_wall(prm, coord) == 2)
		return (create_trgb(0, 190, 175, 41));
	if (has_hit_a_wall(prm, coord) == 3)
		return (create_trgb(0, 35, 91, 225));
	if (has_hit_a_wall(prm, coord) == 4)
		return (create_trgb(0, 140, 65, 73));
	return (0);
}

int	ft_max(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}

int	ft_min(int a, int b)
{
	if (a < b)
		return (a);
	return (b);
}

double	ft_max_d(double a, double b)
{
	if (a > b)
		return (a);
	return (b);
}

double	ft_min_d(double a, double b)
{
	if (a < b)
		return (a);
	return (b);
}

void	print_wall_slice(t_param *prm, int x, t_coord wall, double ang)
{
	int			y;
	t_px_col	col;

	col.px_wall = (prm->height * 4)
		/ (2 * ft_max_d(0.001, get_distance(prm->pos_player, wall) * cos(ang)));
	col.px_cell = (prm->height - ft_min(col.px_wall, prm->height)) / 2;
	col.px_total = 2 * col.px_cell + col.px_wall;
	col.color_cell = create_trgb(0, 116, 208, 241);
	col.color_floor = create_trgb(0, 87, 213, 59);
	col.ofset = (ft_max(0, (col.px_total - prm->height) / 2));
	y = -col.ofset;
	while (x > 0 && x < prm->width && ++y < col.px_cell)
	{
		if (y > 0 && y < prm->height)
			my_mlx_pixel_put(&(prm->layer.front), x, y, col.color_cell);
	}
	while (x > 0 && x < prm->width && y < col.px_cell + col.px_wall)
	{
		if (y > 0 && y < prm->height)
			my_mlx_pixel_put(&(prm->layer.front), x, y,
				get_wall_color(prm, wall));
		y++;
	}
	while (x > 0 && x < prm->width && y < prm->height)
	{
		if (y > 0 && y < prm->height)
			my_mlx_pixel_put(&(prm->layer.front), x, y, col.color_floor);
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
		ang = atan((dx * 0.5773502) / 1280);
		wall = find_wall(prm, convert_angle(prm->view_ang + ang));
		print_wall_slice(prm, x - dx, wall, ang);
		dx++;
	}
	dx = 0;
	while (x + dx < prm->width)
	{
		ang = atan((dx * 0.5773502) / 1280);
		wall = find_wall(prm, convert_angle(prm->view_ang - ang));
		print_wall_slice(prm, x + dx, wall, ang);
		dx++;
	}
	mlx_put_image_to_window(prm->mlx, prm->win, prm->layer.front.img, 0, 0);
}
