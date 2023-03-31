/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_to_card.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbocquel <mbocquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 23:12:11 by jlanza            #+#    #+#             */
/*   Updated: 2023/03/31 18:13:02 by mbocquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	fd_to_card_part2(t_param *prm, int fd, char *str)
{
	if (!ft_strncmp(str, "W3 ", 3) && prm->map.wall3_texture.img == NULL
		&& import_img(prm, &(prm->map.wall3_texture), &str[3]))
		fd_to_map_error(prm, fd, "Error\nInvalid wall 3 texture\n");
	if (!ft_strncmp(str, "W4 ", 3) && prm->map.wall4_texture.img == NULL
		&& import_img(prm, &(prm->map.wall4_texture), &str[3]))
		fd_to_map_error(prm, fd, "Error\nInvalid wall 4 texture\n");
	if (!ft_strncmp(str, "W5 ", 3) && prm->map.wall5_texture.img == NULL
		&& import_img(prm, &(prm->map.wall5_texture), &str[3]))
		fd_to_map_error(prm, fd, "Error\nInvalid wall 5 texture\n");
	if (!ft_strncmp(str, "W6 ", 3) && prm->map.wall6_texture.img == NULL
		&& import_img(prm, &(prm->map.wall6_texture), &str[3]))
		fd_to_map_error(prm, fd, "Error\nInvalid wall 6 texture\n");
	if (!ft_strncmp(str, "W7 ", 3) && prm->map.wall7_texture.img == NULL
		&& import_img(prm, &(prm->map.wall7_texture), &str[3]))
		fd_to_map_error(prm, fd, "Error\nInvalid wall 7 texture\n");
	if (!ft_strncmp(str, "W8 ", 3) && prm->map.wall8_texture.img == NULL
		&& import_img(prm, &(prm->map.wall8_texture), &str[3]))
		fd_to_map_error(prm, fd, "Error\nInvalid wall 8 texture\n");
	if (!ft_strncmp(str, "W9 ", 3) && prm->map.wall9_texture.img == NULL
		&& import_img(prm, &(prm->map.wall9_texture), &str[3]))
		fd_to_map_error(prm, fd, "Error\nInvalid wall 9 texture\n");
}

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
	fd_to_card_part2(prm, fd, str);
}
