/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbocquel <mbocquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 15:18:36 by jlanza            #+#    #+#             */
/*   Updated: 2023/04/12 16:08:19 by mbocquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../../../libft/src/libft.h"
# include "../../../mlx_linux/mlx.h"
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
# define LOOP 150
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
int				handle_mouse_move(int x, int y, void *param);

/*	game -> game_loop.c */
int				game_loop(t_param *prm);
t_coord			get_wanted_move_dir(t_param *prm);
double			angle_move(t_param *prm);
t_coord			pos_buff(t_param *prm, t_coord pos);

/*	game -> get_color_to_print.c */
double			pos_impact(t_param *prm, t_coord point);
int				get_texture_px_color(t_param *prm, t_coord wall, double pos_y);
int				get_color_px(t_param *prm, t_px_col col, int y, t_coord wall);

/*	game -> move_and_rotate.c */
void			move_player(t_param *prm);
void			rotate_player(t_param *prm);

/*	game ->	print_game.c */
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
/*	parsing -> check_extension.c */
int				check_extension(char *file_name);

/*	parsing -> check_if_enclosed_in_walls_utils.c */
void			is_0_next_to_2(t_param *prm, char **map);

/*	parsing -> check_if_enclosed_in_walls.c */
void			check_if_enclosed_in_walls(t_param *prm, char **map);

/*	parsing -> check_map.c */
void			check_map(t_param *prm, char **map);

/*	parsing -> count_map.c */
int				count_number_of_lines(char **map);
int				count_max_width_of_lines(char **map);

/*	parsing	-> fd_to_color.c */
void			fd_to_color(t_param *prm, int fd, char *str);

/*	parsing	-> fd_to_card.c */
void			fd_to_card(t_param *prm, int fd, char *str);

/*	parsing	-> fd_to_map.c */
t_list			*fd_to_lst(t_param *prm, int fd);
char			**lst_to_tab(t_param *prm, t_list *lst, int fd);
void			fd_to_map(t_param *prm, int fd);

/*	parsing -> get_next_nonnull_line.c */
char			*get_next_nonnull_line(t_param *prm, int fd);

/*	parsing -> init_player_pos.c */
void			init_player_pos(t_param *prm);

/*	parsing -> parsing_error.c */
void			open_error(t_param *prm, char *msg);
int				check_map_error(t_param *prm, char *msg);
int				fd_to_map_error(t_param *prm, int fd, char *msg);

/*	parsing -> parsing_map.c */
void			parsing_map(t_param *prm, char *file_name);

/*	parsing -> parsing_utils.c */
void			trim_backslash_n(char *str);
char			*trim_str(t_param *prm, char *str);

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
/*	utils -> destroy_img.c */
void			destroy_images(t_param *prm);

/*	utils -> ft_exit.c */
int				close_win(void *p);
int				ft_exit(t_param *prm, int exit_code);

/*	utils -> import_img.c */
int				import_img(t_param *prm, t_img *xpm, char *path);

/*	utils -> utils.c */
int				get_nb_str(char **strs);
void			ft_swap(int *a, int *b);
void			print_map(t_param *prm);

/*	vector_manipulation	*/
/*	vector_manipulation -> get_distance.c */
double			get_distance(t_coord a, t_coord b);
int				ft_max(int a, int b);
int				ft_min(int a, int b);
double			ft_max_d(double a, double b);
double			ft_min_d(double a, double b);

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
