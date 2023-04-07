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

static int	case_pos_buff_enemy(t_param *prm, double ang_move,
	t_coord pos, double buf)
{
	if (ang_move > 0 && ang_move < PI
		&& ft_strchr("123456789BD",
			prm->map.map[(int)(pos.y) - 1][(int)(pos.x)])
			&& pos.y - (int)(pos.y) < buf)
		return (1);
	if (ang_move > PI && ang_move < 2 * PI
		&& ft_strchr("123456789BD",
			prm->map.map[(int)(pos.y) + 1][(int)(pos.x)])
			&& (int)(pos.y) + 1 - pos.y < buf)
		return (2);
	return (3);
}

static t_coord	pos_buff_enemy(t_param *prm, t_coord pos, double ang_move)
{
	t_coord	new_pos;

	new_pos = pos;
	if (case_pos_buff_enemy(prm, ang_move, pos, BUF) == 1)
		new_pos.y = (int)(pos.y) + BUF;
	if (case_pos_buff_enemy(prm, ang_move, pos, BUF) == 2)
		new_pos.y = (int)(pos.y) + 1 - BUF;
	if ((ang_move > (3 * PI) / 2 || ang_move < PI / 2)
		&& ft_strchr("123456789BD",
			prm->map.map[(int)(pos.y)][(int)(pos.x) + 1])
			&& (int)(pos.x) + 1 - pos.x < BUF)
		new_pos.x = (int)(pos.x + 1) - BUF;
	if (ang_move > PI / 2 && ang_move < (3 * PI) / 2
		&& ft_strchr("123456789BD",
			prm->map.map[(int)(pos.y)][(int)(pos.x) - 1])
			&& pos.x - (int)(pos.x) < BUF)
		new_pos.x = (int)pos.x + BUF;
	return (new_pos);
}

static t_coord	get_wanted_move_dir_enemy_p2(double ang, t_coord *coord)
{
	if (ang > PI / 2 && ang < PI)
	{
		coord->x = -cos(PI - ang);
		coord->y = -sin(PI - ang);
	}
	if (ang > PI && ang < 3 * PI / 2)
	{
		coord->x = -cos(ang - PI);
		coord->y = sin(ang - PI);
	}
	if (ang > 3 * PI / 2 && ang < 2 * PI)
	{
		coord->x = cos(2 * PI - ang);
		coord->y = sin(2 * PI - ang);
	}
	return (*coord);
}

static t_coord	get_wanted_move_dir_enemy(double ang)
{
	t_coord	coord;

	ft_memset(&coord, 0, sizeof(t_coord));
	if (ang == 0)
		coord.x = 1;
	if (ang == PI)
		coord.x = -1;
	if (ang == PI / 2)
		coord.y = -1;
	if (ang == 3 * PI / 2)
		coord.y = 1;
	if (ang > 0 && ang < PI / 2)
	{
		coord.x = cos(ang);
		coord.y = -sin(ang);
	}
	return (get_wanted_move_dir_enemy_p2(ang, &coord));
}

/*static int	is_valid_move_enemy(t_param *prm, t_coord pos)
{
	double	lrg;

	lrg = 0.875;
	if (pos.x - (double)((int)pos.x) < 0.5
		&& pos.y - (double)((int)pos.y) < 0.5
		&& (ft_strchr("123456789D", prm->map.map[(int)(pos.y)][(int)(pos.x)])
			|| ft_strchr("123456789D",
				prm->map.map[(int)(pos.y - lrg)][(int)(pos.x)])
			|| ft_strchr("123456789D",
				prm->map.map[(int)(pos.y - lrg)][(int)(pos.x - lrg)])
			|| ft_strchr("123456789D",
				prm->map.map[(int)(pos.y)][(int)(pos.x - lrg)])))
	{
		printf("block cas 1\n");
		return (0);
	}
	if (pos.x - (double)((int)pos.x) >= 0.5
		&& pos.y - (double)((int)pos.y) < 0.5
		&& (ft_strchr("123456789D", prm->map.map[(int)(pos.y)][(int)(pos.x)])
			|| ft_strchr("123456789D",
				prm->map.map[(int)(pos.y)][(int)(pos.x + lrg)])
			|| ft_strchr("123456789D",
				prm->map.map[(int)(pos.y - lrg)][(int)(pos.x + lrg)])
			|| ft_strchr("123456789D",
				prm->map.map[(int)(pos.y - lrg)][(int)(pos.x)])))
	{
		printf("block cas 2\n");
		return (0);
	}
	if (pos.x - (double)((int)pos.x) >= 0.5
		&& pos.y - (double)((int)pos.y) >= 0.5
		&& (ft_strchr("123456789D", prm->map.map[(int)(pos.y)][(int)(pos.x)])
			|| ft_strchr("123456789D",
				prm->map.map[(int)(pos.y)][(int)(pos.x + lrg)])
			|| ft_strchr("123456789D",
				prm->map.map[(int)(pos.y + lrg)][(int)(pos.x + lrg)])
			|| ft_strchr("123456789D",
				prm->map.map[(int)(pos.y + lrg)][(int)(pos.x)])))
	{
		printf("block cas 3\n");
		return (0);
	}
	if (pos.x - (double)((int)pos.x) < 0.5
		&& pos.y - (double)((int)pos.y) >= 0.5
		&& (ft_strchr("123456789D", prm->map.map[(int)(pos.y)][(int)(pos.x)])
			|| ft_strchr("123456789D",
				prm->map.map[(int)(pos.y + lrg)][(int)(pos.x)])
			|| ft_strchr("123456789D",
				prm->map.map[(int)(pos.y + lrg)][(int)(pos.x - lrg)])
			|| ft_strchr("123456789D",
				prm->map.map[(int)(pos.y)][(int)(pos.x - lrg)])))
	{
		printf("block cas 4\n");
		return (0);
	}
	return (1);
}*/

static int	is_valid_move_enemy(t_param *prm, t_coord pos)
{
	if (ft_strchr("123456789D", prm->map.map[(int)(pos.y)][(int)(pos.x)]))
		return (0);
	return (1);
}

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
		sprite->coord = pos_buff_enemy(prm, 
				sum_vect(sprite->coord, prod_vect(speed, move_dir)), ang);
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
