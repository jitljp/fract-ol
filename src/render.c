/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjeremy <mjeremy@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 13:36:06 by mjeremy           #+#    #+#             */
/*   Updated: 2025/08/09 13:36:08 by mjeremy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

static void	put_pixel(t_frac *f, int x, int y, int color)
{
	char	*p;

	p = f->buf + y * f->line + x * (f->bpp / 8);
	*(int *)p = color;
}

static int	iter_mandel(double cr, double ci, double *zr, double *zi)
{
	int		n;
	double	tmp;
	double	zr2;
	double	zi2;

	n = 0;
	*zr = 0.0;
	*zi = 0.0;
	zr2 = 0.0;
	zi2 = 0.0;
	while (n < MAX_ITERS && (zr2 + zi2) <= 4.0)
	{
		tmp = *zr * *zr - *zi * *zi + cr;
		*zi = 2.0 * *zr * *zi + ci;
		*zr = tmp;
		zr2 = *zr * *zr;
		zi2 = *zi * *zi;
		n++;
	}
	return (n);
}

static int	iter_julia(t_frac *f, double zr, double zi)
{
	int		n;
	double	tmp;
	double	zr2;
	double	zi2;

	n = 0;
	zr2 = zr * zr;
	zi2 = zi * zi;
	while (n < MAX_ITERS && (zr2 + zi2) <= 4.0)
	{
		tmp = zr * zr - zi * zi + f->cr;
		zi = 2.0 * zr * zi + f->ci;
		zr = tmp;
		zr2 = zr * zr;
		zi2 = zi * zi;
		n++;
	}
	return (n);
}

void	render(t_frac *f)
{
	int		x;
	int		y;
	double	r;
	double	i;
	double	zr;
	double	zi;
	int		n;

	y = 0;
	while (y < HEIGHT)
	{
		i = f->max_i + (f->min_i - f->max_i) * ((double)y / (HEIGHT - 1));
		x = 0;
		while (x < WIDTH)
		{
			r = f->min_r + (f->max_r - f->min_r) * ((double)x / (WIDTH - 1));
			if (f->set == MANDELBROT)
				n = iter_mandel(r, i, &zr, &zi);
			else
				n = iter_julia(f, r, i);
			put_pixel(f, x, y, get_color(f, n, zr, zi));
			x++;
		}
		y++;
	}
}
