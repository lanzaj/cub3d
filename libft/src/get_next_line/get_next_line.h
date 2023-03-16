/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlanza <jlanza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 15:38:11 by jlanza            #+#    #+#             */
/*   Updated: 2023/03/07 00:58:37 by jlanza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# include "../libft.h"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

typedef struct s_list_sto
{
	char					*content;
	struct s_list_sto		*next;
}					t_list_sto;

void	ft_lstadd_back_gnl(t_list_sto **lst, void *content);
char	*get_next_line(int fd);
int		line_to_make_gnl(t_list_sto *storage);
char	*make_next_line(t_list_sto **storage, int *error);
int		read_store_gnl(t_list_sto **storage, char *buffer, int fd, int *error);
size_t	ft_line_len(t_list_sto *storage);
void	clean_storage_gnl(t_list_sto **storage);
void	clear_all_memory_gnl(t_list_sto **storage);

#endif
