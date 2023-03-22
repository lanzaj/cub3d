/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_to_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlanza <jlanza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 18:41:28 by jlanza            #+#    #+#             */
/*   Updated: 2023/03/22 16:16:51 by jlanza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

t_list	*fd_to_lst(int fd)
{
	t_list	*lst;
	t_list	*new;
	char	*line;

	lst = NULL;
	line = get_next_nonnull_line(fd);
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
	while (str[i])
	{
		if (str[i] == '\n')
			str[i] = '\0';
		i++;
	}
}

char	**lst_to_tab(t_list *lst, int fd)
{
	int		i;
	char	**map;
	t_list	*current;

	if (lst == NULL)
	{
		close(fd);
		exit(4);
	}
	map = ft_calloc(ft_lstsize(lst) + 2, sizeof(*map));
	/* if (map == NULL)
		lst_to_tab_calloc_fail(lst, fd); */
	current = lst;
	i = 0;
	while (current != NULL)
	{
		map[i] = ft_strdup(current->content);
		/* if (map[i] == NULL)
			lst_to_tab_error(lst, map, fd); */
		trim_backslash_n(map[i]);
		current = current->next;
		i++;
	}
	ft_lstclear(&lst, &free);
	return (map);
}

/* static char	**fd_to_map(int fd)
{
	t_list	*lst;
	char	**map;

	lst = fd_to_lst(fd);
	map = lst_to_tab(lst, fd);
	return (map);
} */
