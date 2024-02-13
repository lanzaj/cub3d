/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_to_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbocquel <mbocquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 18:41:28 by jlanza            #+#    #+#             */
/*   Updated: 2023/04/12 15:59:16 by mbocquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	check_import_textures_and_colors_p4(t_param *prm, int fd)
{
	if (prm->gun.explo[0].img == NULL
		|| prm->gun.explo[1].img == NULL
		|| prm->gun.explo[2].img == NULL
		|| prm->gun.explo[3].img == NULL
		|| prm->gun.explo[4].img == NULL
		|| prm->gun.explo[5].img == NULL
		|| prm->gun.explo[6].img == NULL
		|| prm->mm_window.img == NULL
		|| prm->health_bar[0].img == NULL
		|| prm->health_bar[1].img == NULL
		|| prm->health_bar[2].img == NULL
		|| prm->health_bar[3].img == NULL
		|| prm->health_bar[4].img == NULL)
		fd_to_map_error(prm, fd, "Error\nAssets not imported\n");
}

static void	check_import_textures_and_colors_p3(t_param *prm, int fd)
{
	if (prm->layer.front.img == NULL
		|| prm->layer.back.img == NULL
		|| prm->layer.loading.img == NULL
		|| prm->layer.goal.img == NULL
		|| prm->layer.start[0].img == NULL
		|| prm->layer.start[1].img == NULL
		|| prm->layer.lost[0].img == NULL
		|| prm->layer.lost[1].img == NULL
		|| prm->layer.win[0].img == NULL
		|| prm->layer.win[1].img == NULL
		|| prm->layer.pause[0].img == NULL
		|| prm->layer.pause[1].img == NULL
		|| prm->layer.pause[2].img == NULL
		|| prm->gun.gun1.img == NULL
		|| prm->gun.gun2.img == NULL)
		fd_to_map_error(prm, fd, "Error\nAssets not imported\n");
	check_import_textures_and_colors_p4(prm, fd);
}

static void	check_import_textures_and_colors_p2(t_param *prm, int fd)
{
	if (prm->map.attack_texture[0].img == NULL
		|| prm->map.attack_texture[1].img == NULL
		|| prm->map.attack_texture[2].img == NULL
		|| prm->map.attack_texture[3].img == NULL
		|| prm->map.die_texture[0].img == NULL
		|| prm->map.die_texture[1].img == NULL
		|| prm->map.die_texture[2].img == NULL
		|| prm->map.die_texture[3].img == NULL
		|| prm->map.barrel_texture.img == NULL
		|| prm->map.cables_texture.img == NULL
		|| prm->map.health_texture.img == NULL
		|| prm->map.ceiling_color == -1
		|| prm->map.floor_color == -1)
		fd_to_map_error(prm, fd, "Error\nDuplicate info or info missing\n");
	check_import_textures_and_colors_p3(prm, fd);
}

static void	check_import_textures_and_colors(t_param *prm, int fd)
{
	if (prm->map.north_texture.img == NULL
		|| prm->map.south_texture.img == NULL
		|| prm->map.east_texture.img == NULL
		|| prm->map.west_texture.img == NULL
		|| prm->map.wall2_texture.img == NULL
		|| prm->map.wall3_texture.img == NULL
		|| prm->map.wall4_texture.img == NULL
		|| prm->map.wall5_texture.img == NULL
		|| prm->map.wall6_texture.img == NULL
		|| prm->map.wall7_texture.img == NULL
		|| prm->map.wall8_texture.img == NULL
		|| prm->map.wall9_texture.img == NULL
		|| prm->map.door_texture.img == NULL
		|| prm->map.front_texture[0].img == NULL
		|| prm->map.front_texture[1].img == NULL
		|| prm->map.front_texture[2].img == NULL
		|| prm->map.front_texture[3].img == NULL)
		fd_to_map_error(prm, fd, "Error\nDuplicate info or info missing\n");
	check_import_textures_and_colors_p2(prm, fd);
}

void	fd_to_map(t_param *prm, int fd)
{
	t_list	*lst;
	char	*str;
	int		i;

	prm->map.ceiling_color = -1;
	prm->map.floor_color = -1;
	i = 0;
	while (i < 30)
	{
		str = get_next_nonnull_line(prm, fd);
		if (str == NULL)
			fd_to_map_error(prm, fd, "Error\nTexture or color missing\n");
		trim_backslash_n(str);
		str = trim_str(prm, str);
		if (str == NULL)
			fd_to_map_error(prm, fd, "Error\n");
		fd_to_card(prm, fd, str);
		fd_to_color(prm, fd, str);
		i++;
	}
	check_import_textures_and_colors(prm, fd);
	lst = fd_to_lst(prm, fd);
	prm->map.map = lst_to_tab(prm, lst, fd);
}
