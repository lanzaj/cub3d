/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlanza <jlanza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 11:59:17 by mbocquel          #+#    #+#             */
/*   Updated: 2023/03/26 17:19:24 by jlanza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	get_nb_str(char **strs)
{
	int	i;

	i = 0;
	if (strs == NULL)
		return (0);
	while (strs[i])
		i++;
	return (i);
}

void	ft_swap(int *a, int *b)
{
	int	new_value_a;

	new_value_a = *b;
	*b = *a;
	*a = new_value_a;
}

void	print_map(t_param *prm)
{
	int	row;
	int	col;

	row = 0;
	while (prm->map.map && prm->map.map[row])
	{
		col = 0;
		while (prm->map.map[row][col])
		{
			ft_printf("%c", prm->map.map[row][col]);
			col++;
		}
		ft_printf("\n");
		row++;
	}
}
