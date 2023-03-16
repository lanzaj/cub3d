/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlanza <jlanza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 14:38:30 by jlanza            #+#    #+#             */
/*   Updated: 2023/01/13 16:07:22 by jlanza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*memory;
	size_t	i;
	size_t	size_max;

	size_max = -1;
	if (nmemb == 0 || size == 0)
		return (ft_calloc(1, 1));
	if (nmemb > size_max / size)
		return (NULL);
	memory = malloc(nmemb * size);
	if (memory == NULL)
		return (NULL);
	i = 0;
	while (i < nmemb * size)
	{
		((unsigned char *)memory)[i] = '\0';
		i++;
	}
	return (memory);
}
