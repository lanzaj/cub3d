/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_to_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbocquel <mbocquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 18:41:28 by jlanza            #+#    #+#             */
/*   Updated: 2023/04/12 16:10:47 by mbocquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

t_list	*fd_to_lst(t_param *prm, int fd)
{
	t_list	*lst;
	t_list	*new;
	char	*line;

	lst = NULL;
	line = get_next_nonnull_line(prm, fd);
	while (line != NULL)
	{
		new = ft_lstnew(line);
		if (new == NULL)
			fd_to_map_error(prm, fd, "Error\nlstnew is NULL\n");
		garbage_col(prm, 0, new);
		ft_lstadd_back(&lst, new);
		line = get_next_line(fd);
		garbage_col(prm, 0, line);
	}
	return (lst);
}

char	**lst_to_tab(t_param *prm, t_list *lst, int fd)
{
	int		i;
	char	**map;
	t_list	*current;

	if (lst == NULL)
		fd_to_map_error(prm, fd, "Error\nNo map found\n");
	map = ft_calloc_gc(prm, 0, ft_lstsize(lst) + 2, sizeof(*map));
	if (map == NULL)
		fd_to_map_error(prm, fd, "Error\nCalloc failed\n");
	current = lst;
	i = 0;
	while (current != NULL)
	{
		map[i] = ft_strdup_gc(prm, 0, current->content);
		if (map[i] == NULL)
			fd_to_map_error(prm, fd, "Error\nStrdup failed\n");
		trim_backslash_n(map[i]);
		current = current->next;
		i++;
	}
	return (map);
}

static void	check_import_textures_and_colors(t_param *prm, int fd)
{
	if (prm->map.north_texture.img == NULL
		|| prm->map.south_texture.img == NULL
		|| prm->map.east_texture.img == NULL
		|| prm->map.west_texture.img == NULL
		|| prm->map.ceiling_color == -1
		|| prm->map.floor_color == -1)
		fd_to_map_error(prm, fd, "Error\nDuplicate info or info missing\n");
}

void	fd_to_map(t_param *prm, int fd)
{
	t_list	*lst;
	char	*str;
	int		i;

	prm->map.ceiling_color = -1;
	prm->map.floor_color = -1;
	i = 0;
	while (i < 6)
	{
		str = get_next_nonnull_line(prm, fd);
		if (str == NULL)
			fd_to_map_error(prm, fd, "Error\nTexture or color missing\n");
		trim_backslash_n(str);
		str = trim_str(prm, str);
		if (str == NULL)
			fd_to_map_error(prm, fd, "Error\n");
		fd_to_card(prm, fd, str);
		fd_to_color(prm, fd, str);
		i++;
	}
	check_import_textures_and_colors(prm, fd);
	lst = fd_to_lst(prm, fd);
	prm->map.map = lst_to_tab(prm, lst, fd);
}
