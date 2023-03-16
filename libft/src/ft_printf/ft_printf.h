/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlanza <jlanza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/20 15:03:52 by jlanza            #+#    #+#             */
/*   Updated: 2023/02/27 17:59:32 by jlanza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# if defined (__APPLE__)
#  define PTR_NULL "0x0"
# elif __linux__
#  define PTR_NULL "(nil)"
# endif

# include <stdarg.h>
# include "../libft.h"

int	print_char(char c);
int	print_str(char *s);
int	print_hex(unsigned int nb);
int	print_hex_maj(unsigned int nb);
int	print_addr(unsigned long nb);

int	get_len_nbr(int n);
int	print_int(int n);
int	print_unsigned(unsigned int n);

int	check_arg(char c);
int	convert_and_print(va_list ap, char *s);
int	ft_printf(const char*str, ...);

int	ft_printf_fd_putchar(int fd, int c);
int	ft_printf_fd_putstr(int fd, char *str);
int	ft_printf_fd_putptr(int fd, void *ptr);
int	ft_printf_fd_putnbr(int fd, int n);
int	ft_printf_fd_put_usint(int fd, unsigned int u_nbr);
int	ft_printf_fd_process(int fd, va_list *args, int *i, const char *str);
int	ft_printf_fd_putnbrhex(int fd, unsigned int nb_hex, char x);
int	ft_printf_fd_putnbrhex_ull(int fd, unsigned long long nb_hex, char x);
int	ft_printf_fd(int fd, const char *str, ...);

#endif
