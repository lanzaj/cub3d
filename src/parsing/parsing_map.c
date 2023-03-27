/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlanza <jlanza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 11:41:36 by mbocquel          #+#    #+#             */
/*   Updated: 2023/03/26 23:27:42 by jlanza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	check_import_textures_and_colors(t_param *prm, int fd)
{
	if (prm->map.north_texture.img == NULL
		|| prm->map.south_texture.img == NULL
		|| prm->map.east_texture.img == NULL
		|| prm->map.west_texture.img == NULL)
		fd_to_map_error(prm, fd, "Error\nTexture missing\n");
	if (prm->map.ceiling_color == -1
		|| prm->map.floor_color == -1)
		fd_to_map_error(prm, fd, "Error\nColor missing\n");
}

static void	open_error(t_param *prm, char *msg)
{
	ft_printf_fd(2, "%s", msg);
	mlx_destroy_window(prm->mlx, prm->win);
	mlx_destroy_display(prm->mlx);
	empty_garbage(prm, -1);
	exit(1);
}

void	parsing_map(t_param *prm, char *file_name)
{
	int	fd;

	if (!check_extension(file_name))
		open_error(prm, "Error\nThe file format is invalid\n");
	fd = open(file_name, O_RDONLY);
	if (fd < 0)
		open_error(prm, "Error\nFailed to open the map\n");
	fd_to_map(prm, fd);
	close(fd);
	prm->map.map_height = count_number_of_lines(prm->map.map);
	prm->map.map_width = count_max_width_of_lines(prm->map.map);
	check_map(prm, prm->map.map);
}
