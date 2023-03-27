/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_to_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlanza <jlanza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 18:41:28 by jlanza            #+#    #+#             */
/*   Updated: 2023/03/26 23:28:47 by jlanza           ###   ########.fr       */
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

int	fd_to_map_error(t_param *prm, int fd, char *msg)
{
	char	*str;

	ft_printf_fd(2, "%s", msg);
	str = get_next_line(fd);
	while (str)
	{
		free(str);
		str = get_next_line(fd);
	}
	close(fd);
	destroy_images(prm);
	mlx_destroy_window(prm->mlx, prm->win);
	mlx_destroy_display(prm->mlx);
	empty_garbage(prm, -1);
	exit(1);
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
		trim_backslash_n(str);
		fd_to_card(prm, fd, str);
		fd_to_color(prm, fd, str);
		i++;
	}
	check_import_textures_and_colors(prm, fd);
	lst = fd_to_lst(prm, fd);
	prm->map.map = lst_to_tab(prm, lst, fd);
}
