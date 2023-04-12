/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_to_map_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbocquel <mbocquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 11:33:14 by mbocquel          #+#    #+#             */
/*   Updated: 2023/04/12 14:40:26 by mbocquel         ###   ########.fr       */
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
