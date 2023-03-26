/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlanza <jlanza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 11:41:36 by mbocquel          #+#    #+#             */
/*   Updated: 2023/03/26 21:57:47 by jlanza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	get_starting_pos(t_param *prm, int *x, int *y)
{
	*y = 0;
	while (prm->map.map[*y])
	{
		*x = 0;
		while (prm->map.map[*y][*x])
		{
			if (prm->map.map[*y][*x] == 'N'
				|| prm->map.map[*y][*x] == 'S'
				|| prm->map.map[*y][*x] == 'E'
				|| prm->map.map[*y][*x] == 'W')
				return ;
			(*x)++;
		}
		(*y)++;
	}
}

void	init_player_pos(t_param *prm)
{
	int	x;
	int	y;

	get_starting_pos(prm, &x, &y);
	printf("%d	%d\n", x, y);
	prm->pos_player.x = (double)x + 0.5;
	prm->pos_player.y = (double)y + 0.5;
	printf("%c\n", prm->map.map[y][x]);
	if (prm->map.map[y][x] == 'E')
	{
		prm->view_dir.x = 2;
		prm->view_dir.y = 0;
		prm->screen_dir.x = 0;
		prm->screen_dir.y = 2;
		prm->view_ang = 0;
	}
	else if (prm->map.map[y][x] == 'W')
	{
		prm->view_dir.x = -2;
		prm->view_dir.y = 0;
		prm->screen_dir.x = 0;
		prm->screen_dir.y = -2;
		prm->view_ang = 0;
	}
	else if (prm->map.map[y][x] == 'N')
	{
		prm->view_dir.x = 0;
		prm->view_dir.y = -2;
		prm->screen_dir.x = 2;
		prm->screen_dir.y = 0;
		prm->view_ang = 0;
	}
	else if (prm->map.map[y][x] == 'S')
	{
		prm->view_dir.x = 0;
		prm->view_dir.y = 2;
		prm->screen_dir.x = -2;
		prm->screen_dir.y = 0;
		prm->view_ang = 0;
	}
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

	str = get_next_line(fd);
	if (str != NULL)
		garbage_col(prm, 0, str);
	while (str && (str[0] == '\n' || str[0] == '\0'))
	{
		str = get_next_line(fd);
		if (str != NULL)
			garbage_col(prm, 0, str);
	}
	return (str);
}

int	fd_to_card_error(t_param *prm, int fd, char *msg)
{
	char	*str;

	ft_printf_fd(2, "%s", msg);
	str = get_next_line(fd);
	while (str)
	{
		free(str);
		str = get_next_line(fd);
	}
	close(fd);
	destroy_images(prm);
	mlx_destroy_window(prm->mlx, prm->win);
	mlx_destroy_display(prm->mlx);
	empty_garbage(prm, -1);
	exit(1);
}

void	fd_to_card(t_param *prm, int fd, char *str)
{
	if (!str || ft_strlen(str) < 4)
		fd_to_card_error(prm, fd, "Error\nInvalid line\n");
	if (!ft_strncmp(str, "NO ", 3) && prm->map.north_texture.img == NULL
		&& import_img(prm, &(prm->map.north_texture), &str[3]))
		fd_to_card_error(prm, fd, "Error\nInvalid north texture\n");
	if (!ft_strncmp(str, "SO ", 3) && prm->map.south_texture.img == NULL
		&& import_img(prm, &(prm->map.south_texture), &str[3]))
		fd_to_card_error(prm, fd, "Error\nInvalid south texture\n");
	if (!ft_strncmp(str, "WE ", 3) && prm->map.west_texture.img == NULL
		&& import_img(prm, &(prm->map.west_texture), &str[3]))
		fd_to_card_error(prm, fd, "Error\nInvalid west texture\n");
	if (!ft_strncmp(str, "EA ", 3) && prm->map.east_texture.img == NULL
		&& import_img(prm, &(prm->map.east_texture), &str[3]))
		fd_to_card_error(prm, fd, "Error\nInvalid east texture\n");
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
	while (ft_isdigit(str[i]))
		i++;
	if (str[i] != '\0')
		return (1);
	*color_element = create_trgb(0, (unsigned char)r, (unsigned char)g,
			(unsigned char)b);
	return (0);
}

static int	fd_to_color_error(t_param *prm, int fd, char *msg)
{
	char	*str;

	ft_printf_fd(2, "%s", msg);
	str = get_next_line(fd);
	while (str)
	{
		free(str);
		str = get_next_line(fd);
	}
	close(fd);
	destroy_images(prm);
	mlx_destroy_window(prm->mlx, prm->win);
	mlx_destroy_display(prm->mlx);
	empty_garbage(prm, -1);
	exit(1);
}

void	fd_to_color(t_param *prm, int fd, char *str)
{
	if (!str || ft_strlen(str) < 4)
		fd_to_card_error(prm, fd, "Error\nInvalid line\n");
	if (!ft_strncmp(str, "F ", 2) && prm->map.floor_color == -1
		&& import_color(&(prm->map.floor_color), &str[2]))
		fd_to_color_error(prm, fd, "Error\nInvalid floor color\n");
	if (!ft_strncmp(str, "C ", 2) && prm->map.ceiling_color == -1
		&& import_color(&(prm->map.ceiling_color), &str[2]))
		fd_to_color_error(prm, fd, "Error\nInvalid ceiling color\n");
}

void	check_import_textures_and_colors(t_param *prm, int fd)
{
	if (prm->map.north_texture.img == NULL
		|| prm->map.south_texture.img == NULL
		|| prm->map.east_texture.img == NULL
		|| prm->map.west_texture.img == NULL)
		fd_to_card_error(prm, fd, "Error\nTexture missing\n");
	if (prm->map.ceiling_color == -1
		|| prm->map.floor_color == -1)
		fd_to_color_error(prm, fd, "Error\nColor missing\n");
}

void	fd_to_map(t_param *prm, int fd)
{
	t_list	*lst;
	char	*str;
	int		i;

	prm->map.ceiling_color = -1;
	prm->map.floor_color = -1;
	i = 0;
	while (i < 6)
	{
		str = get_next_nonnull_line(prm, fd);
		trim_backslash_n(str);
		fd_to_card(prm, fd, str);
		fd_to_color(prm, fd, str);
		i++;
	}
	check_import_textures_and_colors(prm, fd);
	lst = fd_to_lst(prm, fd);
	prm->map.map = lst_to_tab(prm, lst, fd);
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
	check_map(prm, prm->map.map);
}
