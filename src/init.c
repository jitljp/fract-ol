/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjeremy <mjeremy@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 13:56:59 by mjeremy           #+#    #+#             */
/*   Updated: 2025/08/09 14:47:20 by mjeremy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

void	clean_init(t_frac *f)
{
	f->mlx = NULL;
	f->win = NULL;
	f->img = NULL;
	f->buf = NULL;
	f->bpp = 0;
	f->line = 0;
	f->endian = 0;
	f->set = -1;
	f->min_r = 0;
	f->max_r = 0;
	f->min_i = 0;
	f->max_i = 0;
	f->cr = 0;
	f->ci = 0;
	f->shift = 0;
	f->max_iter = 100;
}

void	update_iters(t_frac *f)
{
	double	base_w;
	double	zoom;
	int		mi;

	base_w = (f->set == JULIA) ? 4.0 : 3.0;
	zoom = base_w / (f->max_r - f->min_r);
	mi = 100 + (int)(15 * log2(zoom + 1.0));
	if (mi < 100)
		mi = 100;
	if (mi > 1000)
		mi = 1000;
	f->max_iter = mi;
}

void	init_complex_plane(t_frac *f)
{
	double	center_r;
	double	center_i;
	double	width;
	double	height;

	if (f->set == JULIA)
	{
		// Julia set: centered around origin with 4x4 view
		center_r = 0.0;
		center_i = 0.0;
		width = 4.0;
		height = width * HEIGHT / WIDTH;
	}
	else
	{
		// Mandelbrot set: centered on the main cardioid
		center_r = -0.5;
		center_i = 0.0;
		width = 3.0;
		height = width * HEIGHT / WIDTH;
	}

	f->min_r = center_r - width / 2.0;
	f->max_r = center_r + width / 2.0;
	f->max_i = center_i + height / 2.0;
	f->min_i = center_i - height / 2.0;
}

void	init(t_frac *f)
{
	f->mlx = mlx_init();
	if (!f->mlx)
		clean_and_exit(msg("MLX connection error.", "", 1), f);
	f->win = mlx_new_window(f->mlx, WIDTH, HEIGHT, "Fract-ol");
	if (!f->win)
		clean_and_exit(msg("MLX window creation error.", "", 1), f);
	init_complex_plane(f);
	update_iters(f);
}
