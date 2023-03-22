/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbocquel <mbocquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 15:18:36 by jlanza            #+#    #+#             */
/*   Updated: 2023/03/22 18:13:49 by mbocquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../../libft/src/libft.h"
# include "../../mlx_linux/mlx.h"
# include "cub3d_struct.h"
# include <math.h>
# include <sys/stat.h>
# include <limits.h>
# include <fcntl.h>
# define KEY_LEFT_ARROW 65361
# define KEY_RIGHT_ARROW 65363
# define KEY_A 97
# define KEY_W 119
# define KEY_S 115
# define KEY_D 100
# define KEY_ESC 0xFF1B
# define LOOP 1000
# define MOUSE_ROLL_ZOOM 4
# define MOUSE_ROLL_UNZOOM 5
# define PI 3.14159f

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

/*	game */
/*	game -> event_handle.c */
int				key_press(int keycode, void *p);
int				key_release(int keycode, void *p);
int				is_valid_move(t_param *prm, t_coord pos);

/*	game -> game_loop.c */
int				game_loop(t_param *prm);
void			move_player(t_param *prm);
void			rotate_player(t_param *prm);

/*	game ->	initiate_game.c */
void			initiate_img_game(t_param *prm);
void			print_game(t_param *prm);

/*	minimap	*/
/*	minimap -> print_minimap.c */
void			initiate_img_minimap(t_param *prm);
void			print_mini_map_grid(t_param *prm);
void			print_minimap(t_param *prm, int x, int y);
void			print_player(t_param *prm);
void			print_raytracing(t_param *prm);

/*	mlx_functions	*/
/*	mlx_functions -> mlx_color.c */
int				create_trgb(unsigned char t, unsigned char r,
					unsigned char g, unsigned char b);
unsigned char	get_t(int trgb);
unsigned char	get_r(int trgb);
unsigned char	get_g(int trgb);
unsigned char	get_b(int trgb);

/*	mlx_functions -> mlx_print_seg.c */
void			put_segment_img(t_img *img, t_point start, t_point end);

/*	mlx_functions -> mlx_utils.c */
void			my_mlx_pixel_put(t_img *img, int x, int y, int color);
void			ft_swap_seg(t_seg *seg, t_point *delt);
int				get_color_gradian(t_point p_s, t_point p_e, t_point p);

/*	parsing	*/
/*	parsing	-> fd_to_map.c */
t_list			*fd_to_lst(int fd);
void			trim_backslash_n(char *str);
char			**lst_to_tab(t_list *lst, int fd);

/*	parsing -> import_img.c */
int				import_img(t_param *prm, t_img *xpm, char *path);

/*	parsing -> parsing_map.c */
void			init_player_pos(t_param *prm);
char			*get_next_nonnull_line(int fd);
int				parsing_map(t_param *prm, char *file_name);

/*	rayracing */
/*	rayracing -> find_first.c */
t_coord			find_first_h(t_param *prm, double ray_ang);
t_coord			find_first_h_part_2(t_param *prm, double ray_ang);
t_coord			find_first_v(t_param *prm, double ray_ang);
t_coord			find_first_v_part_2(t_param *prm, double ray_ang);

/*	rayracing -> find_wall.c */
t_coord			find_wall_h(t_param *prm, double ray_ang, t_coord first_h);
void			find_wall_h_part_2(t_param *prm,
					double ray_ang, t_coord *delt_h);
t_coord			find_wall_v(t_param *prm, double ray_ang, t_coord first_v);
void			find_wall_v_part_2(t_param *prm,
					double ray_ang, t_coord *delt_v);
t_coord			find_wall(t_param *prm, double ray_ang);

/*	rayracing -> hit_a_wall.c */
int				is_valid_coord(t_param *prm, t_coord coord);
int				has_hit_a_wall(t_param *prm, t_coord point);

/*	utils	*/
/*	utils -> ft_exit.c */
int				close_win(void *p);
int				ft_exit(t_param *prm, int exit_code);

/*	utils -> utils.c */
int				get_nb_str(char **strs);
void			ft_swap(int *a, int *b);
void			print_map(t_param *prm);

/*	vector_manipulation	*/
/*	vector_manipulation -> get_distance.c */
double			get_distance(t_coord a, t_coord b);

/*	vector_manipulation -> matrix_vector_calc.c */
t_coord			rotate(double angle, t_coord coord);
double			prod_scal(t_coord vect_1, t_coord vect_2);
t_coord			sum_vect(t_coord vect_1, t_coord vect_2);
int				va_abs(int i);
t_coord			prod_vect(double factor, t_coord vect);

/* vector_manipulation -> projection_minimap.c */
t_point			get_minimap_pos(t_param *prm, t_coord coord, int color);
double			convert_angle(double angle);

#endif
