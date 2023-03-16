/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlanza <jlanza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 16:07:49 by jlanza            #+#    #+#             */
/*   Updated: 2023/01/13 16:09:16 by jlanza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*new;
	int		i;
	int		len12;
	int		len1;
	int		len2;

	len1 = (int)(ft_strlen((char *)s1));
	len2 = (int)(ft_strlen((char *)s2));
	len12 = len1 + len2;
	new = malloc(sizeof(*new) * (len12 + 1));
	if (new == NULL)
		return (NULL);
	i = 0;
	while (i < len1)
	{
		new[i] = s1[i];
		i++;
	}
	while (i < len12)
	{
		new[i] = s2[i - len1];
		i++;
	}
	new[i] = '\0';
	return (new);
}
