/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbocquel <mbocquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 14:29:53 by jlanza            #+#    #+#             */
/*   Updated: 2023/04/12 13:44:15 by mbocquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	trim_str(char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str && str[i])
	{
		if (!ft_isspace(str[i]) && str[i] != '\\')
		{
			str[j] = str[i];
			j++;
		}
		if (str[i] == '\\')
		{
			if (str[i + 1] && ft_isspace(str[i + 1]))
			{
				str[j] = ' ';
				j++;
				i++;
			}
		}
		i++;
	}
	str[j] = '\0';
}

void	trim_backslash_n(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] == '\n')
			str[i] = '\0';
		i++;
	}
}
