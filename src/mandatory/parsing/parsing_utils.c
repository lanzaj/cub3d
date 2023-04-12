/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbocquel <mbocquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 14:29:53 by jlanza            #+#    #+#             */
/*   Updated: 2023/04/12 16:13:21 by mbocquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	get_nb_space_end(char *str)
{
	int	i;
	int	count;

	if (!str)
		return (0);
	count = 0;
	i = ft_strlen(str) - 1;
	while (i >= 0 && ft_isspace(str[i]))
	{
		count++;
		i--;
	}
	return (count);
}

char	*trim_str(t_param *prm, char *str)
{
	int		i;
	int		j;
	int		space_end;
	char	*new_str;

	new_str = ft_strdup_gc(prm, 0, str);
	if (new_str == NULL)
		return (NULL);
	i = 0;
	j = 0;
	space_end = get_nb_space_end(str);
	while (str && str[i] && ft_isspace(str[i]))
		i++;
	while (str && str[i])
	{
		new_str[j] = str[i];
		i++;
		j++;
	}
	new_str[j - space_end] = '\0';
	return (new_str);
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
