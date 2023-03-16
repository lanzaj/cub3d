/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_arg.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlanza <jlanza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 17:46:42 by jlanza            #+#    #+#             */
/*   Updated: 2023/01/13 16:08:01 by jlanza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_hex(unsigned int nb)
{
	char	u;
	char	*hex;
	int		len;

	len = 1;
	hex = "0123456789abcdef";
	u = hex[nb % 16];
	if (nb >= 16)
	{
		nb = nb / 16;
		len = print_hex(nb) + 1;
	}
	write(1, &u, 1);
	return (len);
}

int	print_hex_maj(unsigned int nb)
{
	char	u;
	char	*hex;
	int		len;

	len = 1;
	hex = "0123456789ABCDEF";
	u = hex[nb % 16];
	if (nb >= 16)
	{
		nb = nb / 16;
		len = print_hex_maj(nb) + 1;
	}
	write(1, &u, 1);
	return (len);
}

int	print_addr_rec(unsigned long nb)
{
	char	u;
	char	*hex;
	int		len;

	len = 1;
	hex = "0123456789abcdef";
	u = hex[nb % 16];
	if (nb >= 16)
	{
		nb = nb / 16;
		len = print_addr_rec(nb) + 1;
	}
	write(1, &u, 1);
	return (len);
}

int	print_addr(unsigned long nb)
{
	if (nb == 0)
	{
		ft_putstr_fd(PTR_NULL, 1);
		return (ft_strlen(PTR_NULL));
	}
	ft_putstr_fd("0x", 1);
	return (2 + print_addr_rec(nb));
}
