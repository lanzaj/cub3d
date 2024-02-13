/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbocquel <mbocquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 12:08:32 by mbocquel          #+#    #+#             */
/*   Updated: 2023/03/18 16:38:59 by mbocquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	create_trgb(unsigned char t, unsigned char r,
	unsigned char g, unsigned char b)
{
	return (*(int *)(unsigned char [4]){b, g, r, t});
}

unsigned char	get_t(int trgb)
{
	return (((unsigned char *)&trgb)[3]);
}

unsigned char	get_r(int trgb)
{
	return (((unsigned char *)&trgb)[2]);
}

unsigned char	get_g(int trgb)
{
	return (((unsigned char *)&trgb)[1]);
}

unsigned char	get_b(int trgb)
{
	return (((unsigned char *)&trgb)[0]);
}
