/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbocquel <mbocquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 18:45:26 by mbocquel          #+#    #+#             */
/*   Updated: 2023/04/07 11:48:13 by mbocquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	move_one_enemy(t_param *prm, t_sprite *sprite)
{
	double	ang;
	double	speed;
	t_coord	move_dir;

	ang = convert_angle(get_angle_with_player_view(prm, sprite->coord) - PI);
	speed = 0.05;
	move_dir = get_wanted_move_dir_enemy(ang);
	if (!(move_dir.x == 0 && move_dir.y == 0) && is_valid_move_enemy(prm,
			sum_vect(sprite->coord, prod_vect(speed, move_dir))))
		sprite->coord = pos_buff_enemy(prm, sum_vect(sprite->coord,
					prod_vect(speed, move_dir)), ang);
	if (!we_are_in_same_room(prm, sprite))
		sprite->follow = FALSE;
}

void	move_all_enemies(t_param *prm)
{
	t_list		*current;
	t_sprite	*sprite;

	current = prm->sprite_lst;
	while (current)
	{
		sprite = (t_sprite *)current->content;
		if (!sprite->dead && sprite->type == 'R' && sprite->follow)
			move_one_enemy(prm, sprite);
		current = current->next;
	}
}

t_bool	is_valid_move_enemy(t_param *prm, t_coord pos)
{
	if (ft_strchr("123456789D", prm->map.map[(int)(pos.y)][(int)(pos.x)]))
		return (FALSE);
	return (TRUE);
}
