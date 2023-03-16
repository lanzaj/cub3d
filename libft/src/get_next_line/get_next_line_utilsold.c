/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlanza <jlanza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 17:42:46 by jlanza            #+#    #+#             */
/*   Updated: 2023/01/13 15:39:39 by jlanza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	pos_end_line(char *s)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != '\n')
		i++;
	if (s[i] == '\n')
		return (i);
	return (-1);
}

char	*get_begin(char *s, int pos)
{
	char	*begin;
	int		i;

	if (s == NULL)
		return (NULL);
	if (pos == -1)
		return (s);
	begin = malloc (sizeof (*begin) * (2 + pos));
	if (begin == NULL)
		return (NULL);
	i = 0;
	while (i <= pos)
	{
		begin[i] = s[i];
		i++;
	}
	begin[i] = '\0';
	free(s);
	return (begin);
}

char	*get_end(char *src, char *dst, int pos)
{
	int		len;
	int		i;

	if (src == NULL)
		return (NULL);
	if (pos == -1)
	{
		dst[0] = '\0';
		return (dst);
	}
	pos++;
	len = 0;
	while (src[pos + len])
		len++;
	i = 0;
	while (src[pos + i])
	{
		dst[i] = src[pos + i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

int	ft_strlen2(const char *s)
{
	int			i;
	char		*str;

	str = (char *)s;
	if (s == NULL)
		return (0);
	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strjoin_gnl(char *s1, char const *s2)
{
	char	*new;
	int		i;
	int		len1;
	int		len2;

	len1 = ft_strlen2((char *)s1);
	len2 = ft_strlen2((char *)s2);
	new = malloc(sizeof(*new) * (len1 + len2 + 1));
	if (new == NULL)
		return (NULL);
	i = 0;
	while (i < len1)
	{
		new[i] = s1[i];
		i++;
	}
	while (i < len1 + len2)
	{
		new[i] = s2[i - len1];
		i++;
	}
	new[i] = '\0';
	if (s1 != NULL)
		free(s1);
	return (new);
}
