/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlanza <jlanza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 16:21:51 by jlanza            #+#    #+#             */
/*   Updated: 2023/01/13 16:09:19 by jlanza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i_src;
	size_t	src_len;
	size_t	dst_len;

	src_len = ft_strlen(src);
	dst_len = ft_strlen(dst);
	if (dst_len >= size)
		return (size + src_len);
	i_src = 0;
	while (src[i_src] && i_src < size - dst_len - 1)
	{
		dst[dst_len + i_src] = src[i_src];
		i_src++;
	}
	dst[dst_len + i_src] = '\0';
	return (dst_len + src_len);
}
