/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbocquel <mbocquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 10:50:47 by mbocquel          #+#    #+#             */
/*   Updated: 2023/03/17 15:44:15 by mbocquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	garbage_split(t_param *prm, int id, char **strs)
{
	int	i;

	i = 0;
	while (strs[i])
	{
		garbage_col(prm, id, (void *)(strs[i]));
		i++;
	}
	garbage_col(prm, id, (void *)strs);
}
