/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_to_card.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbocquel <mbocquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 23:12:11 by jlanza            #+#    #+#             */
/*   Updated: 2023/03/29 15:00:33 by mbocquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	fd_to_card(t_param *prm, int fd, char *str)
{
	if (!str || ft_strlen(str) < 4)
		fd_to_map_error(prm, fd, "Error\nInvalid line\n");
	if (!ft_strncmp(str, "NO ", 3) && prm->map.north_texture.img == NULL
		&& import_img(prm, &(prm->map.north_texture), &str[3]))
		fd_to_map_error(prm, fd, "Error\nInvalid north texture\n");
	if (!ft_strncmp(str, "SO ", 3) && prm->map.south_texture.img == NULL
		&& import_img(prm, &(prm->map.south_texture), &str[3]))
		fd_to_map_error(prm, fd, "Error\nInvalid south texture\n");
	if (!ft_strncmp(str, "WE ", 3) && prm->map.west_texture.img == NULL
		&& import_img(prm, &(prm->map.west_texture), &str[3]))
		fd_to_map_error(prm, fd, "Error\nInvalid west texture\n");
	if (!ft_strncmp(str, "EA ", 3) && prm->map.east_texture.img == NULL
		&& import_img(prm, &(prm->map.east_texture), &str[3]))
		fd_to_map_error(prm, fd, "Error\nInvalid east texture\n");
	if (!ft_strncmp(str, "DO ", 3) && prm->map.door_texture.img == NULL
		&& import_img(prm, &(prm->map.door_texture), &str[3]))
		fd_to_map_error(prm, fd, "Error\nInvalid door texture\n");
}
