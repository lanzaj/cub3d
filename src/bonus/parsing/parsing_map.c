/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbocquel <mbocquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 11:41:36 by mbocquel          #+#    #+#             */
/*   Updated: 2023/03/29 16:08:32 by mbocquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

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
	init_doors_tab(prm);
}
