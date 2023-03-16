/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlanza <jlanza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 13:53:22 by jlanza            #+#    #+#             */
/*   Updated: 2022/11/15 11:04:07 by jlanza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	ft_ismin(int c)
{
	if ('a' <= c && c <= 'z')
		return (1);
	return (0);
}

static int	ft_ismaj(int c)
{
	if ('A' <= c && c <= 'Z')
		return (1);
	return (0);
}

int	ft_isalpha(int c)
{
	return (ft_ismin(c) || ft_ismaj(c));
}
