/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   max_min.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbocquel <mbocquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 14:38:28 by mbocquel          #+#    #+#             */
/*   Updated: 2023/04/06 17:47:39 by mbocquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	ft_max(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}

int	ft_min(int a, int b)
{
	if (a < b)
		return (a);
	return (b);
}

double	ft_max_d(double a, double b)
{
	if (a > b)
		return (a);
	return (b);
}

double	ft_min_d(double a, double b)
{
	if (a < b)
		return (a);
	return (b);
}

double	v_abs_dbl(double a)
{
	if (a < 0 && a > (-1 * DBL_MAX))
		return (-a);
	else
		return (a);
}
