/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_struct.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlanza <jlanza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 15:46:52 by jlanza            #+#    #+#             */
/*   Updated: 2023/04/13 10:40:53 by jlanza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_STRUCT_H
# define CUB3D_STRUCT_H

typedef enum e_bool {
	TRUE = 1,
	FALSE = 0
}				t_bool;

typedef enum e_dir {
	SOUTH = 2,
	NORTH = 3,
	EAST = 5,
	WEST = 7
}				t_dir;

typedef struct s_coord {
	double	x;
	double	y;
}				t_coord;

typedef struct s_px_col
{
	int				px_cell;
	int				px_wall;
	int				px_total;
	int				ofset;
	int				color_cell;
	int				color_floor;
}					t_px_col;

typedef struct s_point {
	int	x;
	int	y;
	int	color;
}				t_point;

typedef struct s_seg {
	t_point	start;
	t_point	end;
}				t_seg;

typedef struct s_img {
	void	*img;
	void	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		width;
	int		height;
}				t_img;

typedef struct s_layer {
	t_img	front;
	t_img	back;
}				t_layer;

typedef struct s_key_stat {
	char	left;
	char	right;
	char	key_w;
	char	key_a;
	char	key_d;
	char	key_s;
}				t_key_stat;

typedef struct s_garb
{
	void			*ptr;
	int				id;
	struct s_garb	*next;
}					t_garb;

typedef struct s_map
{
	char	**map;
	int		map_width;
	int		map_height;
	t_img	north_texture;
	t_img	south_texture;
	t_img	west_texture;
	t_img	east_texture;
	int		floor_color;
	int		ceiling_color;
}					t_map;

typedef struct s_param {
	void		*mlx;
	void		*win;
	int			width;
	int			height;
	int			frame;
	t_img		*img_tab[128];
	int			in_focus;
	t_layer		layer;
	t_key_stat	key;
	t_map		map;
	t_coord		pos_player;
	t_coord		view_dir;
	t_coord		screen_dir;
	double		view_ang;
	t_garb		*garb;
	int			mm_res_x;
	int			mm_res_y;
}				t_param;

#endif
