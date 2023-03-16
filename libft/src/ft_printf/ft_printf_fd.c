/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlanza <jlanza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 14:58:01 by mbocquel          #+#    #+#             */
/*   Updated: 2023/02/27 18:02:36 by jlanza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf_fd(int fd, const char *str, ...)
{
	va_list	args;
	int		result_pf;
	int		i;

	result_pf = 0;
	i = -1;
	va_start(args, str);
	while (str[++i])
	{
		if (str[i] != '%')
			result_pf += ft_printf_fd_putchar(fd, str[i]);
		else
			result_pf += ft_printf_fd_process(fd, &args, &i, str);
	}
	va_end(args);
	return (result_pf);
}

int	ft_printf_fd_process(int fd, va_list *args, int *i, const char *str)
{
	(*i)++;
	if (str[*i] == 'c')
		return (ft_printf_fd_putchar(fd, va_arg(*args, int)));
	else if (str[*i] == 's')
		return (ft_printf_fd_putstr(fd, va_arg(*args, char *)));
	else if (str[*i] == 'p')
		return (ft_printf_fd_putptr(fd, va_arg(*args, void *)));
	else if (str[*i] == 'd' || str[*i] == 'i')
		return (ft_printf_fd_putnbr(fd, va_arg(*args, int)));
	else if (str[*i] == 'u')
		return (ft_printf_fd_put_usint(fd, va_arg(*args, unsigned int)));
	else if (str[*i] == 'x' || str[*i] == 'X')
		return (ft_printf_fd_putnbrhex(fd, va_arg(*args, unsigned int),
				str[*i]));
	else if (str[*i] == '%')
		return (ft_printf_fd_putchar(fd, '%'));
	return (-1);
}

int	ft_printf_fd_putnbrhex(int fd, unsigned int nb_hex, char x)
{
	char			*base;
	int				result;

	if (x == 'x')
		base = "0123456789abcdef";
	else
		base = "0123456789ABCDEF";
	result = 0;
	if (nb_hex < 16)
		result += ft_printf_fd_putchar(fd, base[nb_hex % 16]);
	else
	{
		result += ft_printf_fd_putnbrhex(fd, nb_hex / 16, x);
		result += ft_printf_fd_putchar(fd, base[nb_hex % 16]);
	}
	return (result);
}

int	ft_printf_fd_putnbrhex_ull(int fd, unsigned long long nb_hex, char x)
{
	char			*base;
	int				result;

	if (x == 'x')
		base = "0123456789abcdef";
	else
		base = "0123456789ABCDEF";
	result = 0;
	if (nb_hex < 16)
		result += ft_printf_fd_putchar(fd, base[nb_hex % 16]);
	else
	{
		result += ft_printf_fd_putnbrhex_ull(fd, nb_hex / 16, x);
		result += ft_printf_fd_putchar(fd, base[nb_hex % 16]);
	}
	return (result);
}
