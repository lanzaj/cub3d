/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlanza <jlanza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 11:37:07 by mbocquel          #+#    #+#             */
/*   Updated: 2024/02/12 18:12:28 by jlanza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	leave_win(void *p)
{
	t_param	*prm;

	prm = (t_param *)p;
	if (prm->key.key_tab == 0)
	{
		prm->key.key_tab = 1;
		leave_window(p);
	}
	else
	{
		prm->key.key_tab = 0;
		enter_window(p);
	}
}

int	close_win(void *p)
{
	t_param	*prm;

	prm = (t_param *)p;
	destroy_images(prm);
	mlx_destroy_image(prm->mlx, prm->layer.front.img);
	mlx_destroy_image(prm->mlx, prm->layer.back.img);
	mlx_destroy_window(prm->mlx, prm->win);
	mlx_destroy_display(prm->mlx);
	ft_printf("\r                    ---- Goodbye, see you later ! ----\n\n");
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
