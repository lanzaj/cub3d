/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_distance.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbocquel <mbocquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 11:05:38 by mbocquel          #+#    #+#             */
/*   Updated: 2023/04/05 14:38:19 by mbocquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

double	get_distance(t_coord a, t_coord b)
{
	double	result;

	result = sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
	return (result);
}

double	get_distance_point(t_point a, t_point b)
{
	double	result;

	result = sqrt(pow((double)a.x - (double)b.x, 2)
			+ pow((double)a.y - (double)b.y, 2));
	return (result);
}
