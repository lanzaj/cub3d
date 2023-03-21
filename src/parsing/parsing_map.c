/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlanza <jlanza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 11:41:36 by mbocquel          #+#    #+#             */
/*   Updated: 2023/03/21 18:29:55 by jlanza           ###   ########.fr       */
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
	prm->screen.x = 2;
	prm->screen.y = 0;
}

int	check_extension(char *file_name)
{
	int	i;

	if (file_name == NULL || ft_strlen(file_name) <= 4)
		return (0);
	i = 0;
	while (file_name[i])
		i++;
	if (file_name[i - 5] == '/' || file_name[i - 4] != '.'
		|| file_name[i - 3] != 'c' || file_name[i - 2] != 'u'
		|| file_name[i - 1] != 'b')
		return (0);
	return (1);
}

char	*get_next_nonnull_line(int fd)
{
	char	*str;

	str = get_next_line(fd);
	while (str && (str[0] == '\n' || str[0] == '\0'))
	{
		free (str);
		str = get_next_line(fd);
	}
	return (str);
}

int	fd_to_card(t_param *prm, int fd, t_img *card_texture, char *card)
{
	char	*str;

	str = get_next_nonnull_line(fd);
	if (str || (ft_strncmp(str, card, 3) && ft_strlen(str) < 4)
		|| import_img(prm, card_texture, &str[3]))
	{
		ft_printf_fd(2, "Error\nInvalid %s\n", card);
		if (prm->map.north_texture.img != NULL)
			mlx_destroy_image(prm->mlx, &prm->map.north_texture.img);
		if (prm->map.south_texture.img != NULL)
			mlx_destroy_image(prm->mlx, &prm->map.south_texture.img);
		if (prm->map.west_texture.img != NULL)
			mlx_destroy_image(prm->mlx, &prm->map.west_texture.img);
		if (str)
			free(str);
		return (1);
	}
	free (str);
	return (0);
}

int	get_number(int *r, int i, char *str)
{
	if (ft_isint(&str[i]))
		r = ft_atoi(&str[i]);
	else
		return (1);
	if (r > 255 || r < 0)
		return (1);
}

int	get_next_number_pos(int *i, char *str)
{
	while (ft_isdigit((int)str[*i]))
		*i++;
	if (str[*i] == ",")
		*i++;
	else
		return (1);
}

int	import_color(t_param *prm, int *color_element, char *str)
{
	int	r;
	int	g;
	int	b;
	int	i;

	i = 0;
	if (get_number(&r, i, str) || get_next_number_pos(&i, str))
		return (1);
	if (get_number(&g, i, str) || get_next_number_pos(&i, str))
		return (1);
	if (get_number(&b, i, str))
		return (1);
	*color_element = create_trgb(0, (unsigned char)r, (unsigned char)g,
		(unsigned char)b);
	return (0);
}

int	fd_to_color(t_param *prm, int fd, int *color_element, char *color)
{
	char	*str;

	str = get_next_nonnull_line(fd);
	if (str || (ft_strncmp(str, color, 2) && ft_strlen(str) < 4)
		|| import_color(prm, color_element, &str[3]))
	{
		ft_printf_fd(2, "Error\nInvalid %scolor\n", color);
		if (prm->map.north_texture.img != NULL)
			mlx_destroy_image(prm->mlx, &prm->map.north_texture.img);
		if (prm->map.south_texture.img != NULL)
			mlx_destroy_image(prm->mlx, &prm->map.south_texture.img);
		if (prm->map.west_texture.img != NULL)
			mlx_destroy_image(prm->mlx, &prm->map.west_texture.img);
		if (prm->map.east_texture.img != NULL)
			mlx_destroy_image(prm->mlx, &prm->map.east_texture.img);
		if (str)
			free(str);
		return (1);
	}
	free (str);
	return (0);
}

int	fd_to_map(t_param *prm, int fd)
{
	if (fd_to_card(prm, fd, &prm->map.north_texture, "NO "))
		return (1);
	if (fd_to_card(prm, fd, &prm->map.south_texture, "SO "))
		return (1);
	if (fd_to_card(prm, fd, &prm->map.west_texture, "WE "))
		return (1);
	if (fd_to_card(prm, fd, &prm->map.east_texture, "EA "))
		return (1);
	if (fd_to_floor_color(prm, fd, prm->map.floor_color, "F "))
		return (1);
	if (fd_to_floor_color(prm, fd, prm->map.ceiling_color, "C "))
		return (1);
	return (0);
}

int	parsing_map(t_param *prm, char *file_name)
{
	int	fd;

	if (!check_extension(file_name))
		return (ft_printf_fd(2, "Error\nThe file format is invalid"), 1);
	fd = open(file_name, O_RDONLY);
	if (fd < 0)
		return (ft_printf_fd(2, "Error\nFailed to open the map"), 1);
	if (fd_to_map(prm, fd))
	{
		close(fd);
		return (1);
	}
	close(fd);
	return (0);
}

/* int	parsing_map(t_param *prm, char *file_name)
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
} */
