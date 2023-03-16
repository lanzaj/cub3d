/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_arg2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlanza <jlanza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 17:50:45 by jlanza            #+#    #+#             */
/*   Updated: 2022/11/23 12:51:07 by jlanza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_char(char c)
{
	ft_putchar_fd(c, 1);
	return (1);
}

int	print_str(char *s)
{
	if (s == NULL)
	{
		ft_putstr_fd("(null)", 1);
		return (ft_strlen("(null)"));
	}
	ft_putstr_fd(s, 1);
	return (ft_strlen(s));
}

int	get_len_nbr(int n)
{
	if (n <= -10 || n >= 10)
		return (1 + get_len_nbr(n / 10));
	if (n >= 0)
		return (1);
	return (2);
}

int	print_int(int n)
{
	ft_putnbr_fd(n, 1);
	return (get_len_nbr(n));
}

int	print_unsigned(unsigned int n)
{
	int		len;
	char	c;

	len = 1;
	if (n >= 10)
		len = 1 + print_unsigned(n / 10);
	c = n % 10 + '0';
	write(1, &c, 1);
	return (len);
}
