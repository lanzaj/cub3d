/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_if_enclosed_in_walls.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbocquel <mbocquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 16:00:47 by jlanza            #+#    #+#             */
/*   Updated: 2023/04/05 14:52:18 by mbocquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	is_first_line_only_wall(t_param *prm, char **map)
{
	int		i;

	i = 0;
	while (map[0][i])
	{
		if (!ft_strchr("123456789", map[0][i]) && map[0][i] != 'M')
			check_map_error(prm, "Error\nNot enclosed in walls\n");
		i++;
	}
}

static void	is_last_line_only_wall(t_param *prm, char **map)
{
	int		i;
	int		last_line;

	last_line = count_number_of_lines(map) - 1;
	i = 0;
	while (map[last_line][i])
	{
		if (!ft_strchr("123456789", map[last_line][i])
			&& map[last_line][i] != 'M')
			check_map_error(prm, "Error\nNot enclosed in walls\n");
		i++;
	}
}

static void	is_first_column_only_wall(t_param *prm, char **map)
{
	int	i;

	i = 0;
	while (map[i])
	{
		if (!ft_strchr("123456789", map[i][0]) && map[i][0] != 'M')
			check_map_error(prm, "Error\nNot enclosed in walls\n");
		i++;
	}
}

static void	is_last_column_only_wall(t_param *prm, char **map)
{
	int		i;
	size_t	last_column;

	last_column = ft_strlen(map[0]) - 1;
	i = 0;
	while (map[i])
	{
		if (!ft_strchr("123456789", map[i][last_column])
			&& map[i][last_column] != 'M')
			check_map_error(prm, "Error\nNot enclosed in walls\n");
		i++;
	}
}

void	check_if_enclosed_in_walls(t_param *prm, char **map)
{
	is_first_line_only_wall(prm, map);
	is_last_line_only_wall(prm, map);
	is_first_column_only_wall(prm, map);
	is_last_column_only_wall(prm, map);
	is_0_next_to_2(prm, map);
}
