/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlanza <jlanza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 15:26:31 by jlanza            #+#    #+#             */
/*   Updated: 2023/03/13 14:18:19 by jlanza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strdup(const char *s)
{
	char	*dest;
	char	*src;
	int		i;

	src = (char *)s;
	i = 0;
	if (s == NULL)
		return (NULL);
	dest = malloc(sizeof(*dest) * ((int)((ft_strlen(src))) + 1));
	if (dest == NULL)
		return (dest);
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = src[i];
	return (dest);
}
