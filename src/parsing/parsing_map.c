/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlanza <jlanza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 11:41:36 by mbocquel          #+#    #+#             */
/*   Updated: 2023/03/24 16:38:52 by jlanza           ###   ########.fr       */
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

char	*get_next_nonnull_line(t_param *prm, int fd)
{
	char	*str;
	static int	i = 0;

	printf("appel de get_n_nn_line number: %d\n", i);
	i++;
	print_garbage(prm);
	printf("\n");

	str = get_next_line(fd);
	free(str);
	//garbage_col(prm, 0, str);
	print_garbage(prm);
	/* while (str && (str[0] == '\n' || str[0] == '\0'))
	{
		str = get_next_line(fd);
		if (str != NULL)
			garbage_col(prm, 0, str);
	} */
	return (str);
}

int	fd_to_card_error(t_param *prm, int fd)
{
	close(fd);
	destroy_images(prm);
	mlx_destroy_window(prm->mlx, prm->win);
	mlx_destroy_display(prm->mlx);
	empty_garbage(prm, -1);
	exit(1);
}

void	fd_to_card(t_param *prm, int fd, t_img *card_texture, char *card)
{
	char	*str;

	str = get_next_nonnull_line(prm, fd);
	fd_to_card_error(prm, fd);
	//trim_backslash_n(str);
/* 	if (!str || ft_strncmp(str, card, 3) || ft_strlen(str) < 4
		|| import_img(prm, card_texture, &str[3]))
	{
		ft_printf_fd(2, "Error\nInvalid %s\n", card);
		fd_to_card_error(prm, fd);
	} */
	(void)card;
	(void)card_texture;
	(void)str;
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

static int	fd_to_color_error(t_param *prm, int fd)
{
	close(fd);
	destroy_images(prm);
	mlx_destroy_window(prm->mlx, prm->win);
	mlx_destroy_display(prm->mlx);
	empty_garbage(prm, -1);
	exit(1);
}

void	fd_to_color(t_param *prm, int fd, int *color_element, char *color)
{
	char	*str;

	str = get_next_nonnull_line(prm, fd);
	trim_backslash_n(str);
	if (!str || ft_strncmp(str, color, 2) || ft_strlen(str) < 7
		|| import_color(color_element, &str[2]))
	{
		ft_printf_fd(2, "Error\nInvalid %scolor\n", color);
		fd_to_color_error(prm, fd);
	}
}


void	fd_to_map(t_param *prm, int fd)
{
	t_list	*lst;

	fd_to_card(prm, fd, &(prm->map.north_texture), "NO ");
	fd_to_card(prm, fd, &(prm->map.south_texture), "SO ");
	fd_to_card(prm, fd, &(prm->map.west_texture), "WE ");
	fd_to_card(prm, fd, &(prm->map.east_texture), "EA ");
	fd_to_color(prm, fd, &(prm->map.floor_color), "F ");
	fd_to_color(prm, fd, &(prm->map.ceiling_color), "C ");
	lst = fd_to_lst(prm, fd);
	prm->map.map = lst_to_tab(lst, fd);
}

void	open_error(t_param *prm, char *msg)
{
	ft_printf_fd(2, "%s", msg);
	mlx_destroy_window(prm->mlx, prm->win);
	mlx_destroy_display(prm->mlx);
	empty_garbage(prm, -1);
	exit(1);
}

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
}
