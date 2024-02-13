/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlanza <jlanza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 12:56:32 by jlanza            #+#    #+#             */
/*   Updated: 2023/03/24 12:57:12 by jlanza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	count_number_of_lines(char **map)
{
	int	i;

	i = 0;
	while (map[i])
		i++;
	return (i);
}

int	count_max_width_of_lines(char **map)
{
	int		i;
	size_t	max_len;

	i = 0;
	max_len = 0;
	while (map[i])
	{
		if (ft_strlen(map[i]) > max_len)
			max_len = ft_strlen(map[i]);
		i++;
	}
	return (max_len);
}
