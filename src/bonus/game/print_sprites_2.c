/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_sprites_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlanza <jlanza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 11:13:29 by mbocquel          #+#    #+#             */
/*   Updated: 2023/04/13 09:58:19 by jlanza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	kill_baril(t_param *prm, t_sprite *sprite, double theta, int dx)
{
	if (sprite->health == 0 && sprite->type == 'B')
	{
		if (convert_angle(prm->view_ang - theta - PI / 2) >= PI)
			put_img_to_front(prm, &prm->gun.explo[sprite->frame],
				dx, sprite);
		sprite->frame++;
		if (sprite->frame == 7)
		{
			sprite->dead = 1;
			explode(prm, sprite);
		}
		prm->map.map[(int)sprite->coord.y][(int)sprite->coord.x] = '0';
	}
}

void	kill_enemies(t_param *prm, t_sprite *sprite, double theta, int dx)
{
	if (sprite->health == 0 && sprite->type == 'R')
	{
		if (convert_angle(prm->view_ang - theta - PI / 2) >= PI)
			put_img_to_front(prm,
				&prm->map.die_texture[(sprite->frame / 2)], dx, sprite);
		if (sprite->frame < 6)
			sprite->frame++;
		sprite->dead = 1;
	}
}

void	collect_health(t_param *prm, t_sprite *sprite)
{
	if (sprite->type == 'H'
		&& get_distance_square(sprite->coord, prm->pos_player) < 1
		&& prm->n_life != LIFE_NUMBER)
	{
		sprite->dead = 1;
		prm->n_life++;
	}
}

void	print_sprite(t_param *prm, t_sprite *sprite, t_img *xpm)
{
	double	theta;
	int		dx;
	int		seen;

	dx = 0;
	seen = 0;
	theta = get_angle_with_player_view(prm, sprite->coord);
	dx = (int)nearbyint((tan(convert_angle(prm->view_ang - theta))
				* prm->width) / (2 * 0.5773502)) + (prm->width / 2);
	kill_enemies(prm, sprite, theta, dx);
	if (!sprite->dead && convert_angle(prm->view_ang - theta - PI / 2) >= PI)
		seen = put_img_to_front(prm, xpm, dx, sprite);
	ai_enemies(prm, sprite, seen);
	do_gun_damage(prm, sprite, dx, seen);
	kill_baril(prm, sprite, theta, dx);
	collect_health(prm, sprite);
	if (sprite->red_color > 0)
		sprite->red_color -= 80;
	if (sprite->red_color < 0)
	{
		sprite->red_color = 0;
		if (sprite->type == 'R' && sprite->health == 0)
			prm->nbr_enemies--;
	}
}

void	select_sprite(t_param *prm, t_sprite *sprite)
{
	if (sprite->type == 'B' && !sprite->dead)
		print_sprite(prm, sprite, &prm->map.barrel_texture);
	if (sprite->type == 'C')
		print_sprite(prm, sprite, &prm->map.cables_texture);
	if (sprite->type == 'R')
	{
		if (sprite->follow)
			print_sprite(prm, sprite,
				&prm->map.front_texture[prm->frame / 4 % 4]);
		else if (sprite->ok_to_shoot)
			print_sprite(prm, sprite,
				&prm->map.attack_texture[prm->frame / 4 % 4]);
		else
			print_sprite(prm, sprite, &prm->map.front_texture[0]);
	}
	if (sprite->type == 'H' && !sprite->dead)
		print_sprite(prm, sprite, &prm->map.health_texture);
}
