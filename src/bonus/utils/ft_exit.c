/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbocquel <mbocquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 11:37:07 by mbocquel          #+#    #+#             */
/*   Updated: 2023/04/04 21:41:18 by mbocquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	close_win(void *p)
{
	t_param	*prm;

	prm = (t_param *)p;
	destroy_images(prm);
	mlx_destroy_image(prm->mlx, prm->layer.front.img);
	//mlx_destroy_image(prm->mlx, prm->mini_map.img);
	mlx_destroy_window(prm->mlx, prm->win);
	mlx_destroy_display(prm->mlx);
	ft_printf("---- Goodbye, see you latter ! ----\n");
	return (ft_exit(prm, EXIT_SUCCESS));
}

int	ft_exit(t_param *prm, int exit_code)
{
	empty_garbage(prm, -1);
	exit(exit_code);
}

int	ft_exit_error(t_param *prm, int exit_code)
{
	close_win((void *)prm);
	return (ft_exit(prm, exit_code));
}
