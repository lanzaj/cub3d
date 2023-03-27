/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlanza <jlanza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 15:52:52 by jlanza            #+#    #+#             */
/*   Updated: 2023/03/27 14:46:06 by jlanza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	search_and_replace(char *str, char dest, char src)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == src)
			str[i] = dest;
		i++;
	}
}

static void	make_map_rectangular(t_param *prm, char **map)
{
	int		i;
	char	*str;

	i = 0;
	while (map[i])
	{
		if ((int)ft_strlen(map[i]) != prm->map.map_width)
		{
			str = ft_calloc_gc(prm, 0, prm->map.map_width + 1, sizeof(char));
			ft_memset(str, '2', prm->map.map_width);
			ft_memcpy(str, map[i], sizeof(char) * ft_strlen(map[i]));
			map[i] = str;
		}
		search_and_replace(map[i], '2', ' ');
		i++;
	}
}

static void	check_charset(t_param *prm, char **map)
{
	int		i;
	int		j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (!ft_strchr("01NSEW", map[i][j]))
				check_map_error(prm, "Error\nInvalid character\n");
			j++;
		}
		i++;
	}
	(void)prm;
}

void	check_map(t_param *prm, char **map)
{
	check_charset(prm, map);
	make_map_rectangular(prm, map);
	check_if_enclosed_in_walls(prm, map);
}
