/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_alloc_gc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlanza <jlanza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 13:48:31 by mbocquel          #+#    #+#             */
/*   Updated: 2023/03/08 12:56:32 by jlanza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	*ft_malloc_gc(t_param *prm, int id, size_t size)
{
	void	*result;

	result = malloc(size);
	if (result == NULL)
		return (NULL);
	if (garbage_col(prm, id, result))
		return (NULL);
	return (result);
}

void	*ft_calloc_gc(t_param *prm, int id, size_t nmemb, size_t size)
{
	void	*result;

	result = ft_calloc(nmemb, size);
	if (result == NULL)
		return (NULL);
	if (garbage_col(prm, id, result))
		return (NULL);
	return (result);
}

char	*ft_substr_gc(t_param *prm, char *s, unsigned int start, size_t len)
{
	char	*result_str;
	size_t	i;
	size_t	len_max;

	len_max = len;
	if (ft_strlen(s) - start < len_max && start <= ft_strlen(s))
	{
		len_max = ft_strlen(s) - start;
	}
	else if (start > ft_strlen(s))
		len_max = 0;
	result_str = (char *)ft_calloc_gc(prm, prm->source.id,
			(len_max + 1), sizeof(char));
	if (result_str == NULL)
		return (NULL);
	i = 0;
	while (i < len_max)
	{
		result_str[i] = s[(size_t)start + i];
		i++;
	}
	result_str[i] = '\0';
	return (result_str);
}

char	*ft_strdup_gc(t_param *prm, int id, const char *s)
{
	char	*dest;
	int		i;
	int		len;

	i = 0;
	len = 0;
	while (s[len])
		len++;
	dest = (char *)ft_malloc_gc(prm, id, (len + 1) * sizeof(char));
	if (dest == NULL)
		return (NULL);
	while (s[i])
	{
		dest[i] = s[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strjoin_gc(t_param *prm, int id, char const *s1, char const *s2)
{
	char	*result_join;
	int		i;
	int		len[2];

	len[0] = 0;
	len[1] = 0;
	if (s1)
		len[0] = ft_strlen(s1);
	if (s2)
		len[1] = ft_strlen(s2);
	result_join = ft_calloc((len[0] + len[1] + 1), sizeof(char));
	if (result_join == NULL)
		return (NULL);
	i = -1;
	while (++i < len[0])
		result_join[i] = s1[i];
	while (i < len[0] + len[1])
	{
		result_join[i] = s2[i - len[0]];
		i++;
	}
	garbage_col(prm, id, (void *)result_join);
	return (result_join);
}
