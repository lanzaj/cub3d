/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_to_card.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbocquel <mbocquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 23:12:11 by jlanza            #+#    #+#             */
/*   Updated: 2023/04/12 13:27:16 by mbocquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	fd_to_card(t_param *prm, int fd, char *str)
{
	if (!str || ft_strlen(str) < 4)
		fd_to_map_error(prm, fd, "Error\nInvalid line\n");
	if (!ft_strncmp(str, "NO", 2) && prm->map.north_texture.img == NULL
		&& import_img(prm, &(prm->map.north_texture), &str[2]))
		fd_to_map_error(prm, fd, "Error\nInvalid north texture\n");
	if (!ft_strncmp(str, "SO", 2) && prm->map.south_texture.img == NULL
		&& import_img(prm, &(prm->map.south_texture), &str[2]))
		fd_to_map_error(prm, fd, "Error\nInvalid south texture\n");
	if (!ft_strncmp(str, "WE", 2) && prm->map.west_texture.img == NULL
		&& import_img(prm, &(prm->map.west_texture), &str[2]))
		fd_to_map_error(prm, fd, "Error\nInvalid west texture\n");
	if (!ft_strncmp(str, "EA", 2) && prm->map.east_texture.img == NULL
		&& import_img(prm, &(prm->map.east_texture), &str[2]))
		fd_to_map_error(prm, fd, "Error\nInvalid east texture\n");
}
