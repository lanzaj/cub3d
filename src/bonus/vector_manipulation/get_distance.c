/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_distance.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlanza <jlanza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 11:05:38 by mbocquel          #+#    #+#             */
/*   Updated: 2023/04/06 03:19:55 by jlanza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

double	get_distance(t_coord a, t_coord b)
{
	return (sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y)));
}

double	get_distance_square(t_coord a, t_coord b)
{
	return ((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

double	get_distance_point(t_point a, t_point b)
{
	double	result;

	result = sqrt(pow((double)a.x - (double)b.x, 2)
			+ pow((double)a.y - (double)b.y, 2));
	return (result);
}
