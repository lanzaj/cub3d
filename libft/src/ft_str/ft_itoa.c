/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlanza <jlanza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 14:12:09 by jlanza            #+#    #+#             */
/*   Updated: 2023/01/13 16:08:54 by jlanza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int	get_size(int n)
{
	int			len;
	long int	nbr;

	nbr = (long int)n;
	if (nbr < 0)
		nbr = -nbr;
	len = 0;
	while (nbr >= 10)
	{
		nbr = nbr / 10;
		len++;
	}
	return (len + 1);
}

static void	ft_itoa_rec(long int nbr, char *result, int i)
{
	i--;
	if (nbr >= 10)
		ft_itoa_rec(nbr / 10, result, i);
	result[i] = (nbr % 10) + '0';
}

char	*ft_itoa(int n)
{
	long int	nb;
	int			size_nbr;
	char		*result;

	size_nbr = get_size(n);
	nb = (long int)n;
	if (nb < 0)
	{
		result = malloc(sizeof(*result) * (size_nbr + 2));
		if (result == NULL)
			return (NULL);
		nb = -nb;
		ft_itoa_rec(nb, result + 1, size_nbr);
		result[0] = '-';
		result[size_nbr + 1] = '\0';
	}
	else
	{
		result = malloc(sizeof(*result) * (size_nbr + 1));
		if (result == NULL)
			return (NULL);
		ft_itoa_rec(nb, result, size_nbr);
		result[size_nbr] = '\0';
	}
	return (result);
}
