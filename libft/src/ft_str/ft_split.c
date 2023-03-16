/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlanza <jlanza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 14:11:35 by jlanza            #+#    #+#             */
/*   Updated: 2023/01/22 23:10:45 by jlanza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	**free_tab(char **tab)
{
	int	i;

	if (tab == NULL)
		return (NULL);
	i = 0;
	while (tab[i] != NULL)
	{
		free(tab[i]);
		i++;
	}
	free(tab[i]);
	free(tab);
	return (NULL);
}

static int	count_words(char *str, char c)
{
	int	i;
	int	is_word;
	int	nbr_word;

	i = 0;
	is_word = 0;
	nbr_word = 0;
	while (str[i])
	{
		if (str[i] != c)
			is_word = 1;
		if (str[i] == c && is_word)
		{
			is_word = 0;
			nbr_word++;
		}
		i++;
	}
	if (is_word)
		nbr_word++;
	return (nbr_word);
}

static int	len_word(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] && !(str[i] == c))
	{
		i++;
	}
	return (i);
}

static char	*fill_word(char *str, char c, char *tab)
{
	int	word_len;
	int	i;

	tab = malloc(sizeof(char) * (len_word(str, c) + 1));
	if (tab == NULL)
		return (NULL);
	word_len = len_word(str, c);
	i = 0;
	while (i < word_len)
	{
		tab[i] = str[i];
		i++;
	}
	tab[i] = '\0';
	return (tab);
}

char	**ft_split(char const *s, char c)
{
	char	**tab;
	char	*str;
	int		i;
	int		it;

	str = (char *)s;
	tab = ft_calloc(count_words((char *)s, c) + 1, sizeof(*tab));
	if (!s || tab == NULL)
		return (NULL);
	i = 0;
	it = 0;
	while (s[i])
	{
		if (!(s[i] == c))
		{
			tab[it] = fill_word(&str[i], c, tab[it]);
			if (tab[it] == NULL)
				return (free_tab(tab));
			it++;
			i = i + len_word(&str[i], c) - 1;
		}
		i++;
	}
	tab[it] = NULL;
	return (tab);
}
