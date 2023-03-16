/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isint.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlanza <jlanza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 03:28:03 by jlanza            #+#    #+#             */
/*   Updated: 2023/03/01 03:28:35 by jlanza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_isint(char *s)
{
	int			i;
	int			j;
	long long	n;
	int			signe;

	n = 0;
	signe = 1;
	i = 0;
	while (('\t' <= s[i] && s[i] <= '\r') || s[i] == ' ')
		i++;
	if (s[i] == '-')
		signe = -1;
	if (s[i] == '-' || s[i] == '+')
		i++;
	if (s[i] < '0' || '9' < s[i])
		return (0);
	j = 0;
	while ('0' <= s[i + j] && s[i + j] <= '9')
	{
		n = n * 10 + (s[i + j] - '0');
		if (n * signe < INT_MIN || INT_MAX < n * signe)
			return (0);
		j++;
	}
	return (!s[i + j]);
}
