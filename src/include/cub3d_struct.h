/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_struct.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbocquel <mbocquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 15:46:52 by jlanza            #+#    #+#             */
/*   Updated: 2023/03/16 17:06:51 by mbocquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_STRUCT_H
# define CUB3D_STRUCT_H

typedef enum e_bool {
	TRUE = 1,
	FALSE = 0
}				t_bool;

typedef struct s_coord {
	double	x;
	double	y;
}				t_coord;

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

typedef struct s_direction {
	char	up;
	char	left;
	char	right;
	char	down;
	char	dir;
}				t_direction;

typedef struct s_garb
{
	void			*ptr;
	int				id;
	struct s_garb	*next;
}					t_garb;

typedef struct s_param {
	void		*mlx;
	void		*win;
	int			width;
	int			height;
	t_direction	dir;
	t_garb		*garb;
}				t_param;


#endif
