/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_if_enclosed_in_walls_utils.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlanza <jlanza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 16:00:47 by jlanza            #+#    #+#             */
/*   Updated: 2023/04/04 16:21:23 by jlanza           ###   ########.fr       */
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
