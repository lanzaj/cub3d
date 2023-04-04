/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_if_enclosed_in_walls_utils.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlanza <jlanza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 16:00:47 by jlanza            #+#    #+#             */
/*   Updated: 2023/04/04 16:18:45 by jlanza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	is_0_next_to_2(t_param *prm, char **map)
{
	int	i;
	int	j;

	i = 1;
	while (map[i + 1])
	{
		j = 1;
		while (map[i][j + 1])
		{
			if (!ft_strchr("123456789", map[i][j]) && map[i][j] != 'M')
			{
				if (map[i - 1][j] == 'M'
					|| map[i + 1][j] == 'M'
					|| map[i][j - 1] == 'M'
					|| map[i][j + 1] == 'M')
					check_map_error(prm, "Error\nNot enclosed in walls\n");
			}
			j++;
		}
		i++;
	}
}
