/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_in_room.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlanza <jlanza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 12:15:10 by mbocquel          #+#    #+#             */
/*   Updated: 2023/04/13 10:56:54 by jlanza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	replace_char(char *str, char *charset)
{
	int	i;

	if (!charset)
		return ;
	i = 0;
	while (str && str[i])
	{
		if (ft_strchr(charset, str[i]))
			str[i] = '0';
		i++;
	}
}

char	**dup_map(t_param *prm)
{
	char	**map_copy;
	int		i;

	map_copy = ft_calloc_gc(prm, 0, prm->map.map_height + 1, sizeof(char *));
	if (map_copy == NULL)
		ft_exit_error(prm, 1);
	i = 0;
	while (prm->map.map[i])
	{
		map_copy[i] = ft_strdup_gc(prm, 0, prm->map.map[i]);
		if (map_copy[i] == NULL)
			ft_exit_error(prm, 1);
		replace_char(map_copy[i], "RWESN");
		i++;
	}
	return (map_copy);
}

void	flood(t_param *prm, char **map, int y, int x)
{
	if (ft_strchr("123456789DF", map[y][x]))
		return ;
	map[y][x] = 'F';
	if (x + 1 < prm->map.map_width)
		flood(prm, map, y, x + 1);
	if (x - 1 >= 0)
		flood(prm, map, y, x - 1);
	if (y + 1 < prm->map.map_height)
		flood(prm, map, y + 1, x);
	if (y - 1 >= 0)
		flood(prm, map, y - 1, x);
}

t_bool	player_not_in_map(char **map)
{
	int	x;
	int	y;

	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == 'P')
				return (FALSE);
			x++;
		}
		y++;
	}
	return (TRUE);
}

t_bool	we_are_in_same_room(t_param *prm, t_sprite *sprite)
{
	char	**map_copy;
	t_bool	answer;
	int		i;

	i = -1;
	if ((int)sprite->coord.x == (int)prm->pos_player.x
		&& (int)sprite->coord.y == (int)prm->pos_player.y)
		return (TRUE);
	map_copy = dup_map(prm);
	map_copy[(int)prm->pos_player.y][(int)prm->pos_player.x] = 'P';
	flood(prm, map_copy, (int)sprite->coord.y, (int)sprite->coord.x);
	answer = player_not_in_map(map_copy);
	while (map_copy[++i])
		remove_from_garb(prm, map_copy[i]);
	remove_from_garb(prm, map_copy);
	return (answer);
}
