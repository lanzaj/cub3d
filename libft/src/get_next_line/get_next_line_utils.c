/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlanza <jlanza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 10:23:16 by mbocquel          #+#    #+#             */
/*   Updated: 2023/03/07 00:56:56 by jlanza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	ft_lstadd_back_gnl(t_list_sto **lst, void *content)
{
	t_list_sto	*new;
	t_list_sto	*elem;

	new = malloc(sizeof(t_list_sto));
	if (!new)
		return ;
	new->next = NULL;
	new->content = content;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	elem = *lst;
	while (elem->next)
	{
		elem = elem->next;
	}
	elem->next = new;
}

size_t	ft_line_len(t_list_sto *storage)
{
	size_t		len_line;
	int			i;
	t_list_sto	*elem;

	len_line = 0;
	elem = storage;
	while (elem)
	{
		i = -1;
		while ((elem->content)[++i] && (elem->content)[i] != '\n')
			len_line++;
		if ((elem->content)[i] && (elem->content)[i] == '\n')
			len_line++;
		elem = elem->next;
	}
	return (len_line);
}

void	clear_all_memory_gnl(t_list_sto **storage)
{
	t_list_sto	*elem;
	t_list_sto	*next;

	if (*storage == NULL)
		return ;
	elem = *storage;
	while (elem)
	{
		next = elem->next;
		free(elem->content);
		free(elem);
		elem = next;
	}
	*storage = NULL;
}
