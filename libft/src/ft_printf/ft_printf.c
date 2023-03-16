/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlanza <jlanza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/20 15:13:00 by jlanza            #+#    #+#             */
/*   Updated: 2022/11/24 18:29:43 by jlanza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	check_arg(char c)
{
	if (c == 'c' || c == 's' || c == 'p' || c == 'd' || c == 'i' || c == 'u'
		|| c == 'x' || c == 'X' || c == '%')
		return (1);
	return (0);
}

int	convert_and_print(va_list ap, char *s)
{
	if (*s == 'c')
		return (print_char(va_arg(ap, int)));
	else if (*s == 's')
		return (print_str(va_arg(ap, char *)));
	else if (*s == 'p')
		return (print_addr((unsigned long)va_arg(ap, void *)));
	else if (*s == 'd' || *s == 'i')
		return (print_int(va_arg(ap, int)));
	else if (*s == 'u')
		return (print_unsigned(va_arg(ap, unsigned int)));
	else if (*s == 'x')
		return (print_hex(va_arg(ap, int)));
	else if (*s == 'X')
		return (print_hex_maj(va_arg(ap, int)));
	else if (*s == '%')
		return (print_char('%'));
	return (0);
}

int	ft_printf(const char *s, ...)
{
	va_list	ap;
	int		printed;

	printed = 0;
	va_start(ap, s);
	while (*s)
	{
		if (*s == '%')
		{
			if (check_arg(*((char *)s + 1)))
			{
				printed += convert_and_print(ap, ((char *)s + 1));
				s++;
			}
			else
				printed += print_char('%');
		}
		else
			printed += print_char(*s);
		s++;
	}
	va_end(ap);
	return (printed);
}
