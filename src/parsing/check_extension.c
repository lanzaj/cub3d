/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_extension.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlanza <jlanza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 23:00:09 by jlanza            #+#    #+#             */
/*   Updated: 2023/03/26 23:00:13 by jlanza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	check_extension(char *file_name)
{
	int	i;

	if (file_name == NULL || ft_strlen(file_name) <= 4)
		return (0);
	i = 0;
	while (file_name[i])
		i++;
	if (file_name[i - 5] == '/' || file_name[i - 4] != '.'
		|| file_name[i - 3] != 'c' || file_name[i - 2] != 'u'
		|| file_name[i - 1] != 'b')
		return (0);
	return (1);
}
