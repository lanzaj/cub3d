/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_to_card.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlanza <jlanza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 23:12:11 by jlanza            #+#    #+#             */
/*   Updated: 2023/04/04 16:47:42 by jlanza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	fd_to_card_part4(t_param *prm, int fd, char *str)
{
	if (!ft_strncmp(str, "D1 ", 3) && prm->map.die1_texture.img == NULL
		&& import_img(prm, &(prm->map.die1_texture), &str[3]))
		fd_to_map_error(prm, fd, "Error\nInvalid die1 texture\n");
	if (!ft_strncmp(str, "D2 ", 3) && prm->map.die2_texture.img == NULL
		&& import_img(prm, &(prm->map.die2_texture), &str[3]))
		fd_to_map_error(prm, fd, "Error\nInvalid die2 texture\n");
	if (!ft_strncmp(str, "D3 ", 3) && prm->map.die3_texture.img == NULL
		&& import_img(prm, &(prm->map.die3_texture), &str[3]))
		fd_to_map_error(prm, fd, "Error\nInvalid die3 texture\n");
	if (!ft_strncmp(str, "BA ", 3) && prm->map.barrel_texture.img == NULL
		&& import_img(prm, &(prm->map.barrel_texture), &str[3]))
		fd_to_map_error(prm, fd, "Error\nInvalid barrel texture\n");
	if (!ft_strncmp(str, "CA ", 3) && prm->map.cables_texture.img == NULL
		&& import_img(prm, &(prm->map.cables_texture), &str[3]))
		fd_to_map_error(prm, fd, "Error\nInvalid cables texture\n");
}

static void	fd_to_card_part3(t_param *prm, int fd, char *str)
{
	if (!ft_strncmp(str, "W9 ", 3) && prm->map.wall9_texture.img == NULL
		&& import_img(prm, &(prm->map.wall9_texture), &str[3]))
		fd_to_map_error(prm, fd, "Error\nInvalid wall 9 texture\n");
	if (!ft_strncmp(str, "F1 ", 3) && prm->map.front1_texture.img == NULL
		&& import_img(prm, &(prm->map.front1_texture), &str[3]))
		fd_to_map_error(prm, fd, "Error\nInvalid front1 texture\n");
	if (!ft_strncmp(str, "F2 ", 3) && prm->map.front2_texture.img == NULL
		&& import_img(prm, &(prm->map.front2_texture), &str[3]))
		fd_to_map_error(prm, fd, "Error\nInvalid front2 texture\n");
	if (!ft_strncmp(str, "F3 ", 3) && prm->map.front3_texture.img == NULL
		&& import_img(prm, &(prm->map.front3_texture), &str[3]))
		fd_to_map_error(prm, fd, "Error\nInvalid front3 texture\n");
	if (!ft_strncmp(str, "F4 ", 3) && prm->map.front4_texture.img == NULL
		&& import_img(prm, &(prm->map.front4_texture), &str[3]))
		fd_to_map_error(prm, fd, "Error\nInvalid front4 texture\n");
	if (!ft_strncmp(str, "A1 ", 3) && prm->map.attack1_texture.img == NULL
		&& import_img(prm, &(prm->map.attack1_texture), &str[3]))
		fd_to_map_error(prm, fd, "Error\nInvalid attack1 texture\n");
	if (!ft_strncmp(str, "A2 ", 3) && prm->map.attack2_texture.img == NULL
		&& import_img(prm, &(prm->map.attack2_texture), &str[3]))
		fd_to_map_error(prm, fd, "Error\nInvalid attack2 texture\n");
	if (!ft_strncmp(str, "A3 ", 3) && prm->map.attack3_texture.img == NULL
		&& import_img(prm, &(prm->map.attack3_texture), &str[3]))
		fd_to_map_error(prm, fd, "Error\nInvalid attack3 texture\n");
	fd_to_card_part4(prm, fd, str);
}

static void	fd_to_card_part2(t_param *prm, int fd, char *str)
{
	if (!ft_strncmp(str, "W2 ", 3) && prm->map.wall2_texture.img == NULL
		&& import_img(prm, &(prm->map.wall2_texture), &str[3]))
		fd_to_map_error(prm, fd, "Error\nInvalid wall 2 texture\n");
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
	fd_to_card_part3(prm, fd, str);
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
