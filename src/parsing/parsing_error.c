/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlanza <jlanza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 13:50:36 by jlanza            #+#    #+#             */
/*   Updated: 2023/04/13 10:54:58 by jlanza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	open_error(t_param *prm, char *msg)
{
	ft_printf_fd(2, "%s", msg);
	mlx_destroy_window(prm->mlx, prm->win);
	mlx_destroy_display(prm->mlx);
	empty_garbage(prm, -1);
	exit(1);
}

int	check_map_error(t_param *prm, char *msg)
{
	ft_printf_fd(2, "%s", msg);
	destroy_images(prm);
	mlx_destroy_window(prm->mlx, prm->win);
	mlx_destroy_display(prm->mlx);
	empty_garbage(prm, -1);
	exit(1);
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
	mlx_destroy_image(prm->mlx, prm->layer.front.img);
	mlx_destroy_image(prm->mlx, prm->layer.back.img);
	destroy_images(prm);
	mlx_destroy_window(prm->mlx, prm->win);
	mlx_destroy_display(prm->mlx);
	empty_garbage(prm, -1);
	exit(1);
}
