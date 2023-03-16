/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlanza <jlanza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 16:45:20 by jlanza            #+#    #+#             */
/*   Updated: 2023/03/05 02:11:23 by jlanza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static char	is_partofset(char const c, char const *set)
{
	int	i_set;

	i_set = 0;
	while (set[i_set])
	{
		if (c == set[i_set])
			return (1);
		i_set++;
	}
	return (0);
}

static size_t	strimlen(char const *s1, char const *set)
{
	size_t	debut;
	size_t	fin;

	debut = 0;
	while (s1[debut] && is_partofset(s1[debut], set))
		debut++;
	fin = ft_strlen(s1) - 1;
	if (ft_strlen(s1) == 0)
		fin++;
	while (fin != 0 && is_partofset(s1[fin], set))
		fin--;
	if (fin < debut)
		return (0);
	return (fin - debut + 1);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*new;
	size_t	i;
	size_t	start;
	size_t	len;

	if (s1 == NULL)
		return (NULL);
	len = strimlen(s1, set);
	new = malloc ((len + 1) * sizeof (*new));
	if (new == NULL)
		return (NULL);
	start = 0;
	while (s1[start] && is_partofset(s1[start], set))
		start++;
	i = 0;
	while (i < len)
	{
		new[i] = s1[i + start];
		i++;
	}
	new[i] = '\0';
	return (new);
}
