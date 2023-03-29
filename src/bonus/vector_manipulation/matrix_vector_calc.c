/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_vector_calc.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbocquel <mbocquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 16:55:32 by mbocquel          #+#    #+#             */
/*   Updated: 2023/03/20 18:02:56 by mbocquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

t_coord	rotate(double angle, t_coord coord)
{
	t_coord	rot;

	rot.x = cos(angle) * coord.x + sin(angle) * coord.y;
	rot.y = cos(angle) * coord.y - sin(angle) * coord.x;
	return (rot);
}

double	prod_scal(t_coord vect_1, t_coord vect_2)
{
	return (vect_1.x * vect_2.x + vect_1.y * vect_2.y);
}

t_coord	sum_vect(t_coord vect_1, t_coord vect_2)
{
	t_coord	res;

	res.x = vect_1.x + vect_2.x;
	res.y = vect_1.y + vect_2.y;
	return (res);
}

t_coord	prod_vect(double factor, t_coord vect)
{
	t_coord	res;

	res.x = factor * vect.x;
	res.y = factor * vect.y;
	return (res);
}

int	va_abs(int i)
{
	if (i < 0 && i != -2147483648)
		i = -i;
	return (i);
}
