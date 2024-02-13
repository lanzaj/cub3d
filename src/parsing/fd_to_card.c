/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_to_card.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbocquel <mbocquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 23:12:11 by jlanza            #+#    #+#             */
/*   Updated: 2023/04/12 16:06:53 by mbocquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	fd_to_card_part4(t_param *prm, int fd, char *str)
{
	if (!ft_strncmp(str, "A3", 2) && prm->map.attack_texture[3].img == NULL
		&& import_img(prm, &(prm->map.attack_texture[3]), &str[2]))
		fd_to_map_error(prm, fd, "Error\nInvalid attack3 texture\n");
	if (!ft_strncmp(str, "D0", 2) && prm->map.die_texture[0].img == NULL
		&& import_img(prm, &(prm->map.die_texture[0]), &str[2]))
		fd_to_map_error(prm, fd, "Error\nInvalid die0 texture\n");
	if (!ft_strncmp(str, "D1", 2) && prm->map.die_texture[1].img == NULL
		&& import_img(prm, &(prm->map.die_texture[1]), &str[2]))
		fd_to_map_error(prm, fd, "Error\nInvalid die1 texture\n");
	if (!ft_strncmp(str, "D2", 2) && prm->map.die_texture[2].img == NULL
		&& import_img(prm, &(prm->map.die_texture[2]), &str[2]))
		fd_to_map_error(prm, fd, "Error\nInvalid die2 texture\n");
	if (!ft_strncmp(str, "D3", 2) && prm->map.die_texture[3].img == NULL
		&& import_img(prm, &(prm->map.die_texture[3]), &str[2]))
		fd_to_map_error(prm, fd, "Error\nInvalid die3 texture\n");
	if (!ft_strncmp(str, "BA", 2) && prm->map.barrel_texture.img == NULL
		&& import_img(prm, &(prm->map.barrel_texture), &str[2]))
		fd_to_map_error(prm, fd, "Error\nInvalid barrel texture\n");
	if (!ft_strncmp(str, "HA", 2) && prm->map.cables_texture.img == NULL
		&& import_img(prm, &(prm->map.cables_texture), &str[2]))
		fd_to_map_error(prm, fd, "Error\nInvalid hanging texture\n");
	if (!ft_strncmp(str, "PV", 2) && prm->map.health_texture.img == NULL
		&& import_img(prm, &(prm->map.health_texture), &str[2]))
		fd_to_map_error(prm, fd, "Error\nInvalid health texture\n");
}

static void	fd_to_card_part3(t_param *prm, int fd, char *str)
{
	if (!ft_strncmp(str, "W9", 2) && prm->map.wall9_texture.img == NULL
		&& import_img(prm, &(prm->map.wall9_texture), &str[2]))
		fd_to_map_error(prm, fd, "Error\nInvalid wall 9 texture\n");
	if (!ft_strncmp(str, "E0", 2) && prm->map.front_texture[0].img == NULL
		&& import_img(prm, &(prm->map.front_texture[0]), &str[2]))
		fd_to_map_error(prm, fd, "Error\nInvalid enemy 0 texture\n");
	if (!ft_strncmp(str, "E1", 2) && prm->map.front_texture[1].img == NULL
		&& import_img(prm, &(prm->map.front_texture[1]), &str[2]))
		fd_to_map_error(prm, fd, "Error\nInvalid enemy 1 texture\n");
	if (!ft_strncmp(str, "E2", 2) && prm->map.front_texture[2].img == NULL
		&& import_img(prm, &(prm->map.front_texture[2]), &str[2]))
		fd_to_map_error(prm, fd, "Error\nInvalid enemy 2 texture\n");
	if (!ft_strncmp(str, "E3", 2) && prm->map.front_texture[3].img == NULL
		&& import_img(prm, &(prm->map.front_texture[3]), &str[2]))
		fd_to_map_error(prm, fd, "Error\nInvalid enemy 3 texture\n");
	if (!ft_strncmp(str, "A0", 2) && prm->map.attack_texture[0].img == NULL
		&& import_img(prm, &(prm->map.attack_texture[0]), &str[2]))
		fd_to_map_error(prm, fd, "Error\nInvalid attack0 texture\n");
	if (!ft_strncmp(str, "A1", 2) && prm->map.attack_texture[1].img == NULL
		&& import_img(prm, &(prm->map.attack_texture[1]), &str[2]))
		fd_to_map_error(prm, fd, "Error\nInvalid attack1 texture\n");
	if (!ft_strncmp(str, "A2", 2) && prm->map.attack_texture[2].img == NULL
		&& import_img(prm, &(prm->map.attack_texture[2]), &str[2]))
		fd_to_map_error(prm, fd, "Error\nInvalid attack2 texture\n");
	fd_to_card_part4(prm, fd, str);
}

static void	fd_to_card_part2(t_param *prm, int fd, char *str)
{
	if (!ft_strncmp(str, "W2", 2) && prm->map.wall2_texture.img == NULL
		&& import_img(prm, &(prm->map.wall2_texture), &str[2]))
		fd_to_map_error(prm, fd, "Error\nInvalid wall 2 texture\n");
	if (!ft_strncmp(str, "W3", 2) && prm->map.wall3_texture.img == NULL
		&& import_img(prm, &(prm->map.wall3_texture), &str[2]))
		fd_to_map_error(prm, fd, "Error\nInvalid wall 3 texture\n");
	if (!ft_strncmp(str, "W4", 2) && prm->map.wall4_texture.img == NULL
		&& import_img(prm, &(prm->map.wall4_texture), &str[2]))
		fd_to_map_error(prm, fd, "Error\nInvalid wall 4 texture\n");
	if (!ft_strncmp(str, "W5", 2) && prm->map.wall5_texture.img == NULL
		&& import_img(prm, &(prm->map.wall5_texture), &str[2]))
		fd_to_map_error(prm, fd, "Error\nInvalid wall 5 texture\n");
	if (!ft_strncmp(str, "W6", 2) && prm->map.wall6_texture.img == NULL
		&& import_img(prm, &(prm->map.wall6_texture), &str[2]))
		fd_to_map_error(prm, fd, "Error\nInvalid wall 6 texture\n");
	if (!ft_strncmp(str, "W7", 2) && prm->map.wall7_texture.img == NULL
		&& import_img(prm, &(prm->map.wall7_texture), &str[2]))
		fd_to_map_error(prm, fd, "Error\nInvalid wall 7 texture\n");
	if (!ft_strncmp(str, "W8", 2) && prm->map.wall8_texture.img == NULL
		&& import_img(prm, &(prm->map.wall8_texture), &str[2]))
		fd_to_map_error(prm, fd, "Error\nInvalid wall 8 texture\n");
	fd_to_card_part3(prm, fd, str);
}

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
	if (!ft_strncmp(str, "DO", 2) && prm->map.door_texture.img == NULL
		&& import_img(prm, &(prm->map.door_texture), &str[2]))
		fd_to_map_error(prm, fd, "Error\nInvalid door texture\n");
	fd_to_card_part2(prm, fd, str);
}
