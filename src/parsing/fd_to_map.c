/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_to_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlanza <jlanza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 18:41:28 by jlanza            #+#    #+#             */
/*   Updated: 2023/03/26 14:23:46 by jlanza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

t_list	*fd_to_lst(t_param *prm, int fd)
{
	t_list	*lst;
	t_list	*new;
	char	*line;

	lst = NULL;
	line = ft_strdup(get_next_nonnull_line(prm, fd));
	while (line != NULL)
	{
		new = ft_lstnew(line);
		if (new == NULL)
		{
			ft_lstclear(&lst, &free);
			exit (1);
		}
		ft_lstadd_back(&lst, new);
		line = get_next_line(fd);
	}
	return (lst);
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

char	**lst_to_tab(t_param *prm, t_list *lst, int fd)
{
	int		i;
	char	**map;
	t_list	*current;

	if (lst == NULL)
	{
		close(fd);
		exit(4);
	}
	map = ft_calloc_gc(prm, 0, ft_lstsize(lst) + 2, sizeof(*map));
	/* if (map == NULL)
		lst_to_tab_calloc_fail(lst, fd); */
	current = lst;
	i = 0;
	while (current != NULL)
	{
		map[i] = ft_strdup_gc(prm, 0, current->content);
		/* if (map[i] == NULL)
			lst_to_tab_error(lst, map, fd); */
		trim_backslash_n(map[i]);
		current = current->next;
		i++;
	}
	ft_lstclear(&lst, &free);
	return (map);
}

