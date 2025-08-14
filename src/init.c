/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjeremy <mjeremy@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 13:56:59 by mjeremy           #+#    #+#             */
/*   Updated: 2025/08/14 10:19:47 by mjeremy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

/*
Initialize t_frac to a clean, known state.
Nulls MLX/window/image pointers and buffer; zeroes numeric fields; sets
safe defaults (e.g., max_iter) and a sentinel (set = -1) before parsing.
Enables safe early exits via clean_and_exit(...) and avoids using
uninitialized fields later in the program.
*/
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
	f->iter_bias = 0;
}

void	update_iters(t_frac *f)
{
	double	base_w;
	double	zoom;
	int		mi;

	if (f->set == JULIA)
		base_w = 4.0;
	else
		base_w = 3.0;
	zoom = base_w / (f->max_r - f->min_r);
	mi = 100 + (int)(15.0 * log2(zoom + 1.0));
	mi += f->iter_bias;
	if (mi < 50)
		mi = 50;
	if (mi > 5000)
		mi = 5000;
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
		center_r = 0.0;
		center_i = 0.0;
		width = 4.0;
		height = width * HEIGHT / WIDTH;
	}
	else
	{
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
		clean_and_exit(msg("MLX connection error.", 1), f);
	f->win = mlx_new_window(f->mlx, WIDTH, HEIGHT, "Fract-ol");
	if (!f->win)
		clean_and_exit(msg("MLX window creation error.", 1), f);
	init_complex_plane(f);
	update_iters(f);
}
