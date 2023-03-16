# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mbocquel <mbocquel@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/11 14:11:32 by mbocquel          #+#    #+#              #
#    Updated: 2023/03/10 14:10:55 by mbocquel         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SOURCES_DIR = ./src/

BUILD_DIR = ./build/

MY_SOURCES =	ft_is/ft_isalpha.c \
				ft_is/ft_isdigit.c \
				ft_is/ft_isalnum.c \
				ft_is/ft_isascii.c \
				ft_is/ft_isprint.c \
				ft_is/ft_isspace.c \
				ft_is/ft_isint.c \
				ft_str/ft_strlen.c \
				ft_str/ft_strlcpy.c \
				ft_str/ft_strlcat.c \
				ft_str/ft_strchr.c \
				ft_str/ft_strrchr.c \
				ft_str/ft_strcmp.c \
				ft_str/ft_strncmp.c \
				ft_str/ft_strnstr.c \
				ft_str/ft_strdup.c \
				ft_str/ft_strjoin.c \
				ft_str/ft_strtrim.c \
				ft_str/ft_strmapi.c \
				ft_str/ft_striteri.c \
				ft_str/ft_substr.c \
				ft_str/ft_toupper.c \
				ft_str/ft_tolower.c \
				ft_str/ft_itoa.c \
				ft_str/ft_atoi.c \
				ft_str/ft_split.c \
				ft_mem/ft_bzero.c \
				ft_mem/ft_calloc.c \
				ft_mem/ft_memset.c \
				ft_mem/ft_memcpy.c \
				ft_mem/ft_memmove.c \
				ft_mem/ft_memchr.c \
				ft_mem/ft_memcmp.c \
				ft_put/ft_putchar_fd.c \
				ft_put/ft_putstr_fd.c \
				ft_put/ft_putendl_fd.c \
				ft_put/ft_putnbr_fd.c \
				ft_lst/ft_lstadd_front.c \
				ft_lst/ft_lstnew.c \
				ft_lst/ft_lstsize.c \
				ft_lst/ft_lstlast.c \
				ft_lst/ft_lstadd_back.c \
				ft_lst/ft_lstdelone.c \
				ft_lst/ft_lstclear.c \
				ft_lst/ft_lstiter.c \
				ft_lst/ft_lstmap.c \
				get_next_line/get_next_line.c \
				get_next_line/get_next_line_utils.c \
				ft_printf/ft_printf.c \
				ft_printf/ft_printf_utils.c \
				ft_printf/ft_printf_utils2.c \
				ft_printf/ft_printf_fd.c \
				ft_printf/ft_printf_fd_utils.c

MY_OBJECTS = $(addprefix ${BUILD_DIR}, ${MY_SOURCES:.c=.o})

DEPS := $(MY_OBJECTS:.o=.d)

CC = cc

CFLAGS = -Wall -Wextra -Werror -MMD -MP

RM = rm -rf

all: $(NAME)

$(BUILD_DIR)%.o : $(SOURCES_DIR)%.c
	@mkdir -p $(dir $@)
	@$(CC) -c $(CFLAGS) -c $< -o $@
	@echo "	Compiling " $<

$(NAME): $(MY_OBJECTS)
	@ar rc $(NAME) $(MY_OBJECTS)
	@ranlib $(NAME)
	@echo "Creating "$(NAME)

clean:
	$(RM) $(BUILD_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

-include $(DEPS)
