/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlanza <jlanza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 11:57:06 by jlanza            #+#    #+#             */
/*   Updated: 2023/01/13 16:09:40 by jlanza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i_b;
	size_t	i_l;
	char	*b;
	char	*l;

	b = (char *)big;
	l = (char *)little;
	if (*l == 0)
		return (b);
	i_b = 0;
	while (b[i_b] && i_b < len)
	{
		i_l = 0;
		while (b[i_b + i_l] == l[i_l] && (i_b + i_l) < len)
		{
			i_l++;
			if (l[i_l] == '\0')
				return (&b[i_b]);
		}
		i_b++;
	}
	return (NULL);
}
