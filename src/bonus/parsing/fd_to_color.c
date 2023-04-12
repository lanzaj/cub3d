/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_to_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbocquel <mbocquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 23:06:52 by jlanza            #+#    #+#             */
/*   Updated: 2023/04/12 14:10:48 by mbocquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static int	get_number(int *n, int i, char *str)
{
	if (ft_isint(&str[i]))
		*n = ft_atoi(&str[i]);
	else
		return (1);
	if (*n > 255 || *n < 0)
		return (1);
	return (0);
}

static int	get_next_number_pos(int *i, char *str)
{
	while (ft_isdigit((int)str[*i]))
		(*i)++;
	if (str[*i] == ',')
		(*i)++;
	else
		return (1);
	return (0);
}

static int	import_color(int *color_element, char *str)
{
	int	r;
	int	g;
	int	b;
	int	i;

	i = 0;
	if (get_number(&r, i, str) || get_next_number_pos(&i, str))
		return (1);
	if (get_number(&g, i, str) || get_next_number_pos(&i, str))
		return (1);
	if (get_number(&b, i, str))
		return (1);
	while (ft_isdigit(str[i]))
		i++;
	if (str[i] != '\0')
		return (1);
	*color_element = create_trgb(0, (unsigned char)r, (unsigned char)g,
			(unsigned char)b);
	return (0);
}

void	fd_to_color(t_param *prm, int fd, char *str)
{
	if (!str || ft_strlen(str) < 5)
		fd_to_map_error(prm, fd, "Error\nInvalid line\n");
	if (!ft_strncmp(str, "F", 1) && prm->map.floor_color == -1
		&& import_color(&(prm->map.floor_color), &str[1]))
		fd_to_map_error(prm, fd, "Error\nInvalid floor color\n");
	if (!ft_strncmp(str, "C", 1) && prm->map.ceiling_color == -1
		&& import_color(&(prm->map.ceiling_color), &str[1]))
		fd_to_map_error(prm, fd, "Error\nInvalid ceiling color\n");
}
