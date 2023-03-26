/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_if_enclosed_in_walls.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlanza <jlanza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 16:00:47 by jlanza            #+#    #+#             */
/*   Updated: 2023/03/26 17:23:08 by jlanza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static int	check_map_error(t_param *prm, char *msg)
{
	ft_printf_fd(2, "%s", msg);
	destroy_images(prm);
	mlx_destroy_window(prm->mlx, prm->win);
	mlx_destroy_display(prm->mlx);
	empty_garbage(prm, -1);
	exit(1);
}

static void	is_first_line_only_wall(t_param *prm, char **map)
{
	int		i;

	i = 0;
	while (map[0][i])
	{
		if (map[0][i] != '1' && map[0][i] != '2')
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
		if (map[last_line][i] != '1' && map[last_line][i] != '2')
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
		if (map[i][0] != '1' && map[i][0] != '2')
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
		if (map[i][last_column] != '1' && map[i][last_column] != '2')
			check_map_error(prm, "Error\nNot enclosed in walls\n");
		i++;
	}
}

static void	is_0_next_to_2(t_param *prm, char **map)
{
	int	i;
	int	j;

	i = 1;
	while (map[i + 1])
	{
		j = 1;
		while (map[i][j + 1])
		{
			if (map[i][j] != '1' && map[i][j] != '2')
			{
				if (map[i - 1][j] == '2'
					|| map[i + 1][j] == '2'
					|| map[i][j - 1] == '2'
					|| map[i][j + 1] == '2')
					check_map_error(prm, "Error\nNot enclosed in walls\n");
			}
			j++;
		}
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
