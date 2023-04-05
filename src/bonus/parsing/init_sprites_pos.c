/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sprites_pos.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlanza <jlanza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 16:55:49 by jlanza            #+#    #+#             */
/*   Updated: 2023/04/04 18:59:27 by jlanza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	add_sprite(t_param *prm, char type, int x, int y)
{
	t_list		*new;
	t_sprite	*content;

	content = ft_calloc_gc(prm, 0, sizeof(t_sprite), 1);
	content->coord.x = (double)x + 0.5;
	content->coord.y = (double)y + 0.5;
	content->type = type;
	new = ft_lstnew(content);
	garbage_col(prm, 0, new);
	ft_lstadd_front(&prm->sprite_lst, new);
}

void	init_sprites(t_param *prm)
{
	int	x;
	int	y;

	y = 0;
	while (prm->map.map[y])
	{
		x = 0;
		while (prm->map.map[y][x])
		{
			if (ft_strchr("BCR", prm->map.map[y][x]))
				add_sprite(prm, prm->map.map[y][x], x, y);
			if (prm->map.map[y][x] == 'C' || prm->map.map[y][x] == 'R')
				prm->map.map[y][x] = '0';
			x++;
		}
		y++;
	}
}