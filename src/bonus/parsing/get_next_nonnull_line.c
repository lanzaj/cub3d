/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_nonnull_line.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlanza <jlanza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 23:02:48 by jlanza            #+#    #+#             */
/*   Updated: 2023/03/26 23:03:21 by jlanza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

char	*get_next_nonnull_line(t_param *prm, int fd)
{
	char	*str;

	str = get_next_line(fd);
	if (str != NULL)
		garbage_col(prm, 0, str);
	while (str && (str[0] == '\n' || str[0] == '\0'))
	{
		str = get_next_line(fd);
		if (str != NULL)
			garbage_col(prm, 0, str);
	}
	return (str);
}
