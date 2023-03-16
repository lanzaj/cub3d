/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_fd_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlanza <jlanza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 11:06:38 by mbocquel          #+#    #+#             */
/*   Updated: 2023/02/27 18:02:44 by jlanza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf_fd_putchar(int fd, int c)
{
	int	n;

	n = write(fd, &c, 1);
	return (n);
}

int	ft_printf_fd_putstr(int fd, char *str)
{
	int	result;

	if (str == NULL)
		result = write(fd, "(null)", 6);
	else
		result = write(fd, str, ft_strlen(str));
	return (result);
}

int	ft_printf_fd_putptr(int fd, void *ptr)
{
	int	result;

	result = 0;
	if (ptr == NULL)
		result += write(fd, "(nil)", 5);
	else
	{
		result += ft_printf_fd_putstr(fd, "0x");
		result += ft_printf_fd_putnbrhex_ull(fd, (unsigned long long)ptr, 'x');
	}
	return (result);
}

int	ft_printf_fd_putnbr(int fd, int n)
{
	long int	nb;
	int			result;

	result = 0;
	nb = (long int)n;
	if (nb < 0)
	{
		nb = -nb;
		result += ft_printf_fd_putchar(fd, '-');
	}
	if (nb >= 10)
		result += ft_printf_fd_putnbr(fd, nb / 10);
	result += ft_printf_fd_putchar(fd, nb % 10 + '0');
	return (result);
}

int	ft_printf_fd_put_usint(int fd, unsigned int u_nbr)
{
	int				result;

	result = 0;
	if (u_nbr >= 10)
		result += ft_printf_fd_put_usint(fd, u_nbr / 10);
	result += ft_printf_fd_putchar(fd, u_nbr % 10 + '0');
	return (result);
}
