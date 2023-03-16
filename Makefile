# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jlanza <jlanza@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/06 10:48:53 by mbocquel          #+#    #+#              #
#    Updated: 2023/03/16 15:36:28 by jlanza           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

SOURCES_DIR = ./src/

BUILD_DIR = ./build/

SOURCES =	main.c

OBJECTS		= $(addprefix ${BUILD_DIR}, ${SOURCES:.c=.o})

DEPS := $(OBJECTS:.o=.d)

CC = cc

CFLAGS = -Wall -Wextra -Werror -MMD -MP

RM = rm -rf

LIBFT_DIR = libft/
LIBMLX_DIR = minilibx-linux/

CLIB = -Llibft -lft -Llibmlx -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz

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

clean:
	$(RM) $(BUILD_DIR)
	make clean -C $(LIBFT_DIR)

fclean: clean
	$(RM)  $(NAME)
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
