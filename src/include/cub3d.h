/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbocquel <mbocquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 15:18:36 by jlanza            #+#    #+#             */
/*   Updated: 2023/03/17 12:11:01 by mbocquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../../libft/src/libft.h"
# include "../../minilibx-linux/mlx.h"
# include "cub3d_struct.h"

# include <math.h>
# include <sys/stat.h>
# include <fcntl.h>

/*	alloc_garbage	*/
/*	alloc_garbage -> ft_alloc_gc.c */
void			*ft_malloc_gc(t_param *prm, int id, size_t size);
void			*ft_calloc_gc(t_param *prm, int id, size_t nmemb,
					size_t size);
char			*ft_substr_gc(t_param *prm, char *s, unsigned int start,
					size_t len);
char			*ft_strdup_gc(t_param *prm, int id, const char *s);
char			*ft_strjoin_gc(t_param *prm, int id, char const *s1,
					char const *s2);

/*	alloc_garbage -> garbage_2.c */
void			garbage_split(t_param *prm, int id, char **strs);

/*	alloc_garbage -> garbage.c */
int				garbage_col(t_param *prm, int id, void *ptr);
void			empty_all_garbage(t_param *prm);
void			empty_garbage(t_param *prm, int id);
void			print_garbage(t_param *prm);
void			remove_from_garb(t_param *prm, void *ptr);

/*	maths	*/
/*	maths -> matrix_vector_calc.c */
t_coord			rotate(double angle, t_coord coord);
double			prod_scal(t_coord vect_1, t_coord vect_2);
t_coord			sum_vect(t_coord vect_1, t_coord vect_2);

/*	mlx_functions	*/
/*	mlx_functions -> mlx_print_seg.c */
void			put_segment_img(t_img *img, t_seg seg);

/*	mlx_functions -> mlx_utils.c */
void			my_mlx_pixel_put(t_img *img, int x, int y, int color);
void			ft_swap_seg(t_seg *seg, t_point *delt);

/*	mlx_functions -> mlx_color.c */
int				create_trgb(unsigned char t, unsigned char r,
					unsigned char g, unsigned char b);
unsigned char	get_t(int trgb);
unsigned char	get_r(int trgb);
unsigned char	get_g(int trgb);
unsigned char	get_b(int trgb);

#endif
