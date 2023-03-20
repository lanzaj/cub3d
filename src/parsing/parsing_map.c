/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbocquel <mbocquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 11:41:36 by mbocquel          #+#    #+#             */
/*   Updated: 2023/03/20 17:46:36 by mbocquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

/*Juste pour faire des tests*/
//Fonction temp pour les test. 
void	init_player_pos(t_param *prm)
{
	prm->pos_player.x = 3.5;
	prm->pos_player.y = 2.5;
	prm->view_dir.x = 0;
	prm->view_dir.y = 2;
	prm->screen_dir.x = 2;
	prm->screen_dir.y = 0;
	prm->view_ang = (3 * PI) / 2;
}

int	parsing_map(t_param *prm, char *file_name)
{
	(void)file_name;
	prm->map.map = ft_calloc_gc(prm, 0, 25, sizeof(char *));
	if (prm->map.map == NULL)
		return (1);
	prm->map.map_height = 24;
	prm->map.map_width = 24;
	prm->map.map[0] = ft_strdup_gc(prm, 0, "111111111111111111111111");
	prm->map.map[1] = ft_strdup_gc(prm, 0, "100000000000000000000001");
	prm->map.map[2] = ft_strdup_gc(prm, 0, "100000000000000000000001");
	prm->map.map[3] = ft_strdup_gc(prm, 0, "100000000000000000000001");
	prm->map.map[4] = ft_strdup_gc(prm, 0, "100000111110000101010001");
	prm->map.map[5] = ft_strdup_gc(prm, 0, "100000100010000000000001");
	prm->map.map[6] = ft_strdup_gc(prm, 0, "100000100010000100010001");
	prm->map.map[7] = ft_strdup_gc(prm, 0, "100000100010000000000001");
	prm->map.map[8] = ft_strdup_gc(prm, 0, "100000110110000101010001");
	prm->map.map[9] = ft_strdup_gc(prm, 0, "100000000000000000000001");
	prm->map.map[10] = ft_strdup_gc(prm, 0, "100000000000000000000001");
	prm->map.map[11] = ft_strdup_gc(prm, 0, "100000000000000000000001");
	prm->map.map[12] = ft_strdup_gc(prm, 0, "100000000000000000000001");
	prm->map.map[13] = ft_strdup_gc(prm, 0, "100000000000000000000001");
	prm->map.map[14] = ft_strdup_gc(prm, 0, "100000000000000000000001");
	prm->map.map[15] = ft_strdup_gc(prm, 0, "111111111000000000000001");
	prm->map.map[16] = ft_strdup_gc(prm, 0, "110100001000000000000001");
	prm->map.map[17] = ft_strdup_gc(prm, 0, "110000101000000000000001");
	prm->map.map[18] = ft_strdup_gc(prm, 0, "110100001000000000000001");
	prm->map.map[19] = ft_strdup_gc(prm, 0, "110111111000000000000001");
	prm->map.map[20] = ft_strdup_gc(prm, 0, "110000000000000000000001");
	prm->map.map[21] = ft_strdup_gc(prm, 0, "111111111000000000000001");
	prm->map.map[22] = ft_strdup_gc(prm, 0, "110000000000000000000001");
	prm->map.map[23] = ft_strdup_gc(prm, 0, "111111111111111111111111");
	if (get_nb_str(prm->map.map) != 24)
		return (1);
	return (0);
}
