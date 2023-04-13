/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlanza <jlanza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 15:18:36 by jlanza            #+#    #+#             */
/*   Updated: 2023/04/13 09:58:29 by jlanza           ###   ########.fr       */
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
# include <float.h>
# include <sys/time.h>
# include <fcntl.h>
# define KEY_LEFT_ARROW 65361
# define KEY_RIGHT_ARROW 65363
# define KEY_A 97
# define KEY_W 119
# define KEY_S 115
# define KEY_D 100
# define KEY_M 109
# define KEY_SPACE 32
# define KEY_TAB 65289
# define KEY_CTRL 65507
# define KEY_SHIFT 65505
# define KEY_M 109
# define KEY_F 102
# define KEY_ESC 0xFF1B
# define LOOP 150
# define TIME_CLOSE_DOOR 100
# define SPEED_MOVE_DOOR 20
# define MOUSE_ROLL_ZOOM 4
# define MOUSE_ROLL_UNZOOM 5
# define MOUSE_SPEED 8000
# define FPS 25
# define PI 3.14159f
# define DIST_DOOR 1.5f
# define BUF 0.2f
# define BUF_ENEMY 0.45f
# define LIFE_NUMBER 4
# define SHOOT_FRAME 3
# define SHOOT_ANG 0.14f
# define SHOOT_DST_SQ 25

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
/*	game -> door_close.c */
void			change_door_status(t_param *prm);

/*	game -> door_open.c */
void			find_door_to_open(t_param *prm);

/*	game -> enemy_in_room.c */
t_bool			we_are_in_same_room(t_param *prm, t_sprite *sprite);

/*	game -> enemy_move_utils.c */
t_coord			pos_buff_enemy(t_param *prm, t_coord pos, double ang_move);
t_coord			get_wanted_move_dir_enemy(double ang);

/*	game -> enemy_move.c */
void			move_all_enemies(t_param *prm);
t_bool			is_valid_move_enemy(t_param *prm, t_coord pos);

/*	game -> event_handle.c */
int				key_press(int keycode, void *p);
int				key_release(int keycode, void *p);

/*	game -> game_loop.c */
int				game_loop(t_param *prm);

/*	game -> get_color_to_print_door.c */
double			pos_impact_door(t_param *prm, t_coord point);
void			init_tab_xpm(t_param *prm);
int				get_texture_px_color_door(t_param *prm,
					t_coord wall, double pos_y);
int				get_color_px_door(t_param *prm,
					t_px_col col, int y, t_coord wall);

/*	game -> get_color_to_print.c */
double			pos_impact(t_param *prm, t_coord point);
int				get_texture_px_color(t_param *prm, t_coord wall, double pos_y);
int				get_color_px(t_param *prm, t_px_col col,
					t_coord_int coord, t_coord wall);

/*	game -> get_type_of_wall.c */
t_dir			get_type_of_wall(t_param *prm, t_coord point);
t_dir			get_type_of_wall_part_2(t_param *prm, t_coord point);
t_dir			get_type_of_wall_part_3(t_param *prm, t_coord point);
t_dir			get_type_of_wall_part_4(t_param *prm, t_coord point);
t_dir			get_type_of_wall_part_5(t_param *prm, t_coord point);

/*	game -> impact_raycast.c */
int				allocate_impact_tab(t_param *prm);
void			update_impact_tab(t_param *prm);
void			update_impact_tab_part2(t_param *prm);

/*	game -> mouse_event.c */
int				handle_mouse_move(int x, int y, void *param);
int				handle_mouse_click(int button, int x, int y, void *p);

/*	game -> move.c */
void			move_player(t_param *prm);
t_coord			get_wanted_move_dir(t_param *prm);
t_coord			pos_buff(t_param *prm, t_coord pos);
int				is_valid_move(t_param *prm, t_coord pos);

/*	game ->	print_door.c */
int				find_door(t_param *prm, t_coord door);
void			init_col_px_door(t_param *prm,
					t_coord door, double ang, t_px_col *col);
void			print_door_slice(t_param *prm, int x,
					t_coord door, double ang);

/*	game ->	print_floor_and_sky.c */
void			print_floor_and_sky(t_param *prm, int sky, int floor);

/*	game ->	print_game.c */
void			initiate_img_game(t_param *prm);
void			init_col_px(t_param *prm, t_coord wall,
					double ang, t_px_col *col);
void			print_wall_slice(t_param *prm, int x, t_coord wall, double ang);
void			print_game(t_param *prm);

/*	game ->	print_gun.c */
void			init_gun(t_param *prm);
void			print_gun(t_param *prm);

/*	game ->	print_heart.c */
void			init_life(t_param *prm);
void			print_health_bar(t_param *prm, int x, int y);

/*	game ->	print_screen_1.c */
void			print_red(t_param *prm);
void			print_game_over(t_param *prm);
void			print_win(t_param *prm);
void			print_start(t_param *prm);
void			print_pause(t_param *prm);

/*	game ->	print_screen_2.c */
void			print_special_screen(t_param *prm);
void			update_red_color(t_param *prm);
int				fade_to_dark(t_param *prm);
int				fade_to_dark_start_screen(t_param *prm);

/*	game ->	print_sprites_1.c */
int				put_img_to_front(t_param *prm, t_img *xpm, int dx, t_sprite *s);
double			get_angle_with_player_view(t_param *prm, t_coord sprite);
void			explode(t_param *prm, t_sprite *sprite);
void			ai_enemies(t_param *prm, t_sprite *sprite, int seen);
void			do_gun_damage(t_param *prm, t_sprite *sprite,
					int dx, int seen);

/*	game ->	print_sprites_2.c */
void			kill_baril(t_param *prm, t_sprite *sprite,
					double theta, int dx);
void			kill_enemies(t_param *prm, t_sprite *sprite,
					double theta, int dx);
void			collect_health(t_param *prm, t_sprite *sprite);
void			print_sprite(t_param *prm, t_sprite *sprite, t_img *xpm);
void			select_sprite(t_param *prm, t_sprite *sprite);

/*	game ->	print_sprites_3.c */
void			print_every_sprite(t_param *prm);
void			init_col_px_sprite(t_param *prm, t_coord sprite, t_px_col *col);
int				check_distance_x(t_param *prm, t_coord sprite, t_coord_int i);
int				check_distance_y(t_param *prm, t_coord sprite, t_coord_int i);

/*	game ->	print_sprites_4.c */
void			init_boundary_part2(t_param *prm, t_img *xpm, t_boundary *b);
void			init_boundary(t_param *prm, t_img *xpm, t_boundary *b, int dx);
int				put_on_one_pixel(t_param *prm, t_img *xpm,
					t_boundary b, t_sprite *s);

/*	game ->	rotate.c */
double			angle_move(t_param *prm);
void			rotate_player(t_param *prm);

/*	minimap	*/
/*	minimap -> print_minimap_utils.c */
void			put_px_minimap(t_param *prm, t_point p, int color);
t_bool			mm_is_wall_or_out(t_param *prm, t_coord coord);
t_bool			mm_is_door(t_param *prm, t_coord coord);

/*	minimap -> print_minimap_window.c */
void			print_window_minimap(t_param *prm, int x, int y);

/*	minimap -> print_minimap.c */
void			initiate_img_minimap(t_param *prm);
void			init_print_mimimap(t_param *prm, t_point *p,
					t_point *middle, t_coord *new_orig);
void			print_minimap(t_param *prm);
void			print_player(t_param *prm);

/*	mlx_functions	*/
/*	mlx_functions -> get_color.c */
int				get_color(t_img *xpm, int x, int y);
int				get_fade_color(t_img *xpm, int x, int y);
int				get_grey_color(t_param *prm, t_img *xpm, int x, int y);
int				*get_red_color(void);
int				get_darken_color(t_img *xpm, t_coord_int coord,
					double dist, int *red_color);

/*	mlx_functions -> get_color_2.c */
int				darken_color(int color, t_coord wall, t_coord player);
int				darken_color_floor(int color, int x);
int				red_filter(t_param *prm, t_coord_int coord);

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

/*	mlx_functions -> pixel_put_img.c */
int				pixel_put_img(t_img *img, t_point pixel);

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

/*	parsing	-> fd_to_map_2.c */
t_list			*fd_to_lst(t_param *prm, int fd);
char			**lst_to_tab(t_param *prm, t_list *lst, int fd);

/*	parsing	-> fd_to_map.c */
void			fd_to_map(t_param *prm, int fd);

/*	parsing -> get_next_nonnull_line.c */
char			*get_next_nonnull_line(t_param *prm, int fd);

/*	parsing -> init_player_pos.c */
void			init_player_pos(t_param *prm);

/*	parsing -> init_sprites_pos.c */
void			init_sprites(t_param *prm);

/*	parsing -> parsing_doors.c */
int				get_id_door(t_param *prm, int x, int y);
int				init_doors_tab(t_param *prm);
t_door_status	status_door(t_param *prm, int x, int y);

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

/*	rayracing -> find_first_wall_only.c */
t_coord			find_first_h_w_only(t_param *prm, double ray_ang);
t_coord			find_first_h_part_2_w_only(t_param *prm, double ray_ang);
t_coord			find_first_v_w_only(t_param *prm, double ray_ang);
t_coord			find_first_v_part_2_w_only(t_param *prm, double ray_ang);

/*	rayracing -> find_wall.c */
t_coord			find_wall_h_w_only(t_param *prm,
					double ray_ang, t_coord first_h);
void			find_wall_h_part_2_w_only(t_param *prm,
					double ray_ang, t_coord *delt_h);
t_coord			find_wall_v_w_only(t_param *prm,
					double ray_ang, t_coord first_v);
void			find_wall_v_part_2_w_only(t_param *prm,
					double ray_ang, t_coord *delt_v);
t_coord			find_wall_only(t_param *prm, double ray_ang);

/*	rayracing -> hit_a_wall.c */
int				is_valid_coord(t_param *prm, t_coord coord);
int				has_hit_a_door(t_param *prm, t_coord point);
int				has_hit_a_wall(t_param *prm, t_coord point);
int				has_hit_a_wall_or_door(t_param *prm, t_coord point);
int				has_hit_a_closed_door(t_param *prm, t_coord point);

/*	utils	*/
/*	utils -> destroy_img.c */
void			destroy_images(t_param *prm);

/*	utils -> enter_leave_win.c */
int				leave_window(void *p);
int				enter_window(void *p);

/*	utils -> ft_lstsort.c */
void			ft_lstsort(t_param *prm, t_list *lst,
					int (*fcmp)(t_param *prm, t_list *a, t_list *b));
int				cmp_distance(t_param *prm, t_list *a, t_list *b);

/*	utils -> ft_exit.c */
void			leave_win(void *p);
int				close_win(void *p);
int				ft_exit(t_param *prm, int exit_code);
int				ft_exit_error(t_param *prm, int exit_code);

/*	utils -> import_img.c */
int				import_img(t_param *prm, t_img *xpm, char *path);

/*	utils -> max_min.c */
int				ft_max(int a, int b);
int				ft_min(int a, int b);
double			ft_max_d(double a, double b);
double			ft_min_d(double a, double b);
double			v_abs_dbl(double a);

/*	utils -> utils.c */
int				get_nb_str(char **strs);
void			ft_swap(int *a, int *b);
void			print_map(t_param *prm);

/*	vector_manipulation	*/
/*	vector_manipulation -> get_distance.c */
double			get_distance(t_coord a, t_coord b);
double			get_distance_square(t_coord a, t_coord b);
double			get_distance_point(t_point a, t_point b);

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
