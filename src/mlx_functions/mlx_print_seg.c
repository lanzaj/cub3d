/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_print_seg.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbocquel <mbocquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 10:29:38 by mbocquel          #+#    #+#             */
/*   Updated: 2023/03/20 19:36:37 by mbocquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	process_seg_cas1(int *d, t_point *delt, t_point *p, int *inc_y)
{
	if (*d < 0)
		*d += 2 * (*delt).y;
	else
	{
		*d += 2 * ((*delt).y - (*delt).x);
		(*p).y += *inc_y;
	}	
	((*p).x)++;
}

static void	put_segment_img_cas1(t_img *img, t_seg seg)
{
	t_point	delt;
	t_point	p;
	int		inc_y;
	int		d;

	delt.x = seg.end.x - seg.start.x;
	delt.y = seg.end.y - seg.start.y;
	if (seg.start.x > seg.end.x)
		ft_swap_seg(&seg, &delt);
	inc_y = 1;
	if (delt.y < 0)
	{
		inc_y = -1;
		delt.y = -delt.y;
	}
	p = seg.start;
	d = 2 * delt.y - delt.x;
	while (p.x <= seg.end.x)
	{
		if (p.x >= 0 && p.x < img->width && p.y >= 0 && p.y < img->height)
			my_mlx_pixel_put(img, p.x, p.y,
				get_color_gradian(seg.start, seg.end, p));
		process_seg_cas1(&d, &delt, &p, &inc_y);
	}
}

static void	process_seg_cas2(int *d, t_point *delt, t_point *p, int *inc_x)
{
	if (*d < 0)
		*d += 2 * (*delt).x;
	else
	{
		*d += 2 * ((*delt).x - (*delt).y);
		(*p).x += *inc_x;
	}
	((*p).y)++;
}

static void	put_segment_img_cas2(t_img *img, t_seg seg)
{
	t_point	delt;
	t_point	p;
	int		inc_x;
	int		d;

	delt.x = seg.end.x - seg.start.x;
	delt.y = seg.end.y - seg.start.y;
	if (seg.start.y > seg.end.y)
		ft_swap_seg(&seg, &delt);
	inc_x = 1;
	if (delt.x < 0)
	{
		inc_x = -1;
		delt.x = -delt.x;
	}
	p = seg.start;
	d = 2 * delt.x - delt.y;
	while (p.y <= seg.end.y)
	{
		if (p.x >= 0 && p.x < img->width && p.y >= 0 && p.y < img->height)
			my_mlx_pixel_put(img, p.x, p.y,
				get_color_gradian(seg.start, seg.end, p));
		process_seg_cas2(&d, &delt, &p, &inc_x);
	}
}

void	put_segment_img(t_img *img, t_point start, t_point end)
{
	t_point	delt;
	t_seg	seg;

	seg.start = start;
	seg.end = end;
	delt.x = seg.end.x - seg.start.x;
	delt.y = seg.end.y - seg.start.y;
	if (va_abs(delt.x) > va_abs(delt.y))
		put_segment_img_cas1(img, seg);
	else
		put_segment_img_cas2(img, seg);
}
