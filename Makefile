# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mbocquel <mbocquel@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/06 10:48:53 by mbocquel          #+#    #+#              #
#    Updated: 2023/03/29 14:15:58 by mbocquel         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

NAME_BONUS = cub3D_bonus

SOURCES_DIR = ./src/

BUILD_DIR = ./build/

SOURCES =	alloc_garbage/ft_alloc_gc.c \
			alloc_garbage/garbage_2.c \
			alloc_garbage/garbage.c \
			game/event_handle.c \
			game/game_loop.c \
			game/get_color_to_print.c \
			game/move_and_rotate.c \
			game/print_game.c \
			minimap/print_minimap.c \
			mlx_functions/mlx_print_seg.c \
			mlx_functions/mlx_utils.c \
			mlx_functions/mlx_color.c \
			raytracing/find_first.c \
			raytracing/find_wall.c \
			raytracing/hit_a_wall.c \
			parsing/check_extension.c \
			parsing/check_if_enclosed_in_walls_utils.c \
			parsing/check_if_enclosed_in_walls.c \
			parsing/check_map.c \
			parsing/count_map.c \
			parsing/fd_to_card.c \
			parsing/fd_to_color.c \
			parsing/fd_to_map.c \
			parsing/get_next_nonnull_line.c \
			parsing/init_player_pos.c \
			parsing/parsing_error.c \
			parsing/parsing_map.c \
			parsing/parsing_utils.c \
			utils/destroy_img.c \
			utils/ft_exit.c \
			utils/import_img.c \
			utils/utils.c \
			vector_manipulation/matrix_vector_calc.c \
			vector_manipulation/projection_minimap.c \
			vector_manipulation/get_distance.c \
			main.c
			
SOURCES_BONUS =	bonus/alloc_garbage/ft_alloc_gc.c \
				bonus/alloc_garbage/garbage_2.c \
				bonus/alloc_garbage/garbage.c \
				bonus/game/event_handle.c \
				bonus/game/game_loop.c \
				bonus/game/get_color_to_print.c \
				bonus/game/move_and_rotate.c \
				bonus/game/print_game.c \
				bonus/minimap/print_minimap.c \
				bonus/mlx_functions/mlx_print_seg.c \
				bonus/mlx_functions/mlx_utils.c \
				bonus/mlx_functions/mlx_color.c \
				bonus/raytracing/find_first.c \
				bonus/raytracing/find_wall.c \
				bonus/raytracing/hit_a_wall.c \
				bonus/parsing/check_extension.c \
				bonus/parsing/check_if_enclosed_in_walls_utils.c \
				bonus/parsing/check_if_enclosed_in_walls.c \
				bonus/parsing/check_map.c \
				bonus/parsing/count_map.c \
				bonus/parsing/fd_to_card.c \
				bonus/parsing/fd_to_color.c \
				bonus/parsing/fd_to_map.c \
				bonus/parsing/get_next_nonnull_line.c \
				bonus/parsing/init_player_pos.c \
				bonus/parsing/parsing_error.c \
				bonus/parsing/parsing_map.c \
				bonus/parsing/parsing_utils.c \
				bonus/utils/destroy_img.c \
				bonus/utils/ft_exit.c \
				bonus/utils/import_img.c \
				bonus/utils/utils.c \
				bonus/vector_manipulation/matrix_vector_calc.c \
				bonus/vector_manipulation/projection_minimap.c \
				bonus/vector_manipulation/get_distance.c \
				bonus/main.c

OBJECTS		= $(addprefix ${BUILD_DIR}, ${SOURCES:.c=.o})

OBJECTS_BONUS		= $(addprefix ${BUILD_DIR}, ${SOURCES_BONUS:.c=.o})

DEPS := $(OBJECTS:.o=.d)

DEPS_BONUS := $(OBJECTS_BONUS:.o=.d)

CC = cc

CFLAGS = -Wall -Wextra -Werror -MMD -MP -g3

RM = rm -rf

LIBFT_DIR = libft/

LIBMLX_DIR = mlx_linux/

CLIB = -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz \
		-Llibft -lft
all: $(NAME)

$(BUILD_DIR)%.o: $(SOURCES_DIR)%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "\e[32mCompiling \e[0m" $<

$(NAME):	$(OBJECTS)
			@echo
			@make -C $(LIBFT_DIR)
			@make -C $(LIBMLX_DIR)
			@$(CC) $(CFLAGS) $(OBJECTS) $(CLIB) -o $(NAME)
			@echo "\nCreating ./"$(NAME)
			@echo "\n		      ALL DONE THANKS!\e[36m"
			@echo "		⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣠⣤⣤⣄⣀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀"
			@echo "		⠀⠀⠀⠀⠀⠀⠀⠀⠀⢠⣾⣿⣿⣿⣿⣿⣿⣷⡄⠀⠀⠀⠀⠀⠀⠀⠀⠀"
			@echo "		⠀⠀⠀⠀⠀⠀⠀⠀⢀⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡄⠀⠀⠀⠀⠀⠀⠀⠀"
			@echo "		⠀⠀⠀⠀⠀⠀⠀⠀⢸⣿⣿⡿⠇⠀⠀⠸⢿⣿⣿⡇⠀⠀⠀⠀⠀⠀⠀⠀"
			@echo "		⠀⠀⠀⠀⠀⠀⠀⣤⣾⣿⣿⣿⣦⡀⢀⣴⣿⣿⣿⣷⣤⠀⠀⠀⠀⠀⠀⠀"
			@echo "		⠀⠀⠀⠀⠀⠀⠀⠹⣿⣿⠁⠈⠙⣷⣾⠋⠁⠈⣿⣿⠏⠀⠀⠀⠀⠀⠀⠀"
			@echo "		⠀⠀⠀⠀⠀⠀⠀⠀⠈⢻⣷⣶⣶⣿⣿⣶⣶⣾⡟⠁⠀⠀⠀⠀⠀⠀⠀⠀"
			@echo "		⠀⠀⠀⠀⠀⠀⠀⠀⠀⣦⣙⢿⣿⣿⣿⣿⡿⣋⣴⠀⠀⠀⠀⠀⠀⠀⠀⠀"
			@echo "		⠀⠀⠀⠀⠀⠀⠀⢀⣀⣽⣿⣿⣮⡉⢩⣷⣿⣿⣯⣀⡀⠀⠀⠀⠀⠀⠀⠀"
			@echo "		⠀⠀⠀⠀⠀⣰⣾⣿⣿⣿⣿⣿⣿⣿⣾⣿⣿⣿⣿⣿⣿⣷⣄⠀⠀⠀⠀⠀"
			@echo "		⠀⠀⠀⠀⣴⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣧⠀⠀⠀⠀"
			@echo "		⠀⠀⣀⣼⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣧⣀⠀⠀"
			@echo "		⢀⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡀"
			@echo "		⢺⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⢿⣿⣿⡿⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿"
			@echo "		⠀⠙⠿⠿⠿⠿⠿⢿⣿⣿⣶⣦⣴⣿⣷⣦⣴⣾⣿⣿⣿⠿⠿⠟⠿⠿⠛⠀"
			@echo "		⠀⠀⠀⠀⠀⠀⠀⠘⠿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⠇⠀⠀⠀⠀⠀⠀⠀"
			@echo "		⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠉⠙⠛⠛⠛⠛⠋⠉⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\e[0m"

$(NAME_BONUS): bonus

bonus:		$(OBJECTS_BONUS)
			@echo
			@make -C $(LIBFT_DIR)
			@make -C $(LIBMLX_DIR)
			@$(CC) $(CFLAGS) $(OBJECTS_BONUS) $(CLIB) -o $(NAME_BONUS)
			@echo "\nCreating ./"$(NAME_BONUS)
			@echo "\n		      ALL DONE THANKS!\e[36m"
			@echo "		⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣠⣤⣤⣄⣀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀"
			@echo "		⠀⠀⠀⠀⠀⠀⠀⠀⠀⢠⣾⣿⣿⣿⣿⣿⣿⣷⡄⠀⠀⠀⠀⠀⠀⠀⠀⠀"
			@echo "		⠀⠀⠀⠀⠀⠀⠀⠀⢀⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡄⠀⠀⠀⠀⠀⠀⠀⠀"
			@echo "		⠀⠀⠀⠀⠀⠀⠀⠀⢸⣿⣿⡿⠇⠀⠀⠸⢿⣿⣿⡇⠀⠀⠀⠀⠀⠀⠀⠀"
			@echo "		⠀⠀⠀⠀⠀⠀⠀⣤⣾⣿⣿⣿⣦⡀⢀⣴⣿⣿⣿⣷⣤⠀⠀⠀⠀⠀⠀⠀"
			@echo "		⠀⠀⠀⠀⠀⠀⠀⠹⣿⣿⠁⠈⠙⣷⣾⠋⠁⠈⣿⣿⠏⠀⠀⠀⠀⠀⠀⠀"
			@echo "		⠀⠀⠀⠀⠀⠀⠀⠀⠈⢻⣷⣶⣶⣿⣿⣶⣶⣾⡟⠁⠀⠀⠀⠀⠀⠀⠀⠀"
			@echo "		⠀⠀⠀⠀⠀⠀⠀⠀⠀⣦⣙⢿⣿⣿⣿⣿⡿⣋⣴⠀⠀⠀⠀⠀⠀⠀⠀⠀"
			@echo "		⠀⠀⠀⠀⠀⠀⠀⢀⣀⣽⣿⣿⣮⡉⢩⣷⣿⣿⣯⣀⡀⠀⠀⠀⠀⠀⠀⠀"
			@echo "		⠀⠀⠀⠀⠀⣰⣾⣿⣿⣿⣿⣿⣿⣿⣾⣿⣿⣿⣿⣿⣿⣷⣄⠀⠀⠀⠀⠀"
			@echo "		⠀⠀⠀⠀⣴⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣧⠀⠀⠀⠀"
			@echo "		⠀⠀⣀⣼⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣧⣀⠀⠀"
			@echo "		⢀⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡀"
			@echo "		⢺⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⢿⣿⣿⡿⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿"
			@echo "		⠀⠙⠿⠿⠿⠿⠿⢿⣿⣿⣶⣦⣴⣿⣷⣦⣴⣾⣿⣿⣿⠿⠿⠟⠿⠿⠛⠀"
			@echo "		⠀⠀⠀⠀⠀⠀⠀⠘⠿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⠇⠀⠀⠀⠀⠀⠀⠀"
			@echo "		⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠉⠙⠛⠛⠛⠛⠋⠉⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\e[0m"

clean:
	$(RM) $(BUILD_DIR)
	make clean -C $(LIBFT_DIR)
	make clean -C $(LIBMLX_DIR)

fclean: clean
	$(RM)  $(NAME) $(NAME_BONUS)
	make fclean -C $(LIBFT_DIR)

re: fclean all

avatar:
	@echo "\n			Water. Earth. Fire. Air.\n"
	@echo "	\e[32mLong ago, the four nations lived together in harmony."
	@echo "	Then everything changed when the Fire Nation attacked"
	@echo "	Only the Avatar, master of all four elements, could stop"
	@echo "	them. But when the world needed him most, he vanished.\n"
	@echo "	A hundred years passed and my brother and I discovered"
	@echo "	the new Avatar, an airbender named Aang, and although"
	@echo "	his airbending skills are great, he still has a lot to"
	@echo "	learn before he's ready to save anyone.\n"
	@echo "	But I believe Aang can save the world.\e[0m\n"
	@echo "		⠀⠀⠀⠀⠀⠀⠀⠀⢀⠔⣪⣿⡿⠋⠉⠀⢄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀"
	@echo "		⡇⠀⠀⠀⠀⢀⣼⣿⠟⠉⠉⠙⢰⣇⠀⠀⠀⢻⡆⠀⣀⠀⠀⠀⠀⠀⠀⠀⠀⠀"
	@echo "		⣷⡀⢀⢤⣤⣾⣿⣿⣤⣤⠄⠀⠘⣿⣆⠀⠀⠀⢧⠀⠈⢷⡄⠀⠀⠀⠀⠀⠀⠀"
	@echo "		⠙⠿⠇⠀⢻⣿⣿⡿⠋⠀⠀⠀⢸⣿⠏⠂⠀⠀⠀⠀⠀⠀⠃⠐⠀⠀⠀⠀⠀⠀"
	@echo "		⠀⠰⠀⠀⠀⠙⠉⠀⠀⠀⠀⠀⠀⠀⢠⠀⠀⠀⠀⠀⠀⠀⢀⠀⠁⠀⠀⠀⠀⠀"
	@echo "		⠀⠀⠣⢤⣀⠀⠀⠀⣀⣠⣴⡦⡶⠚⠥⠆⠀⠀⠀⠀⠀⢰⡄⠀⡄⠀⠀⠀⠀⠀"
	@echo "		⠀⠀⠀⢸⢹⣭⣭⣭⣵⣦⠜⠁⠈⣦⡀⠀⠀⠀⠀⡆⠀⠘⠀⠀⣿⡄⠀⠀⠀⠀"
	@echo "		⠀⠀⠀⠀⠙⠿⢿⡿⠿⣯⣤⣴⣾⣿⣧⠀⠀⠀⢠⠁⠀⢸⠀⠀⡟⣿⣦⣀⠀⠀"
	@echo "		⠀⠀⠀⠀⠀⠀⠀⡉⠀⠀⢙⢉⣝⣉⠙⠀⠀⠀⣆⣀⣀⣠⣀⣼⡷⠤⠽⠛⠛⠃"
	@echo "		⠀⠀⠀⠀⠀⠀⠘⠛⠛⠛⠊⠈⠉⠉⠿⢷⣿⠾⠿⠛⠛⠛⠁⠀⠀⠀⠀⠀⠀⠀\n"

.PHONY: all clean fclean re

-include $(DEPS)
-include $(DEPS_BONUS)
