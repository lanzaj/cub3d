/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_vector_calc.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbocquel <mbocquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 16:55:32 by mbocquel          #+#    #+#             */
/*   Updated: 2023/03/17 15:45:44 by mbocquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

t_coord	rotate(double angle, t_coord coord)
{
	t_coord	rot;

	rot.x = cos(angle) * coord.x - sin(angle) * coord.y;
	rot.y = sin(angle) * coord.x + cos(angle) * coord.y;
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

int	va_abs(int i)
{
	if (i < 0 && i != -2147483648)
		i = -i;
	return (i);
}
