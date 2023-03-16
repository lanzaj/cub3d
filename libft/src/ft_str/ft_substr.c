/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlanza <jlanza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 15:43:24 by jlanza            #+#    #+#             */
/*   Updated: 2023/01/13 16:09:52 by jlanza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static size_t	get_len(char *s, unsigned int start, size_t len)
{
	size_t	i;

	i = 0;
	while (s[i + start] && i < len)
		i++;
	return (i);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*new_str;
	size_t	i;

	if (ft_strlen(s) < start)
	{
		new_str = malloc((size_t)(sizeof(*new_str)) * 1);
		if (!new_str)
			return (NULL);
		new_str[0] = '\0';
		return (new_str);
	}
	len = get_len((char *)s, start, len);
	new_str = malloc ((size_t)(sizeof(*new_str)) * (len + 1));
	if (new_str == NULL)
		return (NULL);
	i = 0;
	while (i < len)
	{
		new_str[i] = s[(size_t)start + i];
		i++;
	}
	new_str[i] = '\0';
	return (new_str);
}
