/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjeremy <mjeremy@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 13:56:59 by mjeremy           #+#    #+#             */
/*   Updated: 2025/08/09 13:35:41 by mjeremy          ###   ########.fr       */
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
	f->palette_mode = 0;
	f->shift = 0;
	set_base_color(f, 0x3a9ad9);
}

void	init_complex_plane(t_frac *f)
{
	if (f->set == JULIA)
	{
		f->min_r = -2.0;
		f->max_r = 2.0;
		f->min_i = -2.0;
		f->max_i = f->min_i + (f->max_r - f->min_r) * HEIGHT / WIDTH;
	}
	else
	{
		f->min_r = -2.0;
		f->max_r = 1.0;
		f->max_i = -1.5;
		f->min_i = f->max_i + (f->max_r - f->min_r) * HEIGHT / WIDTH;
	}
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
}
