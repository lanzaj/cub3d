/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbocquel <mbocquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 11:41:36 by mbocquel          #+#    #+#             */
/*   Updated: 2023/03/22 18:52:43 by mbocquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	init_player_pos(t_param *prm)
{
	prm->pos_player.x = 4.5;
	prm->pos_player.y = 2.5;
	prm->view_dir.x = 2;
	prm->view_dir.y = 0;
	prm->screen_dir.x = 0;
	prm->screen_dir.y = 2;
	prm->view_ang = 0;
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
	trim_backslash_n(str);
	if (!str || ft_strncmp(str, card, 3) || ft_strlen(str) < 4
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

int	get_number(int *n, int i, char *str)
{
	if (ft_isint(&str[i]))
		*n = ft_atoi(&str[i]);
	else
		return (1);
	if (*n > 255 || *n < 0)
		return (1);
	return (0);
}

int	get_next_number_pos(int *i, char *str)
{
	while (ft_isdigit((int)str[*i]))
		(*i)++;
	if (str[*i] == ',')
		(*i)++;
	else
		return (1);
	return (0);
}

int	import_color(int *color_element, char *str)
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
	trim_backslash_n(str);
	if (!str || ft_strncmp(str, color, 2) || ft_strlen(str) < 7
		|| import_color(color_element, &str[2]))
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
	t_list	*lst;

	if (fd_to_card(prm, fd, &(prm->map.north_texture), "NO "))
		return (1);
	if (fd_to_card(prm, fd, &(prm->map.south_texture), "SO "))
		return (1);
	if (fd_to_card(prm, fd, &(prm->map.west_texture), "WE "))
		return (1);
	if (fd_to_card(prm, fd, &(prm->map.east_texture), "EA "))
		return (1);
	if (fd_to_color(prm, fd, &(prm->map.floor_color), "F "))
		return (1);
	if (fd_to_color(prm, fd, &(prm->map.ceiling_color), "C "))
		return (1);
	lst = fd_to_lst(fd);
	prm->map.map = lst_to_tab(lst, fd);
	return (0);
}

static int	count_number_of_lines(char **map)
{
	int	i;

	i = 0;
	while (map[i])
		i++;
	return (i);
}

static int	count_max_width_of_lines(char **map)
{
	int		i;
	size_t	max_len;

	i = 0;
	max_len = 0;
	while (map[i])
	{
		if (ft_strlen(map[i]) > max_len)
			max_len = ft_strlen(map[i]);
		i++;
	}
	return (max_len);
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
	prm->map.map_height = count_number_of_lines(prm->map.map);
	prm->map.map_width = count_max_width_of_lines(prm->map.map);
	return (0);
}
